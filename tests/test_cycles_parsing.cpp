#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/cycles/model.h"

using json = nlohmann::json;

TEST(CycleModel, ParsesMinimalCycle) {
    auto j = json::parse(R"({
        "id": "cycle-001",
        "number": 3,
        "startsAt": "2026-03-01T00:00:00Z",
        "endsAt": "2026-03-14T00:00:00Z",
        "progress": 0.0,
        "isActive": false,
        "isFuture": false,
        "isPast": false,
        "isNext": false,
        "isPrevious": false
    })");

    Cycle c;
    from_json(j, c);

    EXPECT_EQ(c.id, "cycle-001");
    EXPECT_EQ(c.number, 3.0);
    EXPECT_EQ(c.starts_at, "2026-03-01T00:00:00Z");
    EXPECT_EQ(c.ends_at, "2026-03-14T00:00:00Z");
    EXPECT_EQ(c.progress, 0.0);
    EXPECT_FALSE(c.is_active);
    EXPECT_FALSE(c.is_future);
    EXPECT_FALSE(c.is_past);
    EXPECT_FALSE(c.is_next);
    EXPECT_FALSE(c.is_previous);
    EXPECT_EQ(c.name, std::nullopt);
    EXPECT_EQ(c.description, std::nullopt);
    EXPECT_EQ(c.completed_at, std::nullopt);
    EXPECT_EQ(c.team_id, std::nullopt);
    EXPECT_EQ(c.team_name, std::nullopt);
}

TEST(CycleModel, ParsesFullCycle) {
    auto j = json::parse(R"({
        "id": "cycle-002",
        "number": 7,
        "name": "Sprint 7",
        "description": "Focus on performance improvements",
        "startsAt": "2026-04-01T00:00:00Z",
        "endsAt": "2026-04-14T00:00:00Z",
        "completedAt": "2026-04-14T18:00:00Z",
        "createdAt": "2026-03-28T10:00:00Z",
        "updatedAt": "2026-04-14T18:00:00Z",
        "progress": 0.85,
        "isActive": false,
        "isFuture": false,
        "isPast": true,
        "isNext": false,
        "isPrevious": true,
        "team": { "id": "team-eng", "name": "Engineering" }
    })");

    Cycle c;
    from_json(j, c);

    EXPECT_EQ(c.id, "cycle-002");
    EXPECT_EQ(c.number, 7.0);
    EXPECT_EQ(c.name, "Sprint 7");
    EXPECT_EQ(c.description, "Focus on performance improvements");
    EXPECT_EQ(c.starts_at, "2026-04-01T00:00:00Z");
    EXPECT_EQ(c.ends_at, "2026-04-14T00:00:00Z");
    EXPECT_EQ(c.completed_at, "2026-04-14T18:00:00Z");
    EXPECT_EQ(c.created_at, "2026-03-28T10:00:00Z");
    EXPECT_EQ(c.updated_at, "2026-04-14T18:00:00Z");
    EXPECT_DOUBLE_EQ(c.progress, 0.85);
    EXPECT_FALSE(c.is_active);
    EXPECT_TRUE(c.is_past);
    EXPECT_TRUE(c.is_previous);
    EXPECT_FALSE(c.is_next);
    EXPECT_EQ(c.team_id, "team-eng");
    EXPECT_EQ(c.team_name, "Engineering");
}

TEST(CycleModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "cycle-003",
        "number": 1,
        "name": null,
        "description": null,
        "startsAt": "2026-01-01T00:00:00Z",
        "endsAt": "2026-01-14T00:00:00Z",
        "completedAt": null,
        "progress": 0.0,
        "isActive": false,
        "isFuture": false,
        "isPast": false,
        "isNext": false,
        "isPrevious": false,
        "team": null
    })");

    Cycle c;
    from_json(j, c);

    EXPECT_EQ(c.id, "cycle-003");
    EXPECT_EQ(c.name, std::nullopt);
    EXPECT_EQ(c.description, std::nullopt);
    EXPECT_EQ(c.completed_at, std::nullopt);
    EXPECT_EQ(c.team_id, std::nullopt);
    EXPECT_EQ(c.team_name, std::nullopt);
}

TEST(CycleModel, ParsesActiveCycle) {
    auto j = json::parse(R"({
        "id": "cycle-004",
        "number": 12,
        "name": "Current Sprint",
        "description": null,
        "startsAt": "2026-02-17T00:00:00Z",
        "endsAt": "2026-03-02T00:00:00Z",
        "completedAt": null,
        "createdAt": "2026-02-14T09:00:00Z",
        "updatedAt": "2026-02-26T15:30:00Z",
        "progress": 0.6,
        "isActive": true,
        "isFuture": false,
        "isPast": false,
        "isNext": false,
        "isPrevious": false,
        "team": { "id": "team-eng", "name": "Engineering" }
    })");

    Cycle c;
    from_json(j, c);

    EXPECT_EQ(c.id, "cycle-004");
    EXPECT_EQ(c.number, 12.0);
    EXPECT_EQ(c.name, "Current Sprint");
    EXPECT_TRUE(c.is_active);
    EXPECT_FALSE(c.is_future);
    EXPECT_FALSE(c.is_past);
    EXPECT_FALSE(c.is_next);
    EXPECT_FALSE(c.is_previous);
    EXPECT_DOUBLE_EQ(c.progress, 0.6);
    EXPECT_EQ(c.completed_at, std::nullopt);
    EXPECT_EQ(c.team_id, "team-eng");
    EXPECT_EQ(c.team_name, "Engineering");
}
