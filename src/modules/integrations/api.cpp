#include "modules/integrations/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query strings
// ---------------------------------------------------------------------------

static const std::string INTEGRATIONS_LIST_QUERY = R"gql(
query IntegrationsList($first: Int, $after: String) {
    integrations(first: $first, after: $after) {
        nodes {
            id service createdAt
            team { id name }
            creator { id displayName }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string INTEGRATION_GET_QUERY = R"gql(
query IntegrationGet($id: String!) {
    integration(id: $id) {
        id service createdAt
        team { id name }
        creator { id displayName }
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

namespace integrations_api {

Connection<Integration> list_integrations(
    int first,
    const std::optional<std::string>& after
) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }

    auto data = execute_graphql(INTEGRATIONS_LIST_QUERY, variables);

    Connection<Integration> result;
    from_json(data.at("integrations"), result);
    return result;
}

Integration get_integration(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(INTEGRATION_GET_QUERY, variables);

    Integration integration;
    from_json(data.at("integration"), integration);
    return integration;
}

}  // namespace integrations_api
