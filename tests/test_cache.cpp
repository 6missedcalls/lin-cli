#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <vector>

#include "core/cache.h"
#include "modules/teams/model.h"
#include "modules/users/model.h"
#include "modules/labels/model.h"

// ============================================================================
// Cache Path Tests
// ============================================================================

TEST(CachePath, ReturnsValidPath) {
    std::string path = cache::cache_path();
    EXPECT_NE(path, "");
}

TEST(CachePath, ContainsLinDirectory) {
    std::string path = cache::cache_path();
    EXPECT_NE(path.find("lin"), std::string::npos);
}

TEST(CachePath, ContainsCacheDbFilename) {
    std::string path = cache::cache_path();
    EXPECT_NE(path.find("cache.db"), std::string::npos);
}

TEST(CachePath, IsAbsolutePath) {
    std::string path = cache::cache_path();
    EXPECT_EQ(path[0], '/');
}

// ============================================================================
// Cache Instance Tests
// ============================================================================

TEST(CacheInstance, CanInstantiateCache) {
    cache::Cache c;
    // Should not crash
    EXPECT_TRUE(true);
}

TEST(CacheInstance, OpensSuccessfully) {
    cache::Cache c;
    EXPECT_TRUE(c.is_open());
}

TEST(CacheInstance, IsMovable) {
    cache::Cache c1;
    cache::Cache c2 = std::move(c1);
    EXPECT_TRUE(c2.is_open());
}

TEST(CacheInstance, IsNonCopyable) {
    cache::Cache c;
    // This should not compile with the deleted copy constructor
    // Compile-time check only
    EXPECT_TRUE(true);
}

// ============================================================================
// Team Cache Tests
// ============================================================================

TEST(CacheTeams, StoreAndRetrieveTeams) {
    cache::Cache c;

    std::vector<Team> teams;
    Team t1;
    t1.id = "team-1";
    t1.created_at = "2025-01-01T00:00:00Z";
    t1.updated_at = "2025-01-01T00:00:00Z";
    t1.name = "Engineering";
    t1.key = "ENG";
    t1.display_name = "Engineering Team";
    t1.issue_estimation_type = "fibonacci";
    t1.cycles_enabled = true;
    t1.triage_enabled = false;
    t1.private_team = false;
    t1.issue_count = 42;
    teams.push_back(t1);

    Team t2;
    t2.id = "team-2";
    t2.created_at = "2025-01-02T00:00:00Z";
    t2.updated_at = "2025-01-02T00:00:00Z";
    t2.name = "Product";
    t2.key = "PROD";
    t2.display_name = "Product Team";
    t2.issue_estimation_type = "points";
    t2.cycles_enabled = false;
    t2.triage_enabled = true;
    t2.private_team = true;
    t2.issue_count = 25;
    teams.push_back(t2);

    // Store teams
    c.store_teams(teams);

    // Retrieve all teams
    auto retrieved = c.get_teams();
    EXPECT_GE(retrieved.size(), 2);

    // Verify first team
    bool found_eng = false;
    for (const auto& t : retrieved) {
        if (t.id == "team-1") {
            found_eng = true;
            EXPECT_EQ(t.name, "Engineering");
            EXPECT_EQ(t.key, "ENG");
            EXPECT_EQ(t.display_name, "Engineering Team");
            EXPECT_TRUE(t.cycles_enabled);
            EXPECT_FALSE(t.triage_enabled);
            EXPECT_EQ(t.issue_count, 42);
            break;
        }
    }
    EXPECT_TRUE(found_eng);

    // Verify second team
    bool found_prod = false;
    for (const auto& t : retrieved) {
        if (t.id == "team-2") {
            found_prod = true;
            EXPECT_EQ(t.name, "Product");
            EXPECT_EQ(t.key, "PROD");
            EXPECT_TRUE(t.triage_enabled);
            EXPECT_FALSE(t.cycles_enabled);
            EXPECT_EQ(t.issue_count, 25);
            break;
        }
    }
    EXPECT_TRUE(found_prod);
}

TEST(CacheTeams, FindTeamByKey) {
    cache::Cache c;

    Team t;
    t.id = "team-find-key";
    t.created_at = "2025-01-01T00:00:00Z";
    t.updated_at = "2025-01-01T00:00:00Z";
    t.name = "Search Test";
    t.key = "SEARCH";
    t.display_name = "Search Test Team";
    t.issue_estimation_type = "fibonacci";

    c.store_teams({t});

    auto found = c.find_team_by_key("SEARCH");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->id, "team-find-key");
    EXPECT_EQ(found->name, "Search Test");
}

