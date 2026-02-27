#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/comments/model.h"

using json = nlohmann::json;

TEST(CommentModel, ParsesMinimalComment) {
    auto j = json::parse(R"({
        "id": "cmt-001",
        "body": "Looks good to me.",
        "url": "https://linear.app/team/issue/ENG-1#comment-cmt-001",
        "createdAt": "2026-02-01T10:00:00Z",
        "updatedAt": "2026-02-01T10:00:00Z"
    })");

    Comment comment;
    from_json(j, comment);

    EXPECT_EQ(comment.id, "cmt-001");
    EXPECT_EQ(comment.body, "Looks good to me.");
    EXPECT_EQ(comment.url, "https://linear.app/team/issue/ENG-1#comment-cmt-001");
    EXPECT_EQ(comment.created_at, "2026-02-01T10:00:00Z");
    EXPECT_EQ(comment.updated_at, "2026-02-01T10:00:00Z");
    EXPECT_EQ(comment.user_id, std::nullopt);
    EXPECT_EQ(comment.user_name, std::nullopt);
    EXPECT_EQ(comment.parent_id, std::nullopt);
    EXPECT_EQ(comment.issue_id, std::nullopt);
    EXPECT_EQ(comment.edited_at, std::nullopt);
    EXPECT_EQ(comment.resolved_at, std::nullopt);
    EXPECT_EQ(comment.project_update_id, std::nullopt);
}

TEST(CommentModel, ParsesFullComment) {
    auto j = json::parse(R"({
        "id": "cmt-002",
        "body": "## Review Notes\n\nThis looks correct. Merging now.",
        "url": "https://linear.app/team/issue/ENG-42#comment-cmt-002",
        "createdAt": "2026-02-10T14:30:00Z",
        "updatedAt": "2026-02-10T15:00:00Z",
        "editedAt": "2026-02-10T15:00:00Z",
        "resolvedAt": "2026-02-11T09:00:00Z",
        "user": { "id": "user-abc", "displayName": "Alice Engineer" },
        "parent": { "id": "cmt-001" },
        "issue": { "id": "issue-xyz" }
    })");

    Comment comment;
    from_json(j, comment);

    EXPECT_EQ(comment.id, "cmt-002");
    EXPECT_EQ(comment.body, "## Review Notes\n\nThis looks correct. Merging now.");
    EXPECT_EQ(comment.url, "https://linear.app/team/issue/ENG-42#comment-cmt-002");
    EXPECT_EQ(comment.created_at, "2026-02-10T14:30:00Z");
    EXPECT_EQ(comment.updated_at, "2026-02-10T15:00:00Z");
    EXPECT_EQ(comment.edited_at, "2026-02-10T15:00:00Z");
    EXPECT_EQ(comment.resolved_at, "2026-02-11T09:00:00Z");
    EXPECT_EQ(comment.user_id, "user-abc");
    EXPECT_EQ(comment.user_name, "Alice Engineer");
    EXPECT_EQ(comment.parent_id, "cmt-001");
    EXPECT_EQ(comment.issue_id, "issue-xyz");
    EXPECT_EQ(comment.project_update_id, std::nullopt);
}

TEST(CommentModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "cmt-003",
        "body": "A comment with all nullable fields set to null.",
        "url": "https://linear.app/team/issue/ENG-7#comment-cmt-003",
        "createdAt": "2026-01-15T08:00:00Z",
        "updatedAt": "2026-01-15T08:00:00Z",
        "editedAt": null,
        "resolvedAt": null,
        "user": null,
        "parent": null,
        "issue": null
    })");

    Comment comment;
    from_json(j, comment);

    EXPECT_EQ(comment.id, "cmt-003");
    EXPECT_EQ(comment.body, "A comment with all nullable fields set to null.");
    EXPECT_EQ(comment.edited_at, std::nullopt);
    EXPECT_EQ(comment.resolved_at, std::nullopt);
    EXPECT_EQ(comment.user_id, std::nullopt);
    EXPECT_EQ(comment.user_name, std::nullopt);
    EXPECT_EQ(comment.parent_id, std::nullopt);
    EXPECT_EQ(comment.issue_id, std::nullopt);
    EXPECT_EQ(comment.project_update_id, std::nullopt);
}
