#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/projects/api.h"

using json = nlohmann::json;

// Forward-declare the helper we'll add to api.h
namespace projects_api {
json build_create_json(const ProjectCreateInput& input);
}

TEST(ProjectCreateInput, MinimalInputAlwaysIncludesTeamIds) {
    ProjectCreateInput input;
    input.name = "Personal";
    input.team_ids = {"team-uuid-123"};

    auto j = projects_api::build_create_json(input);

    EXPECT_EQ(j["name"], "Personal");
    ASSERT_TRUE(j.contains("teamIds"));
    EXPECT_EQ(j["teamIds"].size(), 1);
    EXPECT_EQ(j["teamIds"][0], "team-uuid-123");
}

TEST(ProjectCreateInput, EmptyTeamIdsStillSerialized) {
    // Linear API requires teamIds (NON_NULL) — it should always be present
    ProjectCreateInput input;
    input.name = "Solo Project";

    auto j = projects_api::build_create_json(input);

    EXPECT_EQ(j["name"], "Solo Project");
    ASSERT_TRUE(j.contains("teamIds"));
    EXPECT_TRUE(j["teamIds"].is_array());
}

TEST(ProjectCreateInput, AllFieldsSerialized) {
    ProjectCreateInput input;
    input.name = "Full Project";
    input.description = "A description";
    input.icon = "rocket";
    input.color = "#FF0000";
    input.lead_id = "user-uuid-1";
    input.status_id = "status-uuid-1";
    input.priority = 2;
    input.start_date = "2026-01-01";
    input.target_date = "2026-06-30";
    input.team_ids = {"team-1", "team-2"};
    input.member_ids = {"member-1", "member-2"};

    auto j = projects_api::build_create_json(input);

    EXPECT_EQ(j["name"], "Full Project");
    EXPECT_EQ(j["description"], "A description");
    EXPECT_EQ(j["icon"], "rocket");
    EXPECT_EQ(j["color"], "#FF0000");
    EXPECT_EQ(j["leadId"], "user-uuid-1");
    EXPECT_EQ(j["statusId"], "status-uuid-1");
    EXPECT_EQ(j["priority"], 2);
    EXPECT_EQ(j["startDate"], "2026-01-01");
    EXPECT_EQ(j["targetDate"], "2026-06-30");
    EXPECT_EQ(j["teamIds"].size(), 2);
    EXPECT_EQ(j["memberIds"].size(), 2);
}

TEST(ProjectCreateInput, OptionalFieldsOmittedWhenUnset) {
    ProjectCreateInput input;
    input.name = "Minimal";
    input.team_ids = {"team-1"};

    auto j = projects_api::build_create_json(input);

    EXPECT_FALSE(j.contains("description"));
    EXPECT_FALSE(j.contains("icon"));
    EXPECT_FALSE(j.contains("color"));
    EXPECT_FALSE(j.contains("leadId"));
    EXPECT_FALSE(j.contains("statusId"));
    EXPECT_FALSE(j.contains("priority"));
    EXPECT_FALSE(j.contains("startDate"));
    EXPECT_FALSE(j.contains("targetDate"));
    EXPECT_FALSE(j.contains("memberIds"));
}
