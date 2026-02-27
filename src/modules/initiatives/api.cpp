#include "modules/initiatives/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query strings
// ---------------------------------------------------------------------------

static const std::string INITIATIVES_LIST_QUERY = R"gql(
query InitiativesList($first: Int, $after: String) {
    initiatives(first: $first, after: $after) {
        nodes {
            id name description icon color slugId url
            status health targetDate startedAt completedAt trashed
            createdAt updatedAt
            owner { id displayName }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string INITIATIVE_GET_QUERY = R"gql(
query InitiativeGet($id: String!) {
    initiative(id: $id) {
        id name description icon color slugId url
        status health targetDate startedAt completedAt trashed
        createdAt updatedAt
        owner { id displayName }
    }
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

namespace initiatives_api {

Connection<Initiative> list_initiatives(const InitiativeListOptions& opts) {
    json variables = json::object();
    variables["first"] = opts.first;

    if (opts.after.has_value()) {
        variables["after"] = opts.after.value();
    }

    auto data = execute_graphql(INITIATIVES_LIST_QUERY, variables);

    Connection<Initiative> result;
    from_json(data.at("initiatives"), result);

    // Apply client-side status filter if requested (Linear API may not support
    // server-side filtering on initiatives status in all versions).
    if (opts.status_filter.has_value()) {
        const std::string& wanted = opts.status_filter.value();
        std::vector<Initiative> filtered;
        filtered.reserve(result.nodes.size());
        for (auto& initiative : result.nodes) {
            if (initiative.status.has_value() && initiative.status.value() == wanted) {
                filtered.push_back(std::move(initiative));
            }
        }
        result.nodes = std::move(filtered);
    }

    return result;
}

Initiative get_initiative(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(INITIATIVE_GET_QUERY, variables);

    Initiative initiative;
    from_json(data.at("initiative"), initiative);
    return initiative;
}

}  // namespace initiatives_api
