#include "modules/projects/api.h"

#include <string>
#include <vector>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string PROJECTS_LIST_QUERY = R"gql(
query ProjectsList($first: Int, $after: String, $filter: ProjectFilter) {
    projects(first: $first, after: $after, filter: $filter) {
        nodes {
            id name slugId url createdAt updatedAt trashed
            description icon color priority priorityLabel
            progress scope health healthUpdatedAt
            startDate targetDate startedAt completedAt canceledAt
            status { id name type }
            lead { id displayName }
            creator { id displayName }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string PROJECT_GET_QUERY = R"gql(
query ProjectGet($id: String!) {
    project(id: $id) {
        id name slugId url createdAt updatedAt trashed
        description icon color priority priorityLabel
        progress scope health healthUpdatedAt
        startDate targetDate startedAt completedAt canceledAt
        status { id name type }
        lead { id displayName }
        creator { id displayName }
    }
}
)gql";

static const std::string SEARCH_PROJECTS_QUERY = R"gql(
query SearchProjects($term: String!, $first: Int) {
    searchProjects(term: $term, first: $first) {
        nodes {
            id name slugId url createdAt updatedAt trashed
            priority priorityLabel progress scope health
            startDate targetDate
            status { id name type }
            lead { id displayName }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string PROJECT_CREATE_MUTATION = R"gql(
mutation ProjectCreate($input: ProjectCreateInput!) {
    projectCreate(input: $input) {
        project {
            id name slugId url createdAt updatedAt trashed
            description icon color priority priorityLabel
            progress scope health
            startDate targetDate
            status { id name type }
            lead { id displayName }
            creator { id displayName }
        }
    }
}
)gql";

static const std::string PROJECT_UPDATE_MUTATION = R"gql(
mutation ProjectUpdate($id: String!, $input: ProjectUpdateInput!) {
    projectUpdate(id: $id, input: $input) {
        project {
            id name slugId url createdAt updatedAt trashed
            description icon color priority priorityLabel
            progress scope health
            startDate targetDate
            status { id name type }
            lead { id displayName }
            creator { id displayName }
        }
    }
}
)gql";

static const std::string PROJECT_DELETE_MUTATION = R"gql(
mutation ProjectDelete($id: String!) {
    projectDelete(id: $id) { success }
}
)gql";

static const std::string PROJECT_MILESTONES_QUERY = R"gql(
query ProjectMilestones($projectId: ID!, $first: Int) {
    projectMilestones(filter: { project: { id: { eq: $projectId } } }, first: $first) {
        nodes {
            id name createdAt updatedAt description
            targetDate status progress sortOrder
            project { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string PROJECT_MILESTONE_CREATE_MUTATION = R"gql(
mutation ProjectMilestoneCreate($input: ProjectMilestoneCreateInput!) {
    projectMilestoneCreate(input: $input) {
        projectMilestone {
            id name createdAt updatedAt description
            targetDate status progress sortOrder
            project { id name }
        }
    }
}
)gql";

static const std::string PROJECT_MILESTONE_UPDATE_MUTATION = R"gql(
mutation ProjectMilestoneUpdate($id: String!, $input: ProjectMilestoneUpdateInput!) {
    projectMilestoneUpdate(id: $id, input: $input) {
        projectMilestone {
            id name createdAt updatedAt description
            targetDate status progress sortOrder
            project { id name }
        }
    }
}
)gql";

static const std::string PROJECT_MILESTONE_DELETE_MUTATION = R"gql(
mutation ProjectMilestoneDelete($id: String!) {
    projectMilestoneDelete(id: $id) { success }
}
)gql";

static const std::string PROJECT_UPDATES_QUERY = R"gql(
query ProjectUpdates($projectId: ID!, $first: Int) {
    projectUpdates(filter: { project: { id: { eq: $projectId } } }, first: $first) {
        nodes {
            id body url slugId createdAt updatedAt health diffMarkdown
            user { id displayName }
            project { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string PROJECT_UPDATE_CREATE_MUTATION = R"gql(
mutation ProjectUpdateCreate($input: ProjectUpdateCreateInput!) {
    projectUpdateCreate(input: $input) {
        projectUpdate {
            id body url slugId createdAt updatedAt health diffMarkdown
            user { id displayName }
            project { id name }
        }
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

namespace projects_api {

Connection<Project> list_projects(const ProjectListOptions& opts) {
    json variables = json::object();
    variables["first"] = opts.first;

    if (opts.after.has_value()) {
        variables["after"] = opts.after.value();
    }
    if (!opts.filter.is_null()) {
        variables["filter"] = opts.filter;
    }

    auto data = execute_graphql(PROJECTS_LIST_QUERY, variables);

    Connection<Project> result;
    from_json(data.at("projects"), result);
    return result;
}

Project get_project(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(PROJECT_GET_QUERY, variables);

    Project project;
    from_json(data.at("project"), project);
    return project;
}

Connection<Project> search_projects(const std::string& term, int limit) {
    json variables = json::object();
    variables["term"] = term;
    variables["first"] = limit;

    auto data = execute_graphql(SEARCH_PROJECTS_QUERY, variables);

    Connection<Project> result;
    from_json(data.at("searchProjects"), result);
    return result;
}

Project create_project(const ProjectCreateInput& input) {
    json project_input = json::object();
    project_input["name"] = input.name;

    if (input.description.has_value()) {
        project_input["description"] = input.description.value();
    }
    if (input.icon.has_value()) {
        project_input["icon"] = input.icon.value();
    }
    if (input.color.has_value()) {
        project_input["color"] = input.color.value();
    }
    if (input.lead_id.has_value()) {
        project_input["leadId"] = input.lead_id.value();
    }
    if (input.status_id.has_value()) {
        project_input["statusId"] = input.status_id.value();
    }
    if (input.priority.has_value()) {
        project_input["priority"] = input.priority.value();
    }
    if (input.start_date.has_value()) {
        project_input["startDate"] = input.start_date.value();
    }
    if (input.target_date.has_value()) {
        project_input["targetDate"] = input.target_date.value();
    }
    if (!input.member_ids.empty()) {
        project_input["memberIds"] = input.member_ids;
    }
    if (!input.team_ids.empty()) {
        project_input["teamIds"] = input.team_ids;
    }

    json variables = json::object();
    variables["input"] = project_input;

    auto data = execute_graphql(PROJECT_CREATE_MUTATION, variables);

    Project project;
    from_json(data.at("projectCreate").at("project"), project);
    return project;
}

Project update_project(const std::string& id, const ProjectUpdateInput& input) {
    json project_input = json::object();

    if (input.name.has_value()) {
        project_input["name"] = input.name.value();
    }
    if (input.description.has_value()) {
        project_input["description"] = input.description.value();
    }
    if (input.icon.has_value()) {
        project_input["icon"] = input.icon.value();
    }
    if (input.color.has_value()) {
        project_input["color"] = input.color.value();
    }
    if (input.lead_id.has_value()) {
        project_input["leadId"] = input.lead_id.value();
    }
    if (input.status_id.has_value()) {
        project_input["statusId"] = input.status_id.value();
    }
    if (input.priority.has_value()) {
        project_input["priority"] = input.priority.value();
    }
    if (input.start_date.has_value()) {
        project_input["startDate"] = input.start_date.value();
    }
    if (input.target_date.has_value()) {
        project_input["targetDate"] = input.target_date.value();
    }
    if (input.health.has_value()) {
        project_input["health"] = input.health.value();
    }

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = project_input;

    auto data = execute_graphql(PROJECT_UPDATE_MUTATION, variables);

    Project project;
    from_json(data.at("projectUpdate").at("project"), project);
    return project;
}

void delete_project(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(PROJECT_DELETE_MUTATION, variables);

    bool success = data.at("projectDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete project " + id);
    }
}

Connection<ProjectMilestone> list_milestones(const std::string& project_id) {
    json variables = json::object();
    variables["projectId"] = project_id;
    variables["first"] = 100;

    auto data = execute_graphql(PROJECT_MILESTONES_QUERY, variables);

    Connection<ProjectMilestone> result;
    from_json(data.at("projectMilestones"), result);
    return result;
}

ProjectMilestone create_milestone(const ProjectMilestoneCreateInput& input) {
    json milestone_input = json::object();
    milestone_input["projectId"] = input.project_id;
    milestone_input["name"] = input.name;

    if (input.description.has_value()) {
        milestone_input["description"] = input.description.value();
    }
    if (input.target_date.has_value()) {
        milestone_input["targetDate"] = input.target_date.value();
    }
    if (input.sort_order.has_value()) {
        milestone_input["sortOrder"] = input.sort_order.value();
    }

    json variables = json::object();
    variables["input"] = milestone_input;

    auto data = execute_graphql(PROJECT_MILESTONE_CREATE_MUTATION, variables);

    ProjectMilestone milestone;
    from_json(data.at("projectMilestoneCreate").at("projectMilestone"), milestone);
    return milestone;
}

ProjectMilestone update_milestone(const std::string& id, const ProjectMilestoneUpdateInput& input) {
    json milestone_input = json::object();

    if (input.name.has_value()) {
        milestone_input["name"] = input.name.value();
    }
    if (input.description.has_value()) {
        milestone_input["description"] = input.description.value();
    }
    if (input.target_date.has_value()) {
        milestone_input["targetDate"] = input.target_date.value();
    }
    if (input.sort_order.has_value()) {
        milestone_input["sortOrder"] = input.sort_order.value();
    }

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = milestone_input;

    auto data = execute_graphql(PROJECT_MILESTONE_UPDATE_MUTATION, variables);

    ProjectMilestone milestone;
    from_json(data.at("projectMilestoneUpdate").at("projectMilestone"), milestone);
    return milestone;
}

void delete_milestone(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(PROJECT_MILESTONE_DELETE_MUTATION, variables);

    bool success = data.at("projectMilestoneDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete milestone " + id);
    }
}

Connection<ProjectUpdate> list_updates(const std::string& project_id) {
    json variables = json::object();
    variables["projectId"] = project_id;
    variables["first"] = 50;

    auto data = execute_graphql(PROJECT_UPDATES_QUERY, variables);

    Connection<ProjectUpdate> result;
    from_json(data.at("projectUpdates"), result);
    return result;
}

ProjectUpdate create_update(const ProjectUpdateCreateInput& input) {
    json update_input = json::object();
    update_input["projectId"] = input.project_id;
    update_input["body"] = input.body;

    if (input.health.has_value()) {
        update_input["health"] = input.health.value();
    }

    json variables = json::object();
    variables["input"] = update_input;

    auto data = execute_graphql(PROJECT_UPDATE_CREATE_MUTATION, variables);

    ProjectUpdate update;
    from_json(data.at("projectUpdateCreate").at("projectUpdate"), update);
    return update;
}

}  // namespace projects_api