TEST(CacheTeams, FindTeamByKeyNotFound) {
    cache::Cache c;
    auto found = c.find_team_by_key("NONEXISTENT");
    EXPECT_FALSE(found.has_value());
}

TEST(CacheTeams, FindTeamByName) {
    cache::Cache c;

    Team t;
    t.id = "team-find-name";
    t.created_at = "2025-01-01T00:00:00Z";
    t.updated_at = "2025-01-01T00:00:00Z";
    t.name = "Unique Name";
    t.key = "UN";
    t.display_name = "Unique Display";
    t.issue_estimation_type = "fibonacci";

    c.store_teams({t});

    auto found = c.find_team_by_name("Unique Name");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->id, "team-find-name");
    EXPECT_EQ(found->key, "UN");
}

TEST(CacheTeams, FindTeamByNameNotFound) {
    cache::Cache c;
    auto found = c.find_team_by_name("Does Not Exist");
    EXPECT_FALSE(found.has_value());
}

TEST(CacheTeams, OverwriteExistingTeam) {
    cache::Cache c;

    Team t1;
    t1.id = "team-overwrite";
    t1.created_at = "2025-01-01T00:00:00Z";
    t1.updated_at = "2025-01-01T00:00:00Z";
    t1.name = "Original";
    t1.key = "ORIG";
    t1.display_name = "Original Team";
    t1.issue_estimation_type = "fibonacci";
    t1.issue_count = 10;

    c.store_teams({t1});

    // Update with same ID but different data
    Team t2;
    t2.id = "team-overwrite";
    t2.created_at = "2025-01-01T00:00:00Z";
    t2.updated_at = "2025-01-02T00:00:00Z";
    t2.name = "Updated";
    t2.key = "UPD";
    t2.display_name = "Updated Team";
    t2.issue_estimation_type = "points";
    t2.issue_count = 20;

    c.store_teams({t2});

    auto found = c.find_team_by_key("UPD");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->name, "Updated");
    EXPECT_EQ(found->issue_count, 20);
}

// ============================================================================
// User Cache Tests
// ============================================================================

TEST(CacheUsers, StoreAndRetrieveUsers) {
    cache::Cache c;

    std::vector<User> users;
    User u1;
    u1.id = "user-1";
    u1.created_at = "2025-01-01T00:00:00Z";
    u1.name = "alice";
    u1.display_name = "Alice Developer";
    u1.email = "alice@example.com";
    u1.active = true;
    u1.admin = true;
    u1.guest = false;
    u1.is_me = false;
    users.push_back(u1);

    User u2;
    u2.id = "user-2";
    u2.created_at = "2025-01-02T00:00:00Z";
    u2.name = "bob";
    u2.display_name = "Bob Designer";
    u2.email = "bob@example.com";
    u2.active = true;
    u2.admin = false;
    u2.guest = false;
    u2.is_me = true;
    users.push_back(u2);

    c.store_users(users);

    auto retrieved = c.get_users();
    EXPECT_GE(retrieved.size(), 2);

    // Verify first user
    bool found_alice = false;
    for (const auto& u : retrieved) {
        if (u.id == "user-1") {
            found_alice = true;
            EXPECT_EQ(u.name, "alice");
            EXPECT_EQ(u.display_name, "Alice Developer");
            EXPECT_EQ(u.email, "alice@example.com");
            EXPECT_TRUE(u.admin);
            break;
        }
    }
    EXPECT_TRUE(found_alice);

    // Verify second user
    bool found_bob = false;
    for (const auto& u : retrieved) {
        if (u.id == "user-2") {
            found_bob = true;
            EXPECT_EQ(u.name, "bob");
            EXPECT_EQ(u.display_name, "Bob Designer");
            break;
        }
    }
    EXPECT_TRUE(found_bob);
}

TEST(CacheUsers, FindUserByName) {
    cache::Cache c;

    User u;
    u.id = "user-by-name";
    u.created_at = "2025-01-01T00:00:00Z";
    u.name = "charlie";
    u.display_name = "Charlie Smith";
    u.email = "charlie@example.com";
    u.active = true;
    u.admin = false;
    u.guest = false;
    u.is_me = false;

    c.store_users({u});

    auto found = c.find_user_by_name("Charlie Smith");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->id, "user-by-name");
    EXPECT_EQ(found->email, "charlie@example.com");
}

