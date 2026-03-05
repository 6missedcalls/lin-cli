#include "modules/users/api.h"

#include <algorithm>
#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query strings
// ---------------------------------------------------------------------------

static const std::string USERS_LIST_QUERY = R"gql(
query UsersList($first: Int, $after: String, $includeDisabled: Boolean) {
    users(first: $first, after: $after, includeDisabled: $includeDisabled) {
        nodes {
            id name displayName email avatarUrl description
            timezone lastSeen active admin guest isMe createdAt
            statusEmoji statusLabel
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string USER_GET_QUERY = R"gql(
query UserGet($id: String!) {
    user(id: $id) {
        id name displayName email avatarUrl description
        timezone lastSeen active admin guest isMe createdAt
        statusEmoji statusLabel
    }
}
)gql";

static const std::string VIEWER_QUERY = R"gql(
query Viewer {
    viewer {
        id name displayName email avatarUrl description
        timezone lastSeen active admin guest isMe createdAt
        statusEmoji statusLabel
    }
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

namespace users_api {

Connection<User> list_users(
    int first,
    const std::optional<std::string>& after,
    bool include_disabled
) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }
    if (include_disabled) {
        variables["includeDisabled"] = true;
    }

    auto data = execute_graphql(USERS_LIST_QUERY, variables);

    Connection<User> result;
    from_json(data.at("users"), result);
    return result;
}

User get_user(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(USER_GET_QUERY, variables);

    User user;
    from_json(data.at("user"), user);
    return user;
}

User get_viewer() {
    auto data = execute_graphql(VIEWER_QUERY, json::object());

    User user;
    from_json(data.at("viewer"), user);
    return user;
}

std::string resolve_user_id(const std::string& input) {
    // If it looks like a UUID, try direct lookup first
    if (input.size() == 36 && input[8] == '-') {
        try {
            get_user(input);
            return input;
        } catch (const LinError&) {
            // Not a valid UUID — fall through to name/email search
        }
    }

    // Search by name, displayName, or email (case-insensitive)
    auto connection = list_users(250);
    std::string lower_input = input;
    std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(),
        [](unsigned char c) { return std::tolower(c); });

    for (const auto& user : connection.nodes) {
        auto lower = [](const std::string& s) {
            std::string r = s;
            std::transform(r.begin(), r.end(), r.begin(),
                [](unsigned char c) { return std::tolower(c); });
            return r;
        };
        if (lower(user.name) == lower_input ||
            lower(user.display_name) == lower_input ||
            lower(user.email) == lower_input) {
            return user.id;
        }
    }

    throw LinError(ErrorKind::NotFound,
        "User not found: '" + input + "'. Use a name, email, or ID.");
}

}  // namespace users_api
