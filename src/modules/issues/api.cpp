#include "modules/issues/api.h"

#include <string>
#include <utility>
#include <vector>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string ISSUES_LIST_QUERY = R"gql(
query IssuesList($first: Int, $after: String, $filter: IssueFilter, $orderBy: PaginationOrderBy) {
    issues(first: $first, after: $after, filter: $filter, orderBy: $orderBy) {
        nodes {
            id identifier title number priority priorityLabel
            url branchName createdAt updatedAt trashed
            description dueDate estimate
            state { id name type }
            assignee { id displayName }
            team { id name key }
            labels { nodes { id name color } }
            project { id name }
            cycle { id number }
            parent { id identifier }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string ISSUE_GET_QUERY = R"gql(
query IssueGet($id: String!) {
    issue(id: $id) {
        id identifier title number priority priorityLabel
        url branchName createdAt updatedAt archivedAt trashed
        description dueDate startedAt completedAt canceledAt estimate
        state { id name type }
        assignee { id displayName }
        creator { id displayName }
        team { id name key }
        labels { nodes { id name color } }
        project { id name }
        cycle { id number }
        parent { id identifier }
    }
}
)gql";

static const std::string SEARCH_ISSUES_QUERY = R"gql(
query SearchIssues($term: String!, $filter: IssueFilter, $includeComments: Boolean, $first: Int) {
    searchIssues(term: $term, filter: $filter, includeComments: $includeComments, first: $first) {
        nodes {
            id identifier title number priority priorityLabel
            url branchName createdAt updatedAt trashed
            state { id name type }
            assignee { id displayName }
            team { id name key }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string ISSUE_CREATE_MUTATION = R"gql(
mutation IssueCreate($input: IssueCreateInput!) {
    issueCreate(input: $input) {
        issue {
            id identifier title number priority priorityLabel
            url branchName createdAt updatedAt
            state { id name type }
            assignee { id displayName }
            team { id name key }
        }
    }
}
)gql";

static const std::string ISSUE_UPDATE_MUTATION = R"gql(
mutation IssueUpdate($id: String!, $input: IssueUpdateInput!) {
    issueUpdate(id: $id, input: $input) {
        issue {
            id identifier title number priority priorityLabel
            url branchName createdAt updatedAt
            state { id name type }
            assignee { id displayName }
            team { id name key }
        }
    }
}
)gql";

static const std::string ISSUE_DELETE_MUTATION = R"gql(
mutation IssueDelete($id: String!, $permanentlyDelete: Boolean) {
    issueDelete(id: $id, permanentlyDelete: $permanentlyDelete) { success }
}
)gql";

static const std::string ISSUE_ARCHIVE_MUTATION = R"gql(
mutation IssueArchive($id: String!) {
    issueArchive(id: $id) { success }
}
)gql";

static const std::string ISSUE_UNARCHIVE_MUTATION = R"gql(
mutation IssueUnarchive($id: String!) {
    issueUnarchive(id: $id) { success }
}
)gql";

static const std::string ISSUE_ADD_LABEL_MUTATION = R"gql(
mutation IssueAddLabel($id: String!, $labelId: String!) {
    issueAddLabel(id: $id, labelId: $labelId) { success }
}
)gql";

static const std::string ISSUE_REMOVE_LABEL_MUTATION = R"gql(
mutation IssueRemoveLabel($id: String!, $labelId: String!) {
    issueRemoveLabel(id: $id, labelId: $labelId) { success }
}
)gql";

static const std::string ISSUE_SUBSCRIBE_MUTATION = R"gql(
mutation IssueSubscribe($id: String!) {
    issueSubscribe(id: $id) { success }
}
)gql";

static const std::string ISSUE_UNSUBSCRIBE_MUTATION = R"gql(
mutation IssueUnsubscribe($id: String!) {
    issueUnsubscribe(id: $id) { success }
}
)gql";

static const std::string ISSUE_RELATION_CREATE_MUTATION = R"gql(
mutation IssueRelationCreate($input: IssueRelationCreateInput!) {
    issueRelationCreate(input: $input) {
        issueRelation {
            id type createdAt
            issue { id identifier }
            relatedIssue { id identifier }
        }
    }
}
)gql";

static const std::string ISSUE_RELATION_DELETE_MUTATION = R"gql(
mutation IssueRelationDelete($id: String!) {
    issueRelationDelete(id: $id) { success }
}
)gql";

