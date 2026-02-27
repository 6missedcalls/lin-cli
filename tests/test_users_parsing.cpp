#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/users/model.h"

using json = nlohmann::json;

TEST(UserModel, ParsesMinimalUser) {
    auto j = json::parse(R"({
        "id": "user-001",
        "name": "Jane Doe",
        "displayName": "janedoe",
        "email": "jane@example.com"
    })");

    User user;
    from_json(j, user);

    EXPECT_EQ(user.id, "user-001");
    EXPECT_EQ(user.name, "Jane Doe");
    EXPECT_EQ(user.display_name, "janedoe");
    EXPECT_EQ(user.email, "jane@example.com");
    EXPECT_EQ(user.avatar_url, std::nullopt);
    EXPECT_EQ(user.description, std::nullopt);
    EXPECT_EQ(user.timezone, std::nullopt);
    EXPECT_EQ(user.last_seen, std::nullopt);
    EXPECT_EQ(user.status_emoji, std::nullopt);
    EXPECT_EQ(user.status_label, std::nullopt);
    EXPECT_TRUE(user.active);
    EXPECT_FALSE(user.admin);
    EXPECT_FALSE(user.guest);
    EXPECT_FALSE(user.is_me);
}

TEST(UserModel, ParsesFullUser) {
    auto j = json::parse(R"({
        "id": "user-002",
        "name": "John Smith",
        "displayName": "johnsmith",
        "email": "john@example.com",
        "avatarUrl": "https://example.com/avatar.png",
        "description": "Senior Engineer",
        "timezone": "America/New_York",
        "lastSeen": "2026-02-25T10:00:00Z",
        "active": true,
        "admin": false,
        "guest": false,
        "isMe": false,
        "createdAt": "2024-01-01T00:00:00Z",
        "statusEmoji": "\ud83d\udcbb",
        "statusLabel": "Coding"
    })");

    User user;
    from_json(j, user);

    EXPECT_EQ(user.id, "user-002");
    EXPECT_EQ(user.name, "John Smith");
    EXPECT_EQ(user.display_name, "johnsmith");
    EXPECT_EQ(user.email, "john@example.com");
    EXPECT_EQ(user.avatar_url, "https://example.com/avatar.png");
    EXPECT_EQ(user.description, "Senior Engineer");
    EXPECT_EQ(user.timezone, "America/New_York");
    EXPECT_EQ(user.last_seen, "2026-02-25T10:00:00Z");
    EXPECT_EQ(user.created_at, "2024-01-01T00:00:00Z");
    EXPECT_EQ(user.status_label, "Coding");
    EXPECT_TRUE(user.active);
    EXPECT_FALSE(user.admin);
    EXPECT_FALSE(user.guest);
    EXPECT_FALSE(user.is_me);
}

TEST(UserModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "user-003",
        "name": "Ghost User",
        "displayName": "ghost",
        "email": "ghost@example.com",
        "avatarUrl": null,
        "description": null,
        "timezone": null,
        "lastSeen": null,
        "statusEmoji": null,
        "statusLabel": null,
        "active": true,
        "admin": false,
        "guest": false,
        "isMe": false
    })");

    User user;
    from_json(j, user);

    EXPECT_EQ(user.id, "user-003");
    EXPECT_EQ(user.avatar_url, std::nullopt);
    EXPECT_EQ(user.description, std::nullopt);
    EXPECT_EQ(user.timezone, std::nullopt);
    EXPECT_EQ(user.last_seen, std::nullopt);
    EXPECT_EQ(user.status_emoji, std::nullopt);
    EXPECT_EQ(user.status_label, std::nullopt);
}

TEST(UserModel, ParsesAdminUser) {
    auto j = json::parse(R"({
        "id": "user-004",
        "name": "Admin User",
        "displayName": "admin",
        "email": "admin@example.com",
        "active": true,
        "admin": true,
        "guest": false,
        "isMe": true,
        "createdAt": "2023-06-01T00:00:00Z"
    })");

    User user;
    from_json(j, user);

    EXPECT_EQ(user.id, "user-004");
    EXPECT_EQ(user.display_name, "admin");
    EXPECT_TRUE(user.active);
    EXPECT_TRUE(user.admin);
    EXPECT_FALSE(user.guest);
    EXPECT_TRUE(user.is_me);
    EXPECT_EQ(user.created_at, "2023-06-01T00:00:00Z");
}