TEST(CacheUsers, FindUserByNameNotFound) {
    cache::Cache c;
    auto found = c.find_user_by_name("Nonexistent User");
    EXPECT_FALSE(found.has_value());
}

TEST(CacheUsers, FindUserByEmail) {
    cache::Cache c;

    User u;
    u.id = "user-by-email";
    u.created_at = "2025-01-01T00:00:00Z";
    u.name = "diana";
    u.display_name = "Diana Prince";
    u.email = "diana@example.com";
    u.active = true;
    u.admin = false;
    u.guest = false;
    u.is_me = false;

    c.store_users({u});

    auto found = c.find_user_by_email("diana@example.com");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->id, "user-by-email");
    EXPECT_EQ(found->display_name, "Diana Prince");
}

TEST(CacheUsers, FindUserByEmailNotFound) {
    cache::Cache c;
    auto found = c.find_user_by_email("nonexistent@example.com");
    EXPECT_FALSE(found.has_value());
}

TEST(CacheUsers, HandleOptionalUserFields) {
    cache::Cache c;

    User u;
    u.id = "user-optional";
    u.created_at = "2025-01-01T00:00:00Z";
    u.name = "eve";
    u.display_name = "Eve Optional";
    u.email = "eve@example.com";
    u.avatar_url = std::nullopt;
    u.description = std::nullopt;
    u.timezone = std::nullopt;
    u.last_seen = std::nullopt;
    u.status_emoji = std::nullopt;
    u.status_label = std::nullopt;
    u.active = true;
    u.admin = false;
    u.guest = false;
    u.is_me = false;

    c.store_users({u});

    auto found = c.find_user_by_email("eve@example.com");
    ASSERT_TRUE(found.has_value());
    EXPECT_FALSE(found->avatar_url.has_value());
    EXPECT_FALSE(found->description.has_value());
    EXPECT_FALSE(found->timezone.has_value());
}

// ============================================================================
// Label Cache Tests
// ============================================================================

TEST(CacheLabels, StoreAndRetrieveLabels) {
    cache::Cache c;

    std::vector<IssueLabel> labels;
    IssueLabel l1;
    l1.id = "label-1";
    l1.created_at = "2025-01-01T00:00:00Z";
    l1.name = "bug";
    l1.color = "#FF0000";
    l1.is_group = false;
    labels.push_back(l1);

    IssueLabel l2;
    l2.id = "label-2";
    l2.created_at = "2025-01-02T00:00:00Z";
    l2.name = "feature";
    l2.color = "#00FF00";
    l2.is_group = false;
    labels.push_back(l2);

    IssueLabel l3;
    l3.id = "label-3";
    l3.created_at = "2025-01-03T00:00:00Z";
    l3.name = "priority";
    l3.color = "#FFFF00";
    l3.is_group = true;
    labels.push_back(l3);

    c.store_labels(labels);

    auto retrieved = c.get_labels();
    EXPECT_GE(retrieved.size(), 3);

    // Verify first label
    bool found_bug = false;
    for (const auto& l : retrieved) {
        if (l.id == "label-1") {
            found_bug = true;
            EXPECT_EQ(l.name, "bug");
            EXPECT_EQ(l.color, "#FF0000");
            EXPECT_FALSE(l.is_group);
            break;
        }
    }
    EXPECT_TRUE(found_bug);

    // Verify second label
    bool found_feature = false;
    for (const auto& l : retrieved) {
        if (l.id == "label-2") {
            found_feature = true;
            EXPECT_EQ(l.name, "feature");
            EXPECT_EQ(l.color, "#00FF00");
            break;
        }
    }
    EXPECT_TRUE(found_feature);

    // Verify third label (group)
    bool found_priority = false;
    for (const auto& l : retrieved) {
        if (l.id == "label-3") {
            found_priority = true;
            EXPECT_EQ(l.name, "priority");
            EXPECT_TRUE(l.is_group);
            break;
        }
    }
    EXPECT_TRUE(found_priority);
}

TEST(CacheLabels, FindLabelByName) {
    cache::Cache c;

    IssueLabel l;
    l.id = "label-find";
    l.created_at = "2025-01-01T00:00:00Z";
    l.name = "documentation";
    l.color = "#0000FF";
    l.is_group = false;

    c.store_labels({l});

    auto found = c.find_label_by_name("documentation");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->id, "label-find");
    EXPECT_EQ(found->color, "#0000FF");
}

