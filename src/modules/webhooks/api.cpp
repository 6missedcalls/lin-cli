#include "modules/webhooks/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string WEBHOOKS_LIST_QUERY = R"gql(
query WebhooksList($first: Int, $after: String) {
    webhooks(first: $first, after: $after) {
        nodes {
            id createdAt updatedAt label url enabled
            team { id }
            creator { id displayName }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string WEBHOOK_GET_QUERY = R"gql(
query WebhookGet($id: String!) {
    webhook(id: $id) {
        id createdAt updatedAt label url enabled
        team { id }
        creator { id displayName }
    }
}
)gql";

static const std::string WEBHOOK_CREATE_MUTATION = R"gql(
mutation WebhookCreate($input: WebhookCreateInput!) {
    webhookCreate(input: $input) {
        webhook {
            id createdAt updatedAt label url enabled
            team { id }
            creator { id displayName }
        }
    }
}
)gql";

static const std::string WEBHOOK_UPDATE_MUTATION = R"gql(
mutation WebhookUpdate($id: String!, $input: WebhookUpdateInput!) {
    webhookUpdate(id: $id, input: $input) {
        webhook {
            id createdAt updatedAt label url enabled
            team { id }
            creator { id displayName }
        }
    }
}
)gql";

static const std::string WEBHOOK_DELETE_MUTATION = R"gql(
mutation WebhookDelete($id: String!) {
    webhookDelete(id: $id) { success }
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

namespace webhooks_api {

Connection<Webhook> list_webhooks(int first, const std::optional<std::string>& after) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }

    auto data = execute_graphql(WEBHOOKS_LIST_QUERY, variables);

    Connection<Webhook> result;
    from_json(data.at("webhooks"), result);
    return result;
}

Webhook get_webhook(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(WEBHOOK_GET_QUERY, variables);

    Webhook webhook;
    from_json(data.at("webhook"), webhook);
    return webhook;
}

Webhook create_webhook(
    const std::string& url,
    const std::optional<std::string>& label,
    const std::optional<std::string>& team_id,
    const std::optional<bool>& enabled
) {
    json input = json::object();
    input["url"] = url;

    if (label.has_value()) {
        input["label"] = label.value();
    }
    if (team_id.has_value()) {
        input["teamId"] = team_id.value();
    }
    if (enabled.has_value()) {
        input["enabled"] = enabled.value();
    }

    json variables = json::object();
    variables["input"] = input;

    auto data = execute_graphql(WEBHOOK_CREATE_MUTATION, variables);

    Webhook webhook;
    from_json(data.at("webhookCreate").at("webhook"), webhook);
    return webhook;
}

Webhook update_webhook(
    const std::string& id,
    const std::optional<std::string>& url,
    const std::optional<std::string>& label,
    const std::optional<bool>& enabled
) {
    json input = json::object();

    if (url.has_value()) {
        input["url"] = url.value();
    }
    if (label.has_value()) {
        input["label"] = label.value();
    }
    if (enabled.has_value()) {
        input["enabled"] = enabled.value();
    }

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = input;

    auto data = execute_graphql(WEBHOOK_UPDATE_MUTATION, variables);

    Webhook webhook;
    from_json(data.at("webhookUpdate").at("webhook"), webhook);
    return webhook;
}

void delete_webhook(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(WEBHOOK_DELETE_MUTATION, variables);

    bool success = data.at("webhookDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete webhook " + id);
    }
}

}  // namespace webhooks_api