static const std::string ISSUE_BATCH_UPDATE_MUTATION = R"gql(
mutation IssueBatchUpdate($ids: [UUID!]!, $input: IssueUpdateInput!) {
    issueBatchUpdate(ids: $ids, input: $input) { issues { id } }
}
)gql";

static const std::string VIEWER_QUERY = R"gql(
query Viewer {
    viewer { id name displayName email }
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

static json build_update_variables(const IssueUpdateInput& input) {
    json obj = json::object();

    if (input.title.has_value()) {
        obj["title"] = input.title.value();
    }
    if (input.description.has_value()) {
        obj["description"] = input.description.value();
    }
    if (input.assignee_id.has_value()) {
        obj["assigneeId"] = input.assignee_id.value();
    }
    if (input.priority.has_value()) {
        obj["priority"] = input.priority.value();
    }
    if (input.state_id.has_value()) {
        obj["stateId"] = input.state_id.value();
    }
    if (input.project_id.has_value()) {
        obj["projectId"] = input.project_id.value();
    }
    if (input.cycle_id.has_value()) {
        obj["cycleId"] = input.cycle_id.value();
    }
    if (input.parent_id.has_value()) {
        obj["parentId"] = input.parent_id.value();
    }
    if (input.estimate.has_value()) {
        obj["estimate"] = input.estimate.value();
    }
    if (input.due_date.has_value()) {
        obj["dueDate"] = input.due_date.value();
    }

    return obj;
}

// ---------------------------------------------------------------------------
// API implementations
// ---------------------------------------------------------------------------

namespace issues_api {

Connection<Issue> list_issues(const IssueListOptions& opts) {
    json variables = json::object();
    variables["first"] = opts.first;

    if (opts.after.has_value()) {
        variables["after"] = opts.after.value();
    }
    if (!opts.filter.is_null()) {
        variables["filter"] = opts.filter;
    }
    if (opts.order_by.has_value()) {
        variables["orderBy"] = opts.order_by.value();
    }

    auto data = execute_graphql(ISSUES_LIST_QUERY, variables);

    Connection<Issue> result;
    from_json(data.at("issues"), result);
    return result;
}

Issue get_issue(const std::string& id_or_identifier) {
    json variables = json::object();
    variables["id"] = id_or_identifier;

    auto data = execute_graphql(ISSUE_GET_QUERY, variables);

    Issue issue;
    from_json(data.at("issue"), issue);
    return issue;
}

Connection<Issue> search_issues(
    const std::string& term,
    const std::optional<std::string>& team_id,
    bool include_comments,
    int limit
) {
    json variables = json::object();
    variables["term"] = term;
    variables["includeComments"] = include_comments;
    variables["first"] = limit;

    if (team_id.has_value()) {
        json filter = json::object();
        json team_filter = json::object();
        team_filter["id"] = json::object({{"eq", team_id.value()}});
        filter["team"] = team_filter;
        variables["filter"] = filter;
    }

    auto data = execute_graphql(SEARCH_ISSUES_QUERY, variables);

    Connection<Issue> result;
    from_json(data.at("searchIssues"), result);
    return result;
}

Issue create_issue(const IssueCreateInput& input) {
    json issue_input = json::object();
    issue_input["title"] = input.title;
    issue_input["teamId"] = input.team_id;

    if (input.description.has_value()) {
        issue_input["description"] = input.description.value();
    }
    if (input.assignee_id.has_value()) {
        issue_input["assigneeId"] = input.assignee_id.value();
    }
    if (input.priority.has_value()) {
        issue_input["priority"] = input.priority.value();
    }
    if (input.state_id.has_value()) {
        issue_input["stateId"] = input.state_id.value();
    }
    if (input.project_id.has_value()) {
        issue_input["projectId"] = input.project_id.value();
    }
    if (input.cycle_id.has_value()) {
        issue_input["cycleId"] = input.cycle_id.value();
    }
    if (input.parent_id.has_value()) {
        issue_input["parentId"] = input.parent_id.value();
    }
    if (input.estimate.has_value()) {
        issue_input["estimate"] = input.estimate.value();
    }
    if (input.due_date.has_value()) {
        issue_input["dueDate"] = input.due_date.value();
    }
    if (!input.label_ids.empty()) {
        issue_input["labelIds"] = input.label_ids;
    }

    json variables = json::object();
    variables["input"] = issue_input;

    auto data = execute_graphql(ISSUE_CREATE_MUTATION, variables);

    Issue issue;
    from_json(data.at("issueCreate").at("issue"), issue);
    return issue;
}

Issue update_issue(const std::string& id, const IssueUpdateInput& input) {
    json variables = json::object();
    variables["id"] = id;
    variables["input"] = build_update_variables(input);

    auto data = execute_graphql(ISSUE_UPDATE_MUTATION, variables);

    Issue issue;
    from_json(data.at("issueUpdate").at("issue"), issue);
    return issue;
}

void delete_issue(const std::string& id, bool permanently) {
    json variables = json::object();
    variables["id"] = id;
    if (permanently) {
        variables["permanentlyDelete"] = true;
    }

    auto data = execute_graphql(ISSUE_DELETE_MUTATION, variables);

    bool success = data.at("issueDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete issue " + id);
    }
}

void archive_issue(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(ISSUE_ARCHIVE_MUTATION, variables);

    bool success = data.at("issueArchive").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to archive issue " + id);
    }
}

