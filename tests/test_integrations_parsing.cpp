#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/integrations/model.h"

using json = nlohmann::json;

TEST(IntegrationModel, ParsesMinimalIntegration) {
    auto j = json::parse(R"({
        "id": "intg-1",
        "service": "github",
        "createdAt": "2026-01-01T00:00:00Z"
    })");

    Integration intg;
    from_json(j, intg);

    EXPECT_EQ(intg.id, "intg-1");
    EXPECT_EQ(intg.service, "github");
    EXPECT_EQ(intg.created_at, "2026-01-01T00:00:00Z");
    EXPECT_EQ(intg.team_id, std::nullopt);
    EXPECT_EQ(intg.team_name, std::nullopt);
    EXPECT_EQ(intg.creator_id, std::nullopt);
    EXPECT_EQ(intg.creator_name, std::nullopt);
}

TEST(IntegrationModel, ParsesFullIntegration) {
    auto j = json::parse(R"({
        "id": "intg-42",
        "service": "slack",
        "createdAt": "2026-02-15T10:30:00Z",
        "team": { "id": "team-1", "name": "Engineering" },
        "creator": { "id": "user-1", "displayName": "Jane Doe" }
    })");

    Integration intg;
    from_json(j, intg);

    EXPECT_EQ(intg.id, "intg-42");
    EXPECT_EQ(intg.service, "slack");
    EXPECT_EQ(intg.created_at, "2026-02-15T10:30:00Z");
    EXPECT_EQ(intg.team_id, "team-1");
    EXPECT_EQ(intg.team_name, "Engineering");
    EXPECT_EQ(intg.creator_id, "user-1");
    EXPECT_EQ(intg.creator_name, "Jane Doe");
}

TEST(IntegrationModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "intg-99",
        "service": "figma",
        "createdAt": "2026-03-01T00:00:00Z",
        "team": null,
        "creator": null
    })");

    Integration intg;
    from_json(j, intg);

    EXPECT_EQ(intg.id, "intg-99");
    EXPECT_EQ(intg.service, "figma");
    EXPECT_EQ(intg.created_at, "2026-03-01T00:00:00Z");
    EXPECT_EQ(intg.team_id, std::nullopt);
    EXPECT_EQ(intg.team_name, std::nullopt);
    EXPECT_EQ(intg.creator_id, std::nullopt);
    EXPECT_EQ(intg.creator_name, std::nullopt);
}
