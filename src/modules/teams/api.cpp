#include "modules/teams/api.h"

#include <string>
#include <vector>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query strings
// ---------------------------------------------------------------------------

static const std::string TEAMS_LIST_QUERY = R"gql(
query TeamsList($first: Int, $after: String) {
    teams(first: $first, after: $after) {
        nodes {
            id name key description icon color timezone
            displayName cyclesEnabled triageEnabled private
            issueCount cycleStartDay cycleDuration cycleCooldownTime
            issueEstimationType createdAt updatedAt
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string TEAM_GET_QUERY = R"gql(
query TeamGet($id: String!) {
    team(id: $id) {
        id name key description icon color timezone
        displayName cyclesEnabled triageEnabled private
        issueCount cycleStartDay cycleDuration cycleCooldownTime
        issueEstimationType createdAt updatedAt
    }
}
)gql";

static const std::string WORKFLOW_STATES_QUERY = R"gql(
query WorkflowStates($teamId: ID!) {
    workflowStates(filter: { team: { id: { eq: $teamId } } }) {
        nodes {
            id name color description position type createdAt
            team { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string TEAM_MEMBERS_QUERY = R"gql(
query TeamMembers($id: String!) {
    team(id: $id) {
        members {
            nodes {
                id displayName email admin active
            }
        }
    }
}
)gql";

static const std::string TEAM_LABELS_QUERY = R"gql(
query TeamLabels($id: String!) {
    team(id: $id) {
        labels {
            nodes {
                id name color description
                parent { id name }
            }
        }
    }
}
)gql";

static const std::string TEAM_CYCLES_QUERY = R"gql(
query TeamCycles($id: String!) {
    team(id: $id) {
        cycles {
            nodes {
                id number name startsAt endsAt progress
                inProgressIssueCountHistory
                issues { nodes { id } }
                completedIssues { nodes { id } }
            }
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
// TeamMember parsing (local helper, not in model.h since it's API-internal)
// ---------------------------------------------------------------------------

static TeamMember parse_member(const json& j) {
    TeamMember m;
    m.id = j.value("id", "");
    m.display_name = j.value("displayName", "");
    m.email = j.value("email", "");

    auto safe_bool = [&](const char* key) -> bool {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<bool>();
        return false;
    };
    m.admin = safe_bool("admin");
    m.active = safe_bool("active");
    return m;
}

static TeamLabel parse_label(const json& j) {
    TeamLabel l;
    l.id = j.value("id", "");
    l.name = j.value("name", "");
    l.color = j.value("color", "");

    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return std::nullopt;
    };
    l.description = opt_str("description");

    if (j.contains("parent") && !j["parent"].is_null()) {
        const auto& p = j["parent"];
        l.parent_id = p.value("id", "");
        l.parent_name = p.value("name", "");
    }
    return l;
}

static TeamCycle parse_cycle(const json& j) {
    TeamCycle c;
    c.id = j.value("id", "");

    if (j.contains("number") && !j["number"].is_null()) {
        c.number = j["number"].get<int>();
    }
    if (j.contains("name") && !j["name"].is_null()) {
        c.name = j["name"].get<std::string>();
    }

    c.starts_at = j.value("startsAt", "");
    c.ends_at = j.value("endsAt", "");

    if (j.contains("progress") && !j["progress"].is_null()) {
        c.progress = j["progress"].get<double>();
    }

    // Count issues and completed issues from nodes arrays
    if (j.contains("issues") && !j["issues"].is_null()) {
        const auto& issues = j["issues"];
        if (issues.contains("nodes") && issues["nodes"].is_array()) {
            c.issue_count = static_cast<int>(issues["nodes"].size());
        }
    }
    if (j.contains("completedIssues") && !j["completedIssues"].is_null()) {
        const auto& completed = j["completedIssues"];
        if (completed.contains("nodes") && completed["nodes"].is_array()) {
            c.completed_issue_count = static_cast<int>(completed["nodes"].size());
        }
    }

    return c;
}

// ---------------------------------------------------------------------------
// API implementations
// ---------------------------------------------------------------------------

namespace teams_api {

Connection<Team> list_teams(int first, const std::optional<std::string>& after) {
    json variables = json::object();
    variables["first"] = first;
    if (after.has_value()) {
        variables["after"] = after.value();
    }

    auto data = execute_graphql(TEAMS_LIST_QUERY, variables);

    Connection<Team> result;
    from_json(data.at("teams"), result);
    return result;
}

Team get_team(const std::string& id_or_key) {
    json variables = json::object();
    variables["id"] = id_or_key;

    auto data = execute_graphql(TEAM_GET_QUERY, variables);

    Team team;
    from_json(data.at("team"), team);
    return team;
}

Connection<WorkflowState> list_workflow_states(const std::string& team_id) {
    json variables = json::object();
    variables["teamId"] = team_id;

    auto data = execute_graphql(WORKFLOW_STATES_QUERY, variables);

    Connection<WorkflowState> result;
    from_json(data.at("workflowStates"), result);
    return result;
}

std::vector<TeamMember> list_members(const std::string& team_id) {
    json variables = json::object();
    variables["id"] = team_id;

    auto data = execute_graphql(TEAM_MEMBERS_QUERY, variables);

    std::vector<TeamMember> members;
    const auto& team_node = data.at("team");
    if (team_node.contains("members") && !team_node["members"].is_null()) {
        const auto& members_conn = team_node["members"];
        if (members_conn.contains("nodes") && members_conn["nodes"].is_array()) {
            for (const auto& m : members_conn["nodes"]) {
                members.push_back(parse_member(m));
            }
        }
    }
    return members;
}

std::vector<TeamLabel> list_labels(const std::string& team_id) {
    json variables = json::object();
    variables["id"] = team_id;

    auto data = execute_graphql(TEAM_LABELS_QUERY, variables);

    std::vector<TeamLabel> labels;
    const auto& team_node = data.at("team");
    if (team_node.contains("labels") && !team_node["labels"].is_null()) {
        const auto& labels_conn = team_node["labels"];
        if (labels_conn.contains("nodes") && labels_conn["nodes"].is_array()) {
            for (const auto& l : labels_conn["nodes"]) {
                labels.push_back(parse_label(l));
            }
        }
    }
    return labels;
}

std::vector<TeamCycle> list_cycles(const std::string& team_id) {
    json variables = json::object();
    variables["id"] = team_id;

    auto data = execute_graphql(TEAM_CYCLES_QUERY, variables);

    std::vector<TeamCycle> cycles;
    const auto& team_node = data.at("team");
    if (team_node.contains("cycles") && !team_node["cycles"].is_null()) {
        const auto& cycles_conn = team_node["cycles"];
        if (cycles_conn.contains("nodes") && cycles_conn["nodes"].is_array()) {
            for (const auto& c : cycles_conn["nodes"]) {
                cycles.push_back(parse_cycle(c));
            }
        }
    }
    return cycles;
}

}  // namespace teams_api
