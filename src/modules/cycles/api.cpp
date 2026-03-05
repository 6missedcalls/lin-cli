#include "modules/cycles/api.h"

#include <algorithm>
#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string CYCLES_LIST_QUERY = R"gql(
query CyclesList($first: Int, $after: String, $filter: CycleFilter) {
    cycles(first: $first, after: $after, filter: $filter) {
        nodes {
            id number name description
            startsAt endsAt completedAt
            createdAt updatedAt progress
            isActive isFuture isPast isNext isPrevious
            team { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string CYCLE_GET_QUERY = R"gql(
query CycleGet($id: String!) {
    cycle(id: $id) {
        id number name description
        startsAt endsAt completedAt
        createdAt updatedAt progress
        isActive isFuture isPast isNext isPrevious
        team { id name }
    }
}
)gql";

static const std::string CYCLE_CREATE_MUTATION = R"gql(
mutation CycleCreate($input: CycleCreateInput!) {
    cycleCreate(input: $input) {
        cycle {
            id number name description
            startsAt endsAt completedAt
            createdAt updatedAt progress
            isActive isFuture isPast isNext isPrevious
            team { id name }
        }
    }
}
)gql";

static const std::string CYCLE_UPDATE_MUTATION = R"gql(
mutation CycleUpdate($id: String!, $input: CycleUpdateInput!) {
    cycleUpdate(id: $id, input: $input) {
        cycle {
            id number name description
            startsAt endsAt completedAt
            createdAt updatedAt progress
            isActive isFuture isPast isNext isPrevious
            team { id name }
        }
    }
}
)gql";

static const std::string CYCLE_ARCHIVE_MUTATION = R"gql(
mutation CycleArchive($id: String!) {
    cycleArchive(id: $id) { success }
}
)gql";

// ---------------------------------------------------------------------------
// Shared helpers
// ---------------------------------------------------------------------------

static const std::string GRAPHQL_ENDPOINT = "https://api.linear.app/graphql";

static json execute_graphql(const std::string& query, const json& variables) {
    HttpClient client;
    auto api_key = get_api_key();
    auto body = build_request_body({query, variables});

    auto response = with_retry([&]() {
        auto resp = client.post(
            GRAPHQL_ENDPOINT,
            body,
            {{"Content-Type", "application/json"}, {"Authorization", api_key}}
        );
        check_http_status(resp.status_code, resp.body);
        return resp;
    });

    return parse_response(response.body);
}

// ---------------------------------------------------------------------------
// API implementations
// ---------------------------------------------------------------------------

namespace cycles_api {

Connection<Cycle> list_cycles(const CycleListOptions& opts) {
    json variables = json::object();
    variables["first"] = opts.first;

    if (opts.after.has_value()) {
        variables["after"] = opts.after.value();
    }
    if (!opts.filter.is_null()) {
        variables["filter"] = opts.filter;
    }

    auto data = execute_graphql(CYCLES_LIST_QUERY, variables);

    Connection<Cycle> result;
    from_json(data.at("cycles"), result);
    return result;
}

Cycle get_cycle(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(CYCLE_GET_QUERY, variables);

    Cycle cycle;
    from_json(data.at("cycle"), cycle);
    return cycle;
}

std::string resolve_cycle_id(const std::string& input) {
    // Fast path: try direct UUID lookup
    try {
        auto cycle = get_cycle(input);
        return cycle.id;
    } catch (const LinError&) {
        // Not a UUID — fall through
    }

    // Fetch all cycles and match by number or name
    CycleListOptions opts;
    opts.first = 250;
    auto conn = list_cycles(opts);

    // Try matching by number (e.g. "11" or "#11")
    std::string num_str = input;
    if (!num_str.empty() && num_str[0] == '#') {
        num_str = num_str.substr(1);
    }
    try {
        int target_num = std::stoi(num_str);
        for (const auto& c : conn.nodes) {
            if (static_cast<int>(c.number) == target_num) {
                return c.id;
            }
        }
    } catch (const std::exception&) {
        // Not a number — try name match
    }

    // Case-insensitive name match
    std::string lower_input = input;
    std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(),
        [](unsigned char ch) { return std::tolower(ch); });

    for (const auto& c : conn.nodes) {
        if (!c.name.has_value()) continue;
        std::string lower_name = c.name.value();
        std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
            [](unsigned char ch) { return std::tolower(ch); });
        if (lower_name == lower_input) {
            return c.id;
        }
    }

    throw LinError(ErrorKind::NotFound,
        "Cycle not found: \"" + input + "\". Use a cycle number, name, or UUID.");
}

Cycle create_cycle(const CycleCreateInput& input) {
    json cycle_input = json::object();
    cycle_input["teamId"] = input.team_id;
    cycle_input["startsAt"] = input.starts_at;
    cycle_input["endsAt"] = input.ends_at;

    if (input.name.has_value()) {
        cycle_input["name"] = input.name.value();
    }
    if (input.description.has_value()) {
        cycle_input["description"] = input.description.value();
    }

    json variables = json::object();
    variables["input"] = cycle_input;

    auto data = execute_graphql(CYCLE_CREATE_MUTATION, variables);

    Cycle cycle;
    from_json(data.at("cycleCreate").at("cycle"), cycle);
    return cycle;
}

Cycle update_cycle(const std::string& id, const CycleUpdateInput& input) {
    json update_input = json::object();

    if (input.name.has_value()) {
        update_input["name"] = input.name.value();
    }
    if (input.description.has_value()) {
        update_input["description"] = input.description.value();
    }
    if (input.starts_at.has_value()) {
        update_input["startsAt"] = input.starts_at.value();
    }
    if (input.ends_at.has_value()) {
        update_input["endsAt"] = input.ends_at.value();
    }

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = update_input;

    auto data = execute_graphql(CYCLE_UPDATE_MUTATION, variables);

    Cycle cycle;
    from_json(data.at("cycleUpdate").at("cycle"), cycle);
    return cycle;
}

void archive_cycle(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(CYCLE_ARCHIVE_MUTATION, variables);

    bool success = data.at("cycleArchive").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to archive cycle " + id);
    }
}

}  // namespace cycles_api
