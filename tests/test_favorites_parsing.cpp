#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/favorites/model.h"

using json = nlohmann::json;

TEST(FavoriteModel, ParsesMinimalFavorite) {
    auto j = json::parse(R"({
        "id": "fav-1",
        "createdAt": "2026-01-01T00:00:00Z",
        "type": "issue"
    })");

    Favorite fav;
    from_json(j, fav);

    EXPECT_EQ(fav.id, "fav-1");
    EXPECT_EQ(fav.created_at, "2026-01-01T00:00:00Z");
    EXPECT_EQ(fav.type, "issue");
    EXPECT_EQ(fav.sort_order, 0.0);
    EXPECT_EQ(fav.folder_name, std::nullopt);
    EXPECT_EQ(fav.url, std::nullopt);
    EXPECT_EQ(fav.title, std::nullopt);
    EXPECT_EQ(fav.issue_id, std::nullopt);
    EXPECT_EQ(fav.project_id, std::nullopt);
    EXPECT_EQ(fav.cycle_id, std::nullopt);
    EXPECT_EQ(fav.custom_view_id, std::nullopt);
    EXPECT_EQ(fav.document_id, std::nullopt);
    EXPECT_EQ(fav.label_id, std::nullopt);
}

TEST(FavoriteModel, ParsesFullFavorite) {
    auto j = json::parse(R"({
        "id": "fav-2",
        "createdAt": "2026-02-01T12:00:00Z",
        "type": "project",
        "sortOrder": 1.5,
        "folderName": "Work",
        "url": "https://linear.app/team/project/proj-1",
        "title": "Q1 Launch",
        "issue": { "id": "issue-abc" },
        "project": { "id": "proj-1" },
        "cycle": { "id": "cycle-7" },
        "customView": { "id": "view-3" },
        "document": { "id": "doc-9" },
        "label": { "id": "label-5" }
    })");

    Favorite fav;
    from_json(j, fav);

    EXPECT_EQ(fav.id, "fav-2");
    EXPECT_EQ(fav.created_at, "2026-02-01T12:00:00Z");
    EXPECT_EQ(fav.type, "project");
    EXPECT_EQ(fav.sort_order, 1.5);
    EXPECT_EQ(fav.folder_name, "Work");
    EXPECT_EQ(fav.url, "https://linear.app/team/project/proj-1");
    EXPECT_EQ(fav.title, "Q1 Launch");
    EXPECT_EQ(fav.issue_id, "issue-abc");
    EXPECT_EQ(fav.project_id, "proj-1");
    EXPECT_EQ(fav.cycle_id, "cycle-7");
    EXPECT_EQ(fav.custom_view_id, "view-3");
    EXPECT_EQ(fav.document_id, "doc-9");
    EXPECT_EQ(fav.label_id, "label-5");
}

TEST(FavoriteModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "fav-3",
        "createdAt": "2026-03-01T00:00:00Z",
        "type": "label",
        "sortOrder": null,
        "folderName": null,
        "url": null,
        "title": null,
        "issue": null,
        "project": null,
        "cycle": null,
        "customView": null,
        "document": null,
        "label": null
    })");

    Favorite fav;
    from_json(j, fav);

    EXPECT_EQ(fav.id, "fav-3");
    EXPECT_EQ(fav.type, "label");
    EXPECT_EQ(fav.sort_order, 0.0);
    EXPECT_EQ(fav.folder_name, std::nullopt);
    EXPECT_EQ(fav.url, std::nullopt);
    EXPECT_EQ(fav.title, std::nullopt);
    EXPECT_EQ(fav.issue_id, std::nullopt);
    EXPECT_EQ(fav.project_id, std::nullopt);
    EXPECT_EQ(fav.cycle_id, std::nullopt);
    EXPECT_EQ(fav.custom_view_id, std::nullopt);
    EXPECT_EQ(fav.document_id, std::nullopt);
    EXPECT_EQ(fav.label_id, std::nullopt);
}
