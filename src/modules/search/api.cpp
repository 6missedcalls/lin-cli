#include "modules/search/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query strings
// ---------------------------------------------------------------------------

static const std::string SEMANTIC_SEARCH_QUERY = R"gql(
query SemanticSearch($query: String!, $limit: Int) {
    searchDocuments(term: $query, first: $limit) {
        nodes {
            id title slugId url
            creator { id displayName }
            project { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
    searchIssues(term: $query, first: $limit) {
        nodes {
            id identifier title priority priorityLabel
            url branchName createdAt updatedAt
            state { id name type }
            assignee { id displayName }
            team { id name key }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string SEARCH_ISSUES_QUERY = R"gql(
query SearchIssues($term: String!, $filter: IssueFilter, $first: Int) {
    searchIssues(term: $term, filter: $filter, first: $first) {
        nodes {
            id identifier title priority priorityLabel
            url branchName createdAt updatedAt
            state { id name type }
            assignee { id displayName }
            team { id name key }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string SEARCH_PROJECTS_QUERY = R"gql(
query SearchProjects($term: String!, $first: Int) {
    projectSearch(term: $term, first: $first) {
        nodes {
            id name slugId url
            priority priorityLabel
            progress health
            status { id name type }
            lead { id displayName }
            createdAt updatedAt
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string SEARCH_DOCUMENTS_QUERY = R"gql(
query SearchDocuments($term: String!, $first: Int) {
    searchDocuments(term: $term, first: $first) {
        nodes {
            id title slugId url
            createdAt updatedAt
            creator { id displayName }
            project { id name }
        }
        pageInfo { hasNextPage endCursor }
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

namespace search_api {

json search_all(const std::string& query, int limit) {
    json variables = json::object();
    variables["query"] = query;
    variables["limit"] = limit;

    return execute_graphql(SEMANTIC_SEARCH_QUERY, variables);
}

json search_issues(
    const std::string& term,
    const std::optional<std::string>& team_key,
    int limit
) {
    json variables = json::object();
    variables["term"] = term;
    variables["first"] = limit;

    if (team_key.has_value()) {
        json filter = json::object();
        json team_filter = json::object();
        team_filter["key"] = json::object({{"eq", team_key.value()}});
        filter["team"] = team_filter;
        variables["filter"] = filter;
    }

    return execute_graphql(SEARCH_ISSUES_QUERY, variables);
}

json search_projects(const std::string& term, int limit) {
    json variables = json::object();
    variables["term"] = term;
    variables["first"] = limit;

    return execute_graphql(SEARCH_PROJECTS_QUERY, variables);
}

json search_documents(const std::string& term, int limit) {
    json variables = json::object();
    variables["term"] = term;
    variables["first"] = limit;

    return execute_graphql(SEARCH_DOCUMENTS_QUERY, variables);
}

}  // namespace search_api
