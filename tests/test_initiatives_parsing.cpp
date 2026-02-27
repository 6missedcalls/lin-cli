#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/initiatives/model.h"

using json = nlohmann::json;

TEST(InitiativeModel, ParsesMinimalInitiative) {
    auto j = json::parse(R"({
        "id": "init-1",
        "name": "Platform Modernization"
    })");

    Initiative initiative;
    from_json(j, initiative);

    EXPECT_EQ(initiative.id, "init-1");
    EXPECT_EQ(initiative.name, "Platform Modernization");
    EXPECT_EQ(initiative.description, std::nullopt);
    EXPECT_EQ(initiative.icon, std::nullopt);
    EXPECT_EQ(initiative.color, std::nullopt);
    EXPECT_EQ(initiative.status, std::nullopt);
    EXPECT_EQ(initiative.health, std::nullopt);
    EXPECT_EQ(initiative.target_date, std::nullopt);
    EXPECT_EQ(initiative.owner_id, std::nullopt);
    EXPECT_EQ(initiative.owner_name, std::nullopt);
    EXPECT_EQ(initiative.started_at, std::nullopt);
    EXPECT_EQ(initiative.completed_at, std::nullopt);
    EXPECT_FALSE(initiative.trashed);
    EXPECT_EQ(initiative.slug_id, "");
    EXPECT_EQ(initiative.url, "");
    EXPECT_EQ(initiative.created_at, "");
    EXPECT_EQ(initiative.updated_at, "");
}

TEST(InitiativeModel, ParsesFullInitiative) {
    auto j = json::parse(R"({
        "id": "init-2",
        "name": "Q2 Infrastructure Overhaul",
        "description": "Migrate all services to new infra stack.",
        "icon": "rocket",
        "color": "#FF6B6B",
        "slugId": "q2-infra",
        "url": "https://linear.app/acme/initiative/q2-infra",
        "status": "Active",
        "health": "onTrack",
        "targetDate": "2026-06-30",
        "startedAt": "2026-01-15T00:00:00Z",
        "completedAt": null,
        "trashed": false,
        "createdAt": "2025-12-01T00:00:00Z",
        "updatedAt": "2026-02-10T00:00:00Z",
        "owner": { "id": "user-99", "displayName": "Alice Smith" }
    })");

    Initiative initiative;
    from_json(j, initiative);

    EXPECT_EQ(initiative.id, "init-2");
    EXPECT_EQ(initiative.name, "Q2 Infrastructure Overhaul");
    EXPECT_EQ(initiative.description, "Migrate all services to new infra stack.");
    EXPECT_EQ(initiative.icon, "rocket");
    EXPECT_EQ(initiative.color, "#FF6B6B");
    EXPECT_EQ(initiative.slug_id, "q2-infra");
    EXPECT_EQ(initiative.url, "https://linear.app/acme/initiative/q2-infra");
    EXPECT_EQ(initiative.status, "Active");
    EXPECT_EQ(initiative.health, "onTrack");
    EXPECT_EQ(initiative.target_date, "2026-06-30");
    EXPECT_EQ(initiative.started_at, "2026-01-15T00:00:00Z");
    EXPECT_EQ(initiative.completed_at, std::nullopt);
    EXPECT_FALSE(initiative.trashed);
    EXPECT_EQ(initiative.created_at, "2025-12-01T00:00:00Z");
    EXPECT_EQ(initiative.updated_at, "2026-02-10T00:00:00Z");
    EXPECT_EQ(initiative.owner_id, "user-99");
    EXPECT_EQ(initiative.owner_name, "Alice Smith");
}

TEST(InitiativeModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "init-3",
        "name": "Unowned Initiative",
        "description": null,
        "icon": null,
        "color": null,
        "slugId": "unowned",
        "url": "https://linear.app/acme/initiative/unowned",
        "status": null,
        "health": null,
        "targetDate": null,
        "startedAt": null,
        "completedAt": null,
        "trashed": false,
        "createdAt": "2026-01-01T00:00:00Z",
        "updatedAt": "2026-01-01T00:00:00Z",
        "owner": null
    })");

    Initiative initiative;
    from_json(j, initiative);

    EXPECT_EQ(initiative.id, "init-3");
    EXPECT_EQ(initiative.name, "Unowned Initiative");
    EXPECT_EQ(initiative.description, std::nullopt);
    EXPECT_EQ(initiative.icon, std::nullopt);
    EXPECT_EQ(initiative.color, std::nullopt);
    EXPECT_EQ(initiative.status, std::nullopt);
    EXPECT_EQ(initiative.health, std::nullopt);
    EXPECT_EQ(initiative.target_date, std::nullopt);
    EXPECT_EQ(initiative.started_at, std::nullopt);
    EXPECT_EQ(initiative.completed_at, std::nullopt);
    EXPECT_EQ(initiative.owner_id, std::nullopt);
    EXPECT_EQ(initiative.owner_name, std::nullopt);
    EXPECT_FALSE(initiative.trashed);
    EXPECT_EQ(initiative.slug_id, "unowned");
    EXPECT_EQ(initiative.created_at, "2026-01-01T00:00:00Z");
}
