#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/notifications/model.h"

using json = nlohmann::json;

TEST(NotificationModel, ParsesMinimalNotification) {
    auto j = json::parse(R"({
        "id": "notif-123",
        "type": "issueAssignedToYou",
        "createdAt": "2026-01-01T00:00:00Z",
        "updatedAt": "2026-01-02T00:00:00Z"
    })");

    Notification n;
    from_json(j, n);

    EXPECT_EQ(n.id, "notif-123");
    EXPECT_EQ(n.type, "issueAssignedToYou");
    EXPECT_EQ(n.created_at, "2026-01-01T00:00:00Z");
    EXPECT_EQ(n.updated_at, "2026-01-02T00:00:00Z");
    EXPECT_EQ(n.read_at, std::nullopt);
    EXPECT_EQ(n.snoozed_until_at, std::nullopt);
    EXPECT_EQ(n.archived_at, std::nullopt);
    EXPECT_EQ(n.actor_id, std::nullopt);
    EXPECT_EQ(n.actor_name, std::nullopt);
    EXPECT_EQ(n.title, std::nullopt);
    EXPECT_EQ(n.subtitle, std::nullopt);
    EXPECT_EQ(n.url, std::nullopt);
}

TEST(NotificationModel, ParsesFullNotification) {
    auto j = json::parse(R"({
        "id": "notif-456",
        "type": "issueCommentMention",
        "createdAt": "2026-02-01T08:00:00Z",
        "updatedAt": "2026-02-01T09:00:00Z",
        "readAt": "2026-02-01T10:00:00Z",
        "snoozedUntilAt": "2026-02-10T08:00:00Z",
        "archivedAt": "2026-02-20T12:00:00Z",
        "url": "https://linear.app/team/issue/ENG-42",
        "title": "Jane mentioned you in a comment",
        "subtitle": "ENG-42: Fix performance regression",
        "actor": { "id": "user-99", "name": "Jane Doe" }
    })");

    Notification n;
    from_json(j, n);

    EXPECT_EQ(n.id, "notif-456");
    EXPECT_EQ(n.type, "issueCommentMention");
    EXPECT_EQ(n.created_at, "2026-02-01T08:00:00Z");
    EXPECT_EQ(n.updated_at, "2026-02-01T09:00:00Z");
    EXPECT_EQ(n.read_at, "2026-02-01T10:00:00Z");
    EXPECT_EQ(n.snoozed_until_at, "2026-02-10T08:00:00Z");
    EXPECT_EQ(n.archived_at, "2026-02-20T12:00:00Z");
    EXPECT_EQ(n.url, "https://linear.app/team/issue/ENG-42");
    EXPECT_EQ(n.title, "Jane mentioned you in a comment");
    EXPECT_EQ(n.subtitle, "ENG-42: Fix performance regression");
    EXPECT_EQ(n.actor_id, "user-99");
    EXPECT_EQ(n.actor_name, "Jane Doe");
}

TEST(NotificationModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "notif-789",
        "type": "issueCreated",
        "createdAt": "2026-03-01T00:00:00Z",
        "updatedAt": "2026-03-01T00:00:00Z",
        "readAt": null,
        "snoozedUntilAt": null,
        "archivedAt": null,
        "url": null,
        "title": null,
        "subtitle": null,
        "actor": null
    })");

    Notification n;
    from_json(j, n);

    EXPECT_EQ(n.id, "notif-789");
    EXPECT_EQ(n.type, "issueCreated");
    EXPECT_EQ(n.read_at, std::nullopt);
    EXPECT_EQ(n.snoozed_until_at, std::nullopt);
    EXPECT_EQ(n.archived_at, std::nullopt);
    EXPECT_EQ(n.url, std::nullopt);
    EXPECT_EQ(n.title, std::nullopt);
    EXPECT_EQ(n.subtitle, std::nullopt);
    EXPECT_EQ(n.actor_id, std::nullopt);
    EXPECT_EQ(n.actor_name, std::nullopt);
}