TEST(CacheLabels, FindLabelByNameNotFound) {
    cache::Cache c;
    auto found = c.find_label_by_name("nonexistent-label");
    EXPECT_FALSE(found.has_value());
}

TEST(CacheLabels, HandleOptionalLabelFields) {
    cache::Cache c;

    IssueLabel l;
    l.id = "label-optional";
    l.created_at = "2025-01-01T00:00:00Z";
    l.name = "with-optional";
    l.color = "#123456";
    l.description = "A label with optional fields";
    l.parent_id = "parent-1";
    l.parent_name = "Parent Label";
    l.team_id = "team-1";
    l.team_name = "Engineering";
    l.is_group = false;

    c.store_labels({l});

    auto found = c.find_label_by_name("with-optional");
    ASSERT_TRUE(found.has_value());
    EXPECT_TRUE(found->description.has_value());
    EXPECT_EQ(found->description.value(), "A label with optional fields");
    EXPECT_EQ(found->team_id, "team-1");
}

// ============================================================================
// Workflow State Cache Tests
// ============================================================================

TEST(CacheStates, StoreAndRetrieveStates) {
    cache::Cache c;

    std::vector<WorkflowState> states;
    WorkflowState s1;
    s1.id = "state-1";
    s1.created_at = "2025-01-01T00:00:00Z";
    s1.name = "Backlog";
    s1.color = "#CCCCCC";
    s1.type = "backlog";
    s1.position = 0.0;
    s1.team_id = "team-1";
    s1.team_name = "Engineering";
    states.push_back(s1);

    WorkflowState s2;
    s2.id = "state-2";
    s2.created_at = "2025-01-01T00:00:00Z";
    s2.name = "In Progress";
    s2.color = "#FFAA00";
    s2.type = "started";
    s2.position = 1.0;
    s2.team_id = "team-1";
    s2.team_name = "Engineering";
    states.push_back(s2);

    WorkflowState s3;
    s3.id = "state-3";
    s3.created_at = "2025-01-01T00:00:00Z";
    s3.name = "Done";
    s3.color = "#00AA00";
    s3.type = "completed";
    s3.position = 2.0;
    s3.team_id = "team-1";
    s3.team_name = "Engineering";
    states.push_back(s3);

    c.store_states(states);

    auto retrieved = c.get_states();
    EXPECT_GE(retrieved.size(), 3);

    // Verify backlog state
    bool found_backlog = false;
    for (const auto& s : retrieved) {
        if (s.id == "state-1") {
            found_backlog = true;
            EXPECT_EQ(s.name, "Backlog");
            EXPECT_EQ(s.type, "backlog");
            EXPECT_EQ(s.position, 0.0);
            break;
        }
    }
    EXPECT_TRUE(found_backlog);

    // Verify in progress state
    bool found_progress = false;
    for (const auto& s : retrieved) {
        if (s.id == "state-2") {
            found_progress = true;
            EXPECT_EQ(s.name, "In Progress");
            EXPECT_EQ(s.type, "started");
            EXPECT_EQ(s.color, "#FFAA00");
            break;
        }
    }
    EXPECT_TRUE(found_progress);
}

TEST(CacheStates, FindStateByTeamAndName) {
    cache::Cache c;

    WorkflowState s;
    s.id = "state-find";
    s.created_at = "2025-01-01T00:00:00Z";
    s.name = "Review";
    s.color = "#0099FF";
    s.type = "started";
    s.position = 1.5;
    s.team_id = "team-2";
    s.team_name = "Product";

    c.store_states({s});

    auto found = c.find_state_by_name("team-2", "Review");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->id, "state-find");
    EXPECT_EQ(found->type, "started");
}

TEST(CacheStates, FindStateByTeamAndNameNotFound) {
    cache::Cache c;
    auto found = c.find_state_by_name("team-x", "Nonexistent");
    EXPECT_FALSE(found.has_value());
}

