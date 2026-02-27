#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/webhooks/model.h"

using json = nlohmann::json;

TEST(WebhookModel, ParsesMinimalWebhook) {
    auto j = json::parse(R"({
        "id": "webhook-abc-123"
    })");

    Webhook w;
    from_json(j, w);

    EXPECT_EQ(w.id, "webhook-abc-123");
    EXPECT_EQ(w.created_at, "");
    EXPECT_EQ(w.updated_at, "");
    EXPECT_EQ(w.label, std::nullopt);
    EXPECT_EQ(w.url, std::nullopt);
    EXPECT_EQ(w.enabled, true);
    EXPECT_EQ(w.team_id, std::nullopt);
    EXPECT_EQ(w.creator_id, std::nullopt);
    EXPECT_EQ(w.creator_name, std::nullopt);
}

TEST(WebhookModel, ParsesFullWebhook) {
    auto j = json::parse(R"({
        "id": "webhook-xyz-456",
        "createdAt": "2026-01-10T12:00:00Z",
        "updatedAt": "2026-02-01T08:30:00Z",
        "label": "My CI Hook",
        "url": "https://example.com/hooks/linear",
        "enabled": true,
        "team": { "id": "team-eng-1" },
        "creator": { "id": "user-42", "displayName": "Alice Dev" }
    })");

    Webhook w;
    from_json(j, w);

    EXPECT_EQ(w.id, "webhook-xyz-456");
    EXPECT_EQ(w.created_at, "2026-01-10T12:00:00Z");
    EXPECT_EQ(w.updated_at, "2026-02-01T08:30:00Z");
    EXPECT_EQ(w.label, "My CI Hook");
    EXPECT_EQ(w.url, "https://example.com/hooks/linear");
    EXPECT_EQ(w.enabled, true);
    EXPECT_EQ(w.team_id, "team-eng-1");
    EXPECT_EQ(w.creator_id, "user-42");
    EXPECT_EQ(w.creator_name, "Alice Dev");
}

TEST(WebhookModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "webhook-null-789",
        "createdAt": "2026-01-01T00:00:00Z",
        "updatedAt": "2026-01-01T00:00:00Z",
        "label": null,
        "url": null,
        "enabled": false,
        "team": null,
        "creator": null
    })");

    Webhook w;
    from_json(j, w);

    EXPECT_EQ(w.id, "webhook-null-789");
    EXPECT_EQ(w.label, std::nullopt);
    EXPECT_EQ(w.url, std::nullopt);
    EXPECT_EQ(w.enabled, false);
    EXPECT_EQ(w.team_id, std::nullopt);
    EXPECT_EQ(w.creator_id, std::nullopt);
    EXPECT_EQ(w.creator_name, std::nullopt);
}
