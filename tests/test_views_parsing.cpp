#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/views/model.h"

using json = nlohmann::json;

TEST(CustomViewModel, ParsesMinimalView) {
    auto j = json::parse(R"({
        "id": "view-1",
        "name": "My View",
        "slugId": "my-view",
        "shared": false
    })");

    CustomView v;
    from_json(j, v);

    EXPECT_EQ(v.id, "view-1");
    EXPECT_EQ(v.name, "My View");
    EXPECT_EQ(v.slug_id, "my-view");
    EXPECT_FALSE(v.shared);
    EXPECT_EQ(v.description, std::nullopt);
    EXPECT_EQ(v.icon, std::nullopt);
    EXPECT_EQ(v.color, std::nullopt);
    EXPECT_EQ(v.model_name, std::nullopt);
    EXPECT_EQ(v.filter_data, std::nullopt);
    EXPECT_EQ(v.owner_id, std::nullopt);
    EXPECT_EQ(v.owner_name, std::nullopt);
    EXPECT_EQ(v.team_id, std::nullopt);
    EXPECT_EQ(v.team_name, std::nullopt);
}

TEST(CustomViewModel, ParsesFullView) {
    auto j = json::parse(R"({
        "id": "view-2",
        "createdAt": "2026-01-01T00:00:00Z",
        "updatedAt": "2026-01-15T12:00:00Z",
        "name": "Engineering Bugs",
        "description": "All open bug reports",
        "icon": "BugIcon",
        "color": "#FF0000",
        "slugId": "engineering-bugs",
        "modelName": "Issue",
        "shared": true,
        "filterData": {"assignee": {"id": {"eq": "user-1"}}, "state": {"type": {"eq": "started"}}},
        "owner": { "id": "user-1", "displayName": "Jane Doe" },
        "team": { "id": "team-1", "name": "Engineering" }
    })");

    CustomView v;
    from_json(j, v);

    EXPECT_EQ(v.id, "view-2");
    EXPECT_EQ(v.created_at, "2026-01-01T00:00:00Z");
    EXPECT_EQ(v.updated_at, "2026-01-15T12:00:00Z");
    EXPECT_EQ(v.name, "Engineering Bugs");
    EXPECT_EQ(v.description, "All open bug reports");
    EXPECT_EQ(v.icon, "BugIcon");
    EXPECT_EQ(v.color, "#FF0000");
    EXPECT_EQ(v.slug_id, "engineering-bugs");
    EXPECT_EQ(v.model_name, "Issue");
    EXPECT_TRUE(v.shared);

    ASSERT_TRUE(v.filter_data.has_value());
    EXPECT_TRUE(v.filter_data.value().contains("assignee"));
    EXPECT_TRUE(v.filter_data.value().contains("state"));

    EXPECT_EQ(v.owner_id, "user-1");
    EXPECT_EQ(v.owner_name, "Jane Doe");
    EXPECT_EQ(v.team_id, "team-1");
    EXPECT_EQ(v.team_name, "Engineering");
}

TEST(CustomViewModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "view-3",
        "name": "Sparse View",
        "slugId": "sparse-view",
        "shared": false,
        "description": null,
        "icon": null,
        "color": null,
        "modelName": null,
        "filterData": null,
        "owner": null,
        "team": null,
        "createdAt": null,
        "updatedAt": null
    })");

    CustomView v;
    from_json(j, v);

    EXPECT_EQ(v.id, "view-3");
    EXPECT_EQ(v.name, "Sparse View");
    EXPECT_EQ(v.slug_id, "sparse-view");
    EXPECT_FALSE(v.shared);
    EXPECT_EQ(v.description, std::nullopt);
    EXPECT_EQ(v.icon, std::nullopt);
    EXPECT_EQ(v.color, std::nullopt);
    EXPECT_EQ(v.model_name, std::nullopt);
    EXPECT_EQ(v.filter_data, std::nullopt);
    EXPECT_EQ(v.owner_id, std::nullopt);
    EXPECT_EQ(v.owner_name, std::nullopt);
    EXPECT_EQ(v.team_id, std::nullopt);
    EXPECT_EQ(v.team_name, std::nullopt);
    EXPECT_EQ(v.created_at, "");
    EXPECT_EQ(v.updated_at, "");
}
