#include "modules/comments/api.h"

#include <string>
#include <utility>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string COMMENTS_LIST_QUERY = R"gql(
query CommentsList($first: Int, $after: String, $filter: CommentFilter) {
    comments(first: $first, after: $after, filter: $filter) {
        nodes {
            id body editedAt resolvedAt url createdAt updatedAt
            user { id displayName }
            parent { id }
            issue { id }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string COMMENT_GET_QUERY = R"gql(
query CommentGet($id: String!) {
    comment(id: $id) {
        id body editedAt resolvedAt url createdAt updatedAt
        user { id displayName }
        parent { id }
        issue { id }
    }
}
)gql";

static const std::string COMMENT_CREATE_MUTATION = R"gql(
mutation CommentCreate($input: CommentCreateInput!) {
    commentCreate(input: $input) {
        comment {
            id body editedAt resolvedAt url createdAt updatedAt
            user { id displayName }
            parent { id }
            issue { id }
        }
    }
}
)gql";

static const std::string COMMENT_UPDATE_MUTATION = R"gql(
mutation CommentUpdate($id: String!, $input: CommentUpdateInput!) {
    commentUpdate(id: $id, input: $input) {
        comment {
            id body editedAt resolvedAt url createdAt updatedAt
            user { id displayName }
            parent { id }
            issue { id }
        }
    }
}
)gql";

static const std::string COMMENT_DELETE_MUTATION = R"gql(
mutation CommentDelete($id: String!) {
    commentDelete(id: $id) { success }
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

namespace comments_api {

Connection<Comment> list_comments(
    const std::string& issue_id,
    int first,
    const std::optional<std::string>& after
) {
    json filter = json::object();
    json issue_filter = json::object();
    issue_filter["id"] = json::object({{"eq", issue_id}});
    filter["issue"] = issue_filter;

    json variables = json::object();
    variables["first"] = first;
    variables["filter"] = filter;

    if (after.has_value()) {
        variables["after"] = after.value();
    }

    auto data = execute_graphql(COMMENTS_LIST_QUERY, variables);

    Connection<Comment> result;
    from_json(data.at("comments"), result);
    return result;
}

Comment get_comment(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(COMMENT_GET_QUERY, variables);

    Comment comment;
    from_json(data.at("comment"), comment);
    return comment;
}

Comment create_comment(
    const std::string& issue_id,
    const std::string& body,
    const std::optional<std::string>& parent_id
) {
    json comment_input = json::object();
    comment_input["issueId"] = issue_id;
    comment_input["body"] = body;

    if (parent_id.has_value()) {
        comment_input["parentId"] = parent_id.value();
    }

    json variables = json::object();
    variables["input"] = comment_input;

    auto data = execute_graphql(COMMENT_CREATE_MUTATION, variables);

    Comment comment;
    from_json(data.at("commentCreate").at("comment"), comment);
    return comment;
}

Comment update_comment(const std::string& id, const std::string& body) {
    json comment_input = json::object();
    comment_input["body"] = body;

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = comment_input;

    auto data = execute_graphql(COMMENT_UPDATE_MUTATION, variables);

    Comment comment;
    from_json(data.at("commentUpdate").at("comment"), comment);
    return comment;
}

void delete_comment(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(COMMENT_DELETE_MUTATION, variables);

    bool success = data.at("commentDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete comment " + id);
    }
}

}  // namespace comments_api
