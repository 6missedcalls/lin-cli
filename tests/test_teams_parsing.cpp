#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/teams/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Team parsing tests
// ---------------------------------------------------------------------------

TEST(TeamModel, ParsesMinimalTeam) {
    auto j = json::parse(R"({
        "id": "team-abc",
        "name": "Engineering",
        "key": "ENG"
    })");

    Team team;
    from_json(j, team);

    EXPECT_EQ(team.id, "team-abc");
    EXPECT_EQ(team.name, "Engineering");
    EXPECT_EQ(team.key, "ENG");
    EXPECT_EQ(team.description, std::nullopt);
    EXPECT_EQ(team.icon, std::nullopt);
    EXPECT_EQ(team.color, std::nullopt);
    EXPECT_EQ(team.timezone, std::nullopt);
    EXPECT_EQ(team.cycles_enabled, false);
    EXPECT_EQ(team.triage_enabled, false);
    EXPECT_EQ(team.private_team, false);
    EXPECT_EQ(team.issue_count, 0);
}

TEST(TeamModel, ParsesFullTeam) {
    auto j = json::parse(R"({
        "id": "team-xyz",
        "name": "Product",
        "key": "PROD",
        "description": "Product team",
        "icon": "star",
        "color": "#FF0000",
        "timezone": "America/New_York",
        "displayName": "Product Team",
        "cyclesEnabled": true,
        "triageEnabled": true,
        "private": true,
        "issueCount": 42,
        "cycleDuration": 2,
        "cycleCooldownTime": 1,
        "cycleStartDay": 1,
        "issueEstimationType": "fibonacci",
        "createdAt": "2025-01-01T00:00:00Z",
        "updatedAt": "2026-01-01T00:00:00Z"
    })");

    Team team;
    from_json(j, team);

    EXPECT_EQ(team.id, "team-xyz");
    EXPECT_EQ(team.name, "Product");
    EXPECT_EQ(team.key, "PROD");
    EXPECT_EQ(team.description, "Product team");
    EXPECT_EQ(team.icon, "star");
    EXPECT_EQ(team.color, "#FF0000");
    EXPECT_EQ(team.timezone, "America/New_York");
    EXPECT_EQ(team.display_name, "Product Team");
    EXPECT_EQ(team.cycles_enabled, true);
    EXPECT_EQ(team.triage_enabled, true);
    EXPECT_EQ(team.private_team, true);
    EXPECT_EQ(team.issue_count, 42);
    EXPECT_EQ(team.cycle_duration, 2.0);
    EXPECT_EQ(team.cycle_cooldown_time, 1.0);
    EXPECT_EQ(team.cycle_start_day, 1.0);
    EXPECT_EQ(team.issue_estimation_type, "fibonacci");
    EXPECT_EQ(team.created_at, "2025-01-01T00:00:00Z");
    EXPECT_EQ(team.updated_at, "2026-01-01T00:00:00Z");
}

TEST(TeamModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "team-null",
        "name": "Nulls Team",
        "key": "NULL",
        "description": null,
        "icon": null,
        "color": null,
        "timezone": null,
        "cyclesEnabled": null,
        "triageEnabled": null,
        "private": null,
        "issueCount": null,
        "cycleDuration": null,
        "cycleCooldownTime": null,
        "cycleStartDay": null
    })");

    Team team;
    from_json(j, team);

    EXPECT_EQ(team.id, "team-null");
    EXPECT_EQ(team.description, std::nullopt);
    EXPECT_EQ(team.icon, std::nullopt);
    EXPECT_EQ(team.color, std::nullopt);
    EXPECT_EQ(team.timezone, std::nullopt);
    EXPECT_EQ(team.cycles_enabled, false);
    EXPECT_EQ(team.triage_enabled, false);
    EXPECT_EQ(team.private_team, false);
    EXPECT_EQ(team.issue_count, 0);
    EXPECT_EQ(team.cycle_duration, 0.0);
    EXPECT_EQ(team.cycle_cooldown_time, 0.0);
    EXPECT_EQ(team.cycle_start_day, 0.0);
}

// ---------------------------------------------------------------------------
// WorkflowState parsing tests
// ---------------------------------------------------------------------------

TEST(WorkflowStateModel, ParsesWorkflowState) {
    auto j = json::parse(R"({
        "id": "state-1",
        "name": "In Progress",
        "color": "#FFFF00",
        "description": "Active work",
        "position": 3.0,
        "type": "started",
        "createdAt": "2025-06-01T00:00:00Z",
        "team": { "id": "team-1", "name": "Engineering" }
    })");

    WorkflowState state;
    from_json(j, state);

    EXPECT_EQ(state.id, "state-1");
    EXPECT_EQ(state.name, "In Progress");
    EXPECT_EQ(state.color, "#FFFF00");
    EXPECT_EQ(state.description, "Active work");
    EXPECT_EQ(state.position, 3.0);
    EXPECT_EQ(state.type, "started");
    EXPECT_EQ(state.created_at, "2025-06-01T00:00:00Z");
    EXPECT_EQ(state.team_id, "team-1");
    EXPECT_EQ(state.team_name, "Engineering");
}

TEST(WorkflowStateModel, HandlesNullTeamAndDescription) {
    auto j = json::parse(R"({
        "id": "state-2",
        "name": "Backlog",
        "color": "#CCCCCC",
        "description": null,
        "position": 0.0,
        "type": "backlog",
        "createdAt": "2025-01-01T00:00:00Z",
        "team": null
    })");

    WorkflowState state;
    from_json(j, state);

    EXPECT_EQ(state.id, "state-2");
    EXPECT_EQ(state.name, "Backlog");
    EXPECT_EQ(state.description, std::nullopt);
    EXPECT_EQ(state.team_id, std::nullopt);
    EXPECT_EQ(state.team_name, std::nullopt);
    EXPECT_EQ(state.type, "backlog");
    EXPECT_EQ(state.position, 0.0);
}
