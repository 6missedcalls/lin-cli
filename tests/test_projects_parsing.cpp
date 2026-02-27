#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/projects/model.h"

using json = nlohmann::json;

TEST(ProjectModel, ParsesMinimalProject) {
    auto j = json::parse(R"({
        "id": "proj-123",
        "name": "Q1 Launch",
        "slugId": "q1-launch",
        "url": "https://linear.app/team/project/Q1-Launch-q1-launch"
    })");

    Project p;
    from_json(j, p);

    EXPECT_EQ(p.id, "proj-123");
    EXPECT_EQ(p.name, "Q1 Launch");
    EXPECT_EQ(p.slug_id, "q1-launch");
    EXPECT_EQ(p.url, "https://linear.app/team/project/Q1-Launch-q1-launch");
    EXPECT_EQ(p.priority, 0);
    EXPECT_EQ(p.progress, 0.0);
    EXPECT_EQ(p.trashed, false);
    EXPECT_EQ(p.description, std::nullopt);
    EXPECT_EQ(p.status_name, std::nullopt);
    EXPECT_EQ(p.lead_name, std::nullopt);
    EXPECT_EQ(p.health, std::nullopt);
}

TEST(ProjectModel, ParsesFullProject) {
    auto j = json::parse(R"({
        "id": "proj-456",
        "name": "Platform Revamp",
        "slugId": "platform-revamp",
        "url": "https://linear.app/team/project/Platform-Revamp-abc",
        "description": "Revamp the core platform",
        "icon": "rocket",
        "color": "#FF5733",
        "priority": 2,
        "priorityLabel": "High",
        "progress": 0.45,
        "scope": 120.0,
        "health": "onTrack",
        "healthUpdatedAt": "2026-02-01T00:00:00Z",
        "startDate": "2026-01-01",
        "targetDate": "2026-06-30",
        "startedAt": "2026-01-05T00:00:00Z",
        "completedAt": null,
        "canceledAt": null,
        "createdAt": "2025-12-01T00:00:00Z",
        "updatedAt": "2026-02-15T00:00:00Z",
        "trashed": false,
        "status": { "id": "status-1", "name": "In Progress", "type": "started" },
        "lead": { "id": "user-1", "displayName": "Alice" },
        "creator": { "id": "user-2", "displayName": "Bob" }
    })");

    Project p;
    from_json(j, p);

    EXPECT_EQ(p.id, "proj-456");
    EXPECT_EQ(p.name, "Platform Revamp");
    EXPECT_EQ(p.description, "Revamp the core platform");
    EXPECT_EQ(p.icon, "rocket");
    EXPECT_EQ(p.color, "#FF5733");
    EXPECT_EQ(p.priority, 2);
    EXPECT_EQ(p.priority_label, "High");
    EXPECT_DOUBLE_EQ(p.progress, 0.45);
    EXPECT_DOUBLE_EQ(p.scope, 120.0);
    EXPECT_EQ(p.health, "onTrack");
    EXPECT_EQ(p.health_updated_at, "2026-02-01T00:00:00Z");
    EXPECT_EQ(p.start_date, "2026-01-01");
    EXPECT_EQ(p.target_date, "2026-06-30");
    EXPECT_EQ(p.started_at, "2026-01-05T00:00:00Z");
    EXPECT_EQ(p.completed_at, std::nullopt);
    EXPECT_EQ(p.canceled_at, std::nullopt);
    EXPECT_EQ(p.status_id, "status-1");
    EXPECT_EQ(p.status_name, "In Progress");
    EXPECT_EQ(p.status_type, "started");
    EXPECT_EQ(p.lead_id, "user-1");
    EXPECT_EQ(p.lead_name, "Alice");
    EXPECT_EQ(p.creator_id, "user-2");
    EXPECT_EQ(p.creator_name, "Bob");
    EXPECT_EQ(p.trashed, false);
}

TEST(ProjectModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "proj-789",
        "name": "Minimal",
        "slugId": "minimal",
        "url": "https://linear.app/...",
        "description": null,
        "icon": null,
        "color": null,
        "health": null,
        "priorityLabel": null,
        "startDate": null,
        "targetDate": null,
        "startedAt": null,
        "completedAt": null,
        "canceledAt": null,
        "status": null,
        "lead": null,
        "creator": null
    })");

    Project p;
    from_json(j, p);

    EXPECT_EQ(p.description, std::nullopt);
    EXPECT_EQ(p.icon, std::nullopt);
    EXPECT_EQ(p.color, std::nullopt);
    EXPECT_EQ(p.health, std::nullopt);
    EXPECT_EQ(p.priority_label, std::nullopt);
    EXPECT_EQ(p.start_date, std::nullopt);
    EXPECT_EQ(p.target_date, std::nullopt);
    EXPECT_EQ(p.started_at, std::nullopt);
    EXPECT_EQ(p.completed_at, std::nullopt);
    EXPECT_EQ(p.canceled_at, std::nullopt);
    EXPECT_EQ(p.status_id, std::nullopt);
    EXPECT_EQ(p.status_name, std::nullopt);
    EXPECT_EQ(p.status_type, std::nullopt);
    EXPECT_EQ(p.lead_id, std::nullopt);
    EXPECT_EQ(p.lead_name, std::nullopt);
    EXPECT_EQ(p.creator_id, std::nullopt);
    EXPECT_EQ(p.creator_name, std::nullopt);
}

