#include "modules/views/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string VIEWS_LIST_QUERY = R"gql(
query CustomViewsList($first: Int, $after: String) {
    customViews(first: $first, after: $after) {
        nodes {
            id createdAt updatedAt name description icon color slugId modelName shared filterData
            owner { id displayName }
            team { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string VIEW_GET_QUERY = R"gql(
query CustomViewGet($id: String!) {
    customView(id: $id) {
        id createdAt updatedAt name description icon color slugId modelName shared filterData
        owner { id displayName }
        team { id name }
    }
}
)gql";

static const std::string VIEW_CREATE_MUTATION = R"gql(
mutation CustomViewCreate($input: CustomViewCreateInput!) {
    customViewCreate(input: $input) {
        customView {
            id createdAt updatedAt name description icon color slugId modelName shared filterData
            owner { id displayName }
            team { id name }
        }
    }
}
)gql";

static const std::string VIEW_DELETE_MUTATION = R"gql(
mutation CustomViewDelete($id: String!) {
    customViewDelete(id: $id) { success }
}
)gql";

// ---------------------------------------------------------------------------
// Shared helper
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

namespace views_api {

Connection<CustomView> list_views(
    int first,
    const std::optional<std::string>& after,
    const std::optional<bool>& shared
) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }

    // Linear's customViews query does not support a filter parameter,
    // so shared filtering is applied client-side after fetching.
    auto data = execute_graphql(VIEWS_LIST_QUERY, variables);

    Connection<CustomView> result;
    from_json(data.at("customViews"), result);

    if (shared.has_value()) {
        bool want_shared = shared.value();
        std::vector<CustomView> filtered;
        filtered.reserve(result.nodes.size());
        for (auto& view : result.nodes) {
            if (view.shared == want_shared) {
                filtered.push_back(std::move(view));
            }
        }
        result.nodes = std::move(filtered);
    }

    return result;
}

CustomView get_view(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(VIEW_GET_QUERY, variables);

    CustomView view;
    from_json(data.at("customView"), view);
    return view;
}

CustomView create_view(
    const std::string& name,
    const std::optional<std::string>& description,
    bool shared,
    const std::optional<json>& filter_json
) {
    json view_input = json::object();
    view_input["name"] = name;
    view_input["shared"] = shared;

    if (description.has_value()) {
        view_input["description"] = description.value();
    }
    if (filter_json.has_value()) {
        view_input["filterData"] = filter_json.value();
    }

    json variables = json::object();
    variables["input"] = view_input;

    auto data = execute_graphql(VIEW_CREATE_MUTATION, variables);

    CustomView view;
    from_json(data.at("customViewCreate").at("customView"), view);
    return view;
}

void delete_view(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(VIEW_DELETE_MUTATION, variables);

    bool success = data.at("customViewDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete view " + id);
    }
}

}  // namespace views_api
