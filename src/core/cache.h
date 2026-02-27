#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

// Forward declarations — avoid pulling in heavy model headers
struct Team;
struct User;
struct IssueLabel;
struct WorkflowState;

struct sqlite3;

namespace cache {

class Cache {
public:
    Cache();   // Opens/creates ~/.config/lin/cache.db, runs migrations
    ~Cache();  // Closes db

    // Non-copyable, movable
    Cache(const Cache&) = delete;
    Cache& operator=(const Cache&) = delete;
    Cache(Cache&& other) noexcept;
    Cache& operator=(Cache&& other) noexcept;

    // Teams
    void store_teams(const std::vector<Team>& teams);
    std::vector<Team> get_teams();
    std::optional<Team> find_team_by_key(const std::string& key);
    std::optional<Team> find_team_by_name(const std::string& name);

    // Users
    void store_users(const std::vector<User>& users);
    std::vector<User> get_users();
    std::optional<User> find_user_by_name(const std::string& display_name);
    std::optional<User> find_user_by_email(const std::string& email);

    // Labels
    void store_labels(const std::vector<IssueLabel>& labels);
    std::vector<IssueLabel> get_labels();
    std::optional<IssueLabel> find_label_by_name(const std::string& name);

    // Workflow States
    void store_states(const std::vector<WorkflowState>& states);
    std::vector<WorkflowState> get_states(const std::string& team_id = "");
    std::optional<WorkflowState> find_state_by_name(
        const std::string& team_id,
        const std::string& name
    );

    // Cache management
    bool is_stale(const std::string& table, int max_age_minutes = 60);
    void invalidate(const std::string& table);
    void invalidate_all();

    // Check if database is open
    bool is_open() const;

private:
    sqlite3* db_ = nullptr;

    void create_tables();
    void update_timestamp(const std::string& table);
    void exec(const std::string& sql);
};

// Get the singleton cache instance
Cache& get_cache();

// Get the cache database path
std::string cache_path();

}  // namespace cache