TEST(ProjectMilestoneModel, ParsesMilestone) {
    auto j = json::parse(R"({
        "id": "ms-1",
        "name": "Alpha Release",
        "createdAt": "2026-01-01T00:00:00Z",
        "updatedAt": "2026-01-10T00:00:00Z",
        "description": "First alpha build",
        "targetDate": "2026-03-31",
        "status": "next",
        "progress": 0.3,
        "sortOrder": 1.0,
        "project": { "id": "proj-456", "name": "Platform Revamp" }
    })");

    ProjectMilestone m;
    from_json(j, m);

    EXPECT_EQ(m.id, "ms-1");
    EXPECT_EQ(m.name, "Alpha Release");
    EXPECT_EQ(m.created_at, "2026-01-01T00:00:00Z");
    EXPECT_EQ(m.updated_at, "2026-01-10T00:00:00Z");
    EXPECT_EQ(m.description, "First alpha build");
    EXPECT_EQ(m.target_date, "2026-03-31");
    EXPECT_EQ(m.status, "next");
    EXPECT_DOUBLE_EQ(m.progress, 0.3);
    EXPECT_DOUBLE_EQ(m.sort_order, 1.0);
    EXPECT_EQ(m.project_id, "proj-456");
    EXPECT_EQ(m.project_name, "Platform Revamp");
}

TEST(ProjectMilestoneModel, ParsesMilestoneNullOptionals) {
    auto j = json::parse(R"({
        "id": "ms-2",
        "name": "Beta Release",
        "createdAt": "2026-02-01T00:00:00Z",
        "updatedAt": "2026-02-01T00:00:00Z",
        "status": "unstarted",
        "description": null,
        "targetDate": null,
        "project": null
    })");

    ProjectMilestone m;
    from_json(j, m);

    EXPECT_EQ(m.id, "ms-2");
    EXPECT_EQ(m.name, "Beta Release");
    EXPECT_EQ(m.status, "unstarted");
    EXPECT_EQ(m.description, std::nullopt);
    EXPECT_EQ(m.target_date, std::nullopt);
    EXPECT_EQ(m.project_id, std::nullopt);
    EXPECT_EQ(m.project_name, std::nullopt);
}

TEST(ProjectUpdateModel, ParsesProjectUpdate) {
    auto j = json::parse(R"({
        "id": "upd-1",
        "createdAt": "2026-02-10T00:00:00Z",
        "updatedAt": "2026-02-10T00:00:00Z",
        "body": "We made great progress this week on the API layer.",
        "health": "onTrack",
        "url": "https://linear.app/update/upd-1",
        "slugId": "upd-1-slug",
        "diffMarkdown": "Added 3 endpoints",
        "user": { "id": "user-1", "displayName": "Alice" },
        "project": { "id": "proj-456", "name": "Platform Revamp" }
    })");

    ProjectUpdate u;
    from_json(j, u);

    EXPECT_EQ(u.id, "upd-1");
    EXPECT_EQ(u.created_at, "2026-02-10T00:00:00Z");
    EXPECT_EQ(u.body, "We made great progress this week on the API layer.");
    EXPECT_EQ(u.health, "onTrack");
    EXPECT_EQ(u.url, "https://linear.app/update/upd-1");
    EXPECT_EQ(u.slug_id, "upd-1-slug");
    EXPECT_EQ(u.diff_markdown, "Added 3 endpoints");
    EXPECT_EQ(u.user_id, "user-1");
    EXPECT_EQ(u.user_name, "Alice");
    EXPECT_EQ(u.project_id, "proj-456");
    EXPECT_EQ(u.project_name, "Platform Revamp");
}

TEST(ProjectUpdateModel, ParsesProjectUpdateNullFields) {
    auto j = json::parse(R"({
        "id": "upd-2",
        "createdAt": "2026-02-11T00:00:00Z",
        "updatedAt": "2026-02-11T00:00:00Z",
        "body": "Short update.",
        "health": null,
        "url": "https://linear.app/update/upd-2",
        "slugId": "upd-2-slug",
        "diffMarkdown": null,
        "user": null,
        "project": null
    })");

    ProjectUpdate u;
    from_json(j, u);

    EXPECT_EQ(u.id, "upd-2");
    EXPECT_EQ(u.health, std::nullopt);
    EXPECT_EQ(u.diff_markdown, std::nullopt);
    EXPECT_EQ(u.user_id, std::nullopt);
    EXPECT_EQ(u.user_name, std::nullopt);
    EXPECT_EQ(u.project_id, std::nullopt);
    EXPECT_EQ(u.project_name, std::nullopt);
}
