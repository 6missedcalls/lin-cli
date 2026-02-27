#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/labels/model.h"

using json = nlohmann::json;

TEST(IssueLabelModel, ParsesMinimalLabel) {
    auto j = json::parse(R"({
        "id": "label-1",
        "name": "Bug",
        "color": "#FF0000"
    })");

    IssueLabel label;
    from_json(j, label);

    EXPECT_EQ(label.id, "label-1");
    EXPECT_EQ(label.name, "Bug");
    EXPECT_EQ(label.color, "#FF0000");
    EXPECT_EQ(label.is_group, false);
    EXPECT_EQ(label.description, std::nullopt);
    EXPECT_EQ(label.parent_id, std::nullopt);
    EXPECT_EQ(label.parent_name, std::nullopt);
    EXPECT_EQ(label.team_id, std::nullopt);
    EXPECT_EQ(label.team_name, std::nullopt);
}

TEST(IssueLabelModel, ParsesFullLabel) {
    auto j = json::parse(R"({
        "id": "label-42",
        "name": "Feature",
        "color": "#00FF00",
        "description": "A new feature request",
        "isGroup": false,
        "createdAt": "2026-01-15T10:00:00Z",
        "parent": { "id": "parent-1", "name": "Category" },
        "team": { "id": "team-1", "name": "Engineering" }
    })");

    IssueLabel label;
    from_json(j, label);

    EXPECT_EQ(label.id, "label-42");
    EXPECT_EQ(label.name, "Feature");
    EXPECT_EQ(label.color, "#00FF00");
    EXPECT_EQ(label.description, "A new feature request");
    EXPECT_EQ(label.is_group, false);
    EXPECT_EQ(label.created_at, "2026-01-15T10:00:00Z");
    EXPECT_EQ(label.parent_id, "parent-1");
    EXPECT_EQ(label.parent_name, "Category");
    EXPECT_EQ(label.team_id, "team-1");
    EXPECT_EQ(label.team_name, "Engineering");
}

TEST(IssueLabelModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "label-99",
        "name": "Triage",
        "color": "#CCCCCC",
        "description": null,
        "isGroup": false,
        "parent": null,
        "team": null
    })");

    IssueLabel label;
    from_json(j, label);

    EXPECT_EQ(label.id, "label-99");
    EXPECT_EQ(label.name, "Triage");
    EXPECT_EQ(label.description, std::nullopt);
    EXPECT_EQ(label.parent_id, std::nullopt);
    EXPECT_EQ(label.parent_name, std::nullopt);
    EXPECT_EQ(label.team_id, std::nullopt);
    EXPECT_EQ(label.team_name, std::nullopt);
    EXPECT_EQ(label.is_group, false);
}

TEST(IssueLabelModel, ParsesGroupLabel) {
    auto j = json::parse(R"({
        "id": "group-1",
        "name": "Status",
        "color": "#0000FF",
        "isGroup": true,
        "createdAt": "2026-02-01T00:00:00Z",
        "team": { "id": "team-2", "name": "Platform" }
    })");

    IssueLabel label;
    from_json(j, label);

    EXPECT_EQ(label.id, "group-1");
    EXPECT_EQ(label.name, "Status");
    EXPECT_EQ(label.color, "#0000FF");
    EXPECT_EQ(label.is_group, true);
    EXPECT_EQ(label.team_id, "team-2");
    EXPECT_EQ(label.team_name, "Platform");
    EXPECT_EQ(label.parent_id, std::nullopt);
    EXPECT_EQ(label.description, std::nullopt);
}
