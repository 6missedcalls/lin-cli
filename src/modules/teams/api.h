#pragma once

#include <optional>
#include <string>
#include <vector>

#include "core/types.h"
#include "modules/teams/model.h"

struct TeamMember {
    std::string id;
    std::string display_name;
    std::string email;
    bool admin = false;
    bool active = false;
};

struct TeamLabel {
    std::string id;
    std::string name;
    std::string color;
    std::optional<std::string> description;
    std::optional<std::string> parent_id;
    std::optional<std::string> parent_name;
};

struct TeamCycle {
    std::string id;
    int number = 0;
    std::optional<std::string> name;
    std::string starts_at;
    std::string ends_at;
    double progress = 0.0;
    bool is_active = false;
    int issue_count = 0;
    int completed_issue_count = 0;
};

namespace teams_api {

// List all teams in the workspace
Connection<Team> list_teams(int first = 50, const std::optional<std::string>& after = std::nullopt);

// Get a single team by ID or key
Team get_team(const std::string& id_or_key);

// Resolve a team name, key, or ID to a team ID.
// Tries get_team(input) first (works for ID/key), then falls back
// to searching by display name across all teams.
std::string resolve_team_id(const std::string& input);

// Resolve a state name or ID to a workflow state UUID.
// If the input looks like a UUID, returns it as-is.
// Otherwise searches workflow states by name (case-insensitive) within the team.
std::string resolve_state_id(const std::string& team_id, const std::string& input);

// List workflow states for a team
Connection<WorkflowState> list_workflow_states(const std::string& team_id);

// List members of a team
std::vector<TeamMember> list_members(const std::string& team_id);

// List labels for a team
std::vector<TeamLabel> list_labels(const std::string& team_id);

// List cycles for a team
std::vector<TeamCycle> list_cycles(const std::string& team_id);

}  // namespace teams_api