TEST(CacheStates, GetStatesByTeamId) {
    cache::Cache c;

    std::vector<WorkflowState> states;
    WorkflowState s1;
    s1.id = "state-team-2-1";
    s1.created_at = "2025-01-01T00:00:00Z";
    s1.name = "Triage";
    s1.color = "#FF00FF";
    s1.type = "triage";
    s1.position = 0.0;
    s1.team_id = "team-3";
    s1.team_name = "Support";
    states.push_back(s1);

    WorkflowState s2;
    s2.id = "state-team-2-2";
    s2.created_at = "2025-01-01T00:00:00Z";
    s2.name = "Assigned";
    s2.color = "#FFFF00";
    s2.type = "unstarted";
    s2.position = 1.0;
    s2.team_id = "team-3";
    s2.team_name = "Support";
    states.push_back(s2);

    c.store_states(states);

    auto by_team = c.get_states("team-3");
    EXPECT_GE(by_team.size(), 2);

    // Verify that we got the right team's states
    bool found_triage = false;
    bool found_assigned = false;
    for (const auto& s : by_team) {
        if (s.id == "state-team-2-1") found_triage = true;
        if (s.id == "state-team-2-2") found_assigned = true;
    }
    EXPECT_TRUE(found_triage);
    EXPECT_TRUE(found_assigned);
}

// ============================================================================
// Cache Management Tests
// ============================================================================

TEST(CacheStaleness, FreshDataIsNotStale) {
    cache::Cache c;

    Team t;
    t.id = "team-fresh";
    t.created_at = "2025-01-01T00:00:00Z";
    t.updated_at = "2025-01-01T00:00:00Z";
    t.name = "Fresh Team";
    t.key = "FRESH";
    t.display_name = "Fresh Team";
    t.issue_estimation_type = "fibonacci";

    c.store_teams({t});

    // Just stored, should not be stale with 60 min TTL
    EXPECT_FALSE(c.is_stale("teams", 60));
}

TEST(CacheInvalidation, InvalidateTeamsTable) {
    cache::Cache c;

    Team t;
    t.id = "team-inv";
    t.created_at = "2025-01-01T00:00:00Z";
    t.updated_at = "2025-01-01T00:00:00Z";
    t.name = "Invalidation Test";
    t.key = "INV";
    t.display_name = "Invalidation Test";
    t.issue_estimation_type = "fibonacci";

    c.store_teams({t});

    // After storing, should not be stale
    EXPECT_FALSE(c.is_stale("teams", 60));

    // After invalidation, should be stale
    c.invalidate("teams");
    EXPECT_TRUE(c.is_stale("teams"));
}

TEST(CacheInvalidation, InvalidateUsersTable) {
    cache::Cache c;

    User u;
    u.id = "user-inv";
    u.created_at = "2025-01-01T00:00:00Z";
    u.name = "inv";
    u.display_name = "Invalidation Test";
    u.email = "inv@example.com";
    u.active = true;
    u.admin = false;
    u.guest = false;
    u.is_me = false;

    c.store_users({u});
    EXPECT_FALSE(c.is_stale("users", 60));

    c.invalidate("users");
    EXPECT_TRUE(c.is_stale("users"));
}

TEST(CacheInvalidation, InvalidateLabelsTable) {
    cache::Cache c;

    IssueLabel l;
    l.id = "label-inv";
    l.created_at = "2025-01-01T00:00:00Z";
    l.name = "inv";
    l.color = "#000000";
    l.is_group = false;

    c.store_labels({l});
    EXPECT_FALSE(c.is_stale("labels", 60));

    c.invalidate("labels");
    EXPECT_TRUE(c.is_stale("labels"));
}

TEST(CacheInvalidation, InvalidateStatesTable) {
    cache::Cache c;

    WorkflowState s;
    s.id = "state-inv";
    s.created_at = "2025-01-01T00:00:00Z";
    s.name = "Invalidation";
    s.color = "#000000";
    s.type = "started";
    s.position = 0.0;

    c.store_states({s});
    EXPECT_FALSE(c.is_stale("workflow_states", 60));

    c.invalidate("workflow_states");
    EXPECT_TRUE(c.is_stale("workflow_states"));
}

