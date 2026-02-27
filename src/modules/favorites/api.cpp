#include "modules/favorites/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string FAVORITES_LIST_QUERY = R"gql(
query FavoritesList($first: Int, $after: String) {
    favorites(first: $first, after: $after) {
        nodes {
            id createdAt type sortOrder
            folderName url title
            issue { id }
            project { id }
            cycle { id }
            customView { id }
            document { id }
            label { id }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string FAVORITE_CREATE_MUTATION = R"gql(
mutation FavoriteCreate($input: FavoriteCreateInput!) {
    favoriteCreate(input: $input) {
        favorite {
            id createdAt type sortOrder
            folderName url title
            issue { id }
            project { id }
            cycle { id }
            customView { id }
            document { id }
            label { id }
        }
    }
}
)gql";

static const std::string FAVORITE_DELETE_MUTATION = R"gql(
mutation FavoriteDelete($id: String!) {
    favoriteDelete(id: $id) { success }
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

namespace favorites_api {

Connection<Favorite> list_favorites(int first, std::optional<std::string> after) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }

    auto data = execute_graphql(FAVORITES_LIST_QUERY, variables);

    Connection<Favorite> result;
    from_json(data.at("favorites"), result);
    return result;
}

Favorite create_favorite(const FavoriteCreateInput& input) {
    json fav_input = json::object();

    if (input.issue_id.has_value()) {
        fav_input["issueId"] = input.issue_id.value();
    }
    if (input.project_id.has_value()) {
        fav_input["projectId"] = input.project_id.value();
    }
    if (input.cycle_id.has_value()) {
        fav_input["cycleId"] = input.cycle_id.value();
    }
    if (input.custom_view_id.has_value()) {
        fav_input["customViewId"] = input.custom_view_id.value();
    }
    if (input.document_id.has_value()) {
        fav_input["documentId"] = input.document_id.value();
    }
    if (input.label_id.has_value()) {
        fav_input["labelId"] = input.label_id.value();
    }

    json variables = json::object();
    variables["input"] = fav_input;

    auto data = execute_graphql(FAVORITE_CREATE_MUTATION, variables);

    Favorite fav;
    from_json(data.at("favoriteCreate").at("favorite"), fav);
    return fav;
}

void delete_favorite(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(FAVORITE_DELETE_MUTATION, variables);

    bool success = data.at("favoriteDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete favorite " + id);
    }
}

}  // namespace favorites_api
