#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/documents/model.h"

using json = nlohmann::json;

TEST(DocumentModel, ParsesMinimalDocument) {
    auto j = json::parse(R"({
        "id": "doc-001",
        "title": "Architecture Overview",
        "slugId": "arch-overview",
        "url": "https://linear.app/team/doc/arch-overview"
    })");

    Document doc;
    from_json(j, doc);

    EXPECT_EQ(doc.id, "doc-001");
    EXPECT_EQ(doc.title, "Architecture Overview");
    EXPECT_EQ(doc.slug_id, "arch-overview");
    EXPECT_EQ(doc.url, "https://linear.app/team/doc/arch-overview");
    EXPECT_EQ(doc.icon, std::nullopt);
    EXPECT_EQ(doc.color, std::nullopt);
    EXPECT_EQ(doc.content, std::nullopt);
    EXPECT_EQ(doc.creator_id, std::nullopt);
    EXPECT_EQ(doc.creator_name, std::nullopt);
    EXPECT_EQ(doc.project_id, std::nullopt);
    EXPECT_EQ(doc.project_name, std::nullopt);
    EXPECT_EQ(doc.initiative_id, std::nullopt);
    EXPECT_FALSE(doc.trashed);
}

TEST(DocumentModel, ParsesFullDocument) {
    auto j = json::parse(R"({
        "id": "doc-002",
        "title": "RFC: New Auth Flow",
        "slugId": "rfc-new-auth-flow",
        "url": "https://linear.app/team/doc/rfc-new-auth-flow",
        "icon": "lock",
        "color": "#4A90E2",
        "createdAt": "2026-01-10T09:00:00Z",
        "updatedAt": "2026-02-01T14:30:00Z",
        "trashed": false,
        "content": "# RFC: New Auth Flow\n\nThis document describes...",
        "creator": { "id": "user-abc", "displayName": "Alice Chen" },
        "project": { "id": "proj-xyz", "name": "Platform Revamp" },
        "initiative": { "id": "init-123" }
    })");

    Document doc;
    from_json(j, doc);

    EXPECT_EQ(doc.id, "doc-002");
    EXPECT_EQ(doc.title, "RFC: New Auth Flow");
    EXPECT_EQ(doc.slug_id, "rfc-new-auth-flow");
    EXPECT_EQ(doc.url, "https://linear.app/team/doc/rfc-new-auth-flow");
    EXPECT_EQ(doc.icon, "lock");
    EXPECT_EQ(doc.color, "#4A90E2");
    EXPECT_EQ(doc.created_at, "2026-01-10T09:00:00Z");
    EXPECT_EQ(doc.updated_at, "2026-02-01T14:30:00Z");
    EXPECT_FALSE(doc.trashed);
    EXPECT_EQ(doc.content, "# RFC: New Auth Flow\n\nThis document describes...");
    EXPECT_EQ(doc.creator_id, "user-abc");
    EXPECT_EQ(doc.creator_name, "Alice Chen");
    EXPECT_EQ(doc.project_id, "proj-xyz");
    EXPECT_EQ(doc.project_name, "Platform Revamp");
    EXPECT_EQ(doc.initiative_id, "init-123");
}

TEST(DocumentModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "doc-003",
        "title": "Untitled",
        "slugId": "untitled",
        "url": "https://linear.app/team/doc/untitled",
        "icon": null,
        "color": null,
        "content": null,
        "trashed": false,
        "creator": null,
        "project": null,
        "initiative": null
    })");

    Document doc;
    from_json(j, doc);

    EXPECT_EQ(doc.id, "doc-003");
    EXPECT_EQ(doc.title, "Untitled");
    EXPECT_EQ(doc.icon, std::nullopt);
    EXPECT_EQ(doc.color, std::nullopt);
    EXPECT_EQ(doc.content, std::nullopt);
    EXPECT_EQ(doc.creator_id, std::nullopt);
    EXPECT_EQ(doc.creator_name, std::nullopt);
    EXPECT_EQ(doc.project_id, std::nullopt);
    EXPECT_EQ(doc.project_name, std::nullopt);
    EXPECT_EQ(doc.initiative_id, std::nullopt);
    EXPECT_FALSE(doc.trashed);
}