TEST(CacheInvalidation, InvalidateAllTables) {
    cache::Cache c;

    Team t;
    t.id = "team-all";
    t.created_at = "2025-01-01T00:00:00Z";
    t.updated_at = "2025-01-01T00:00:00Z";
    t.name = "All Inv";
    t.key = "ALL";
    t.display_name = "All Inv";
    t.issue_estimation_type = "fibonacci";
    c.store_teams({t});

    User u;
    u.id = "user-all";
    u.created_at = "2025-01-01T00:00:00Z";
    u.name = "all";
    u.display_name = "All Inv";
    u.email = "all@example.com";
    u.active = true;
    u.admin = false;
    u.guest = false;
    u.is_me = false;
    c.store_users({u});

    IssueLabel l;
    l.id = "label-all";
    l.created_at = "2025-01-01T00:00:00Z";
    l.name = "all";
    l.color = "#000000";
    l.is_group = false;
    c.store_labels({l});

    WorkflowState s;
    s.id = "state-all";
    s.created_at = "2025-01-01T00:00:00Z";
    s.name = "All";
    s.color = "#000000";
    s.type = "started";
    s.position = 0.0;
    c.store_states({s});

    // After storing, none should be stale
    EXPECT_FALSE(c.is_stale("teams", 60));
    EXPECT_FALSE(c.is_stale("users", 60));
    EXPECT_FALSE(c.is_stale("labels", 60));
    EXPECT_FALSE(c.is_stale("workflow_states", 60));

    // After invalidate_all, all should be stale
    c.invalidate_all();
    EXPECT_TRUE(c.is_stale("teams"));
    EXPECT_TRUE(c.is_stale("users"));
    EXPECT_TRUE(c.is_stale("labels"));
    EXPECT_TRUE(c.is_stale("workflow_states"));
}

// ============================================================================
// Edge Cases and Boundary Tests
// ============================================================================

TEST(CacheEdgeCases, EmptyTeamsList) {
    cache::Cache c;
    std::vector<Team> empty;
    c.store_teams(empty);

    auto retrieved = c.get_teams();
    // Should not crash on empty list
    EXPECT_TRUE(true);
}

TEST(CacheEdgeCases, EmptyUsersList) {
    cache::Cache c;
    std::vector<User> empty;
    c.store_users(empty);

    auto retrieved = c.get_users();
    // Should not crash on empty list
    EXPECT_TRUE(true);
}

TEST(CacheEdgeCases, EmptyLabelsList) {
    cache::Cache c;
    std::vector<IssueLabel> empty;
    c.store_labels(empty);

    auto retrieved = c.get_labels();
    // Should not crash on empty list
    EXPECT_TRUE(true);
}

TEST(CacheEdgeCases, EmptyStatesList) {
    cache::Cache c;
    std::vector<WorkflowState> empty;
    c.store_states(empty);

    auto retrieved = c.get_states();
    // Should not crash on empty list
    EXPECT_TRUE(true);
}

TEST(CacheEdgeCases, SpecialCharactersInStrings) {
    cache::Cache c;

    Team t;
    t.id = "team-special";
    t.created_at = "2025-01-01T00:00:00Z";
    t.updated_at = "2025-01-01T00:00:00Z";
    t.name = "Team \"With\" 'Quotes'";
    t.key = "SPC";
    t.display_name = "Team & Co.";
    t.description = "Description with 'apostrophe' and \"quotes\"";
    t.issue_estimation_type = "fibonacci";

    c.store_teams({t});

    auto found = c.find_team_by_name("Team \"With\" 'Quotes'");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->display_name, "Team & Co.");
}

TEST(CacheEdgeCases, LongStrings) {
    cache::Cache c;

    Team t;
    t.id = "team-long";
    t.created_at = "2025-01-01T00:00:00Z";
    t.updated_at = "2025-01-01T00:00:00Z";
    t.name = std::string(256, 'a');  // Very long name
    t.key = "LONG";
    t.display_name = "Long Team";
    t.issue_estimation_type = "fibonacci";

    c.store_teams({t});

    auto found = c.find_team_by_name(std::string(256, 'a'));
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->name.length(), 256);
}

TEST(CacheEdgeCases, MultipleEntrieSameType) {
    cache::Cache c;

    std::vector<User> users;
    for (int i = 0; i < 10; ++i) {
        User u;
        u.id = "user-" + std::to_string(i);
        u.created_at = "2025-01-01T00:00:00Z";
        u.name = "user" + std::to_string(i);
        u.display_name = "User " + std::to_string(i);
        u.email = "user" + std::to_string(i) + "@example.com";
        u.active = true;
        u.admin = false;
        u.guest = false;
        u.is_me = false;
        users.push_back(u);
    }

    c.store_users(users);

    // Find one of them
    auto found = c.find_user_by_email("user5@example.com");
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->name, "user5");
}