void unarchive_issue(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(ISSUE_UNARCHIVE_MUTATION, variables);

    bool success = data.at("issueUnarchive").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to unarchive issue " + id);
    }
}

void add_label(const std::string& issue_id, const std::string& label_id) {
    json variables = json::object();
    variables["id"] = issue_id;
    variables["labelId"] = label_id;

    auto data = execute_graphql(ISSUE_ADD_LABEL_MUTATION, variables);

    bool success = data.at("issueAddLabel").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to add label to issue " + issue_id);
    }
}

void remove_label(const std::string& issue_id, const std::string& label_id) {
    json variables = json::object();
    variables["id"] = issue_id;
    variables["labelId"] = label_id;

    auto data = execute_graphql(ISSUE_REMOVE_LABEL_MUTATION, variables);

    bool success = data.at("issueRemoveLabel").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to remove label from issue " + issue_id);
    }
}

void subscribe(const std::string& issue_id) {
    json variables = json::object();
    variables["id"] = issue_id;

    auto data = execute_graphql(ISSUE_SUBSCRIBE_MUTATION, variables);

    bool success = data.at("issueSubscribe").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to subscribe to issue " + issue_id);
    }
}

void unsubscribe(const std::string& issue_id) {
    json variables = json::object();
    variables["id"] = issue_id;

    auto data = execute_graphql(ISSUE_UNSUBSCRIBE_MUTATION, variables);

    bool success = data.at("issueUnsubscribe").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to unsubscribe from issue " + issue_id);
    }
}

IssueRelation create_relation(
    const std::string& issue_id,
    const std::string& related_id,
    const std::string& type
) {
    json relation_input = json::object();
    relation_input["issueId"] = issue_id;
    relation_input["relatedIssueId"] = related_id;
    relation_input["type"] = type;

    json variables = json::object();
    variables["input"] = relation_input;

    auto data = execute_graphql(ISSUE_RELATION_CREATE_MUTATION, variables);

    IssueRelation relation;
    from_json(data.at("issueRelationCreate").at("issueRelation"), relation);
    return relation;
}

void delete_relation(const std::string& relation_id) {
    json variables = json::object();
    variables["id"] = relation_id;

    auto data = execute_graphql(ISSUE_RELATION_DELETE_MUTATION, variables);

    bool success = data.at("issueRelationDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete relation " + relation_id);
    }
}

int bulk_update(const std::vector<std::string>& ids, const IssueUpdateInput& input) {
    if (ids.empty()) {
        return 0;
    }

    json variables = json::object();
    variables["ids"] = ids;
    variables["input"] = build_update_variables(input);

    auto data = execute_graphql(ISSUE_BATCH_UPDATE_MUTATION, variables);

    const auto& issues = data.at("issueBatchUpdate").at("issues");
    if (!issues.is_array()) {
        return 0;
    }
    return static_cast<int>(issues.size());
}

ViewerInfo get_viewer() {
    auto data = execute_graphql(VIEWER_QUERY, json::object());
    const auto& v = data.at("viewer");

    return ViewerInfo{
        v.at("id").get<std::string>(),
        v.value("name", ""),
        v.value("email", ""),
        v.value("displayName", "")
    };
}

}  // namespace issues_api
