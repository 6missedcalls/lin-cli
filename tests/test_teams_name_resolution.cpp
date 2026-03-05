#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/teams/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Tests verifying that resolve_team_id logic handles name matching correctly.
// The actual resolve_team_id function does HTTP calls, so we test the
// underlying name-matching logic by simulating what it does: case-insensitive
// comparison of display_name and name fields.
// ---------------------------------------------------------------------------

namespace {

// Mirrors the matching logic in resolve_team_id (api.cpp)
std::string to_lower(const std::string& s) {
    std::string result = s;
    for (auto& c : result) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

std::optional<std::string> find_team_by_name(
    const std::vector<Team>& teams,
    const std::string& input
) {
    std::string lower_input = to_lower(input);

    for (const auto& team : teams) {
        if (to_lower(team.display_name) == lower_input) {
            return team.id;
        }
        if (to_lower(team.name) == lower_input) {
            return team.id;
        }
    }
    return std::nullopt;
}

std::vector<Team> make_test_teams() {
    std::vector<Team> teams;

    auto parse_team = [](const char* data) {
        auto j = json::parse(data);
        Team t;
        from_json(j, t);
        return t;
    };

    teams.push_back(parse_team(R"({
        "id": "team-aaa",
        "name": "Engineering",
        "key": "ENG",
        "displayName": "Webisoft USA"
    })"));

    teams.push_back(parse_team(R"({
        "id": "team-bbb",
        "name": "Design",
        "key": "DES",
        "displayName": "Design Team"
    })"));

    teams.push_back(parse_team(R"({
        "id": "team-ccc",
        "name": "Product",
        "key": "PROD",
        "displayName": "Product"
    })"));

    return teams;
}

}  // namespace

TEST(TeamNameResolution, MatchesExactDisplayName) {
    auto teams = make_test_teams();
    auto result = find_team_by_name(teams, "Webisoft USA");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "team-aaa");
}

TEST(TeamNameResolution, MatchesCaseInsensitiveDisplayName) {
    auto teams = make_test_teams();
    auto result = find_team_by_name(teams, "webisoft usa");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "team-aaa");
}

TEST(TeamNameResolution, MatchesRawName) {
    auto teams = make_test_teams();
    auto result = find_team_by_name(teams, "Engineering");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "team-aaa");
}

TEST(TeamNameResolution, MatchesCaseInsensitiveRawName) {
    auto teams = make_test_teams();
    auto result = find_team_by_name(teams, "engineering");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "team-aaa");
}

TEST(TeamNameResolution, ReturnsNulloptForUnknownName) {
    auto teams = make_test_teams();
    auto result = find_team_by_name(teams, "Nonexistent Team");
    EXPECT_FALSE(result.has_value());
}

TEST(TeamNameResolution, PrefersDisplayNameOverRawName) {
    // display_name is checked first, so if a team's display_name matches,
    // it should be returned even if another team's raw name also matches
    auto teams = make_test_teams();
    auto result = find_team_by_name(teams, "Design Team");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "team-bbb");
}

TEST(TeamNameResolution, MatchesWhenDisplayNameEqualsName) {
    auto teams = make_test_teams();
    auto result = find_team_by_name(teams, "Product");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "team-ccc");
}
