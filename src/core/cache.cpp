#include "core/cache.h"

#include "modules/labels/model.h"
#include "modules/teams/model.h"
#include "modules/users/model.h"

#include <sqlite3.h>

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace cache {

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

// Safely extract a TEXT column that may be NULL from a statement row.
static std::string col_text(sqlite3_stmt* stmt, int col) {
    const unsigned char* raw = sqlite3_column_text(stmt, col);
    return raw ? std::string(reinterpret_cast<const char*>(raw)) : std::string{};
}

// Safely extract a TEXT column as std::optional<std::string>.
static std::optional<std::string> col_opt_text(sqlite3_stmt* stmt, int col) {
    const unsigned char* raw = sqlite3_column_text(stmt, col);
    if (raw == nullptr) {
        return std::nullopt;
    }
    return std::string(reinterpret_cast<const char*>(raw));
}

// ---------------------------------------------------------------------------
// cache_path
// ---------------------------------------------------------------------------

std::string cache_path() {
    const char* home = std::getenv("HOME");
    std::string dir = std::string(home ? home : ".") + "/.config/lin";
    std::filesystem::create_directories(dir);
    return dir + "/cache.db";
}

// ---------------------------------------------------------------------------
// Constructor / Destructor / Move
// ---------------------------------------------------------------------------

Cache::Cache() {
    int rc = sqlite3_open(cache_path().c_str(), &db_);
    if (rc != SQLITE_OK) {
        std::string msg = "Failed to open cache database: ";
        if (db_) {
            msg += sqlite3_errmsg(db_);
            sqlite3_close(db_);
            db_ = nullptr;
        } else {
            msg += "out of memory";
        }
        throw std::runtime_error(msg);
    }

    // WAL mode for better concurrency and performance
    exec("PRAGMA journal_mode=WAL");
    exec("PRAGMA synchronous=NORMAL");
    exec("PRAGMA foreign_keys=ON");

    create_tables();
}

Cache::~Cache() {
    if (db_) {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

Cache::Cache(Cache&& other) noexcept : db_(other.db_) {
    other.db_ = nullptr;
}

Cache& Cache::operator=(Cache&& other) noexcept {
    if (this != &other) {
        if (db_) {
            sqlite3_close(db_);
        }
        db_ = other.db_;
        other.db_ = nullptr;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------

void Cache::exec(const std::string& sql) {
    char* errmsg = nullptr;
    int rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK) {
        std::string msg = "SQLite error: ";
        if (errmsg) {
            msg += errmsg;
            sqlite3_free(errmsg);
        }
        throw std::runtime_error(msg);
    }
}

void Cache::create_tables() {
    exec(R"sql(
        CREATE TABLE IF NOT EXISTS cache_meta (
            table_name TEXT PRIMARY KEY,
            updated_at INTEGER NOT NULL
        )
    )sql");

    exec(R"sql(
        CREATE TABLE IF NOT EXISTS teams (
            id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            key TEXT NOT NULL,
            description TEXT,
            color TEXT,
            display_name TEXT,
            cycles_enabled INTEGER DEFAULT 0,
            triage_enabled INTEGER DEFAULT 0,
            issue_count INTEGER DEFAULT 0
        )
    )sql");

    exec(R"sql(
        CREATE TABLE IF NOT EXISTS users (
            id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            display_name TEXT NOT NULL,
            email TEXT NOT NULL,
            active INTEGER DEFAULT 1,
            admin INTEGER DEFAULT 0
        )
    )sql");

    exec(R"sql(
        CREATE TABLE IF NOT EXISTS labels (
            id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            color TEXT NOT NULL,
            description TEXT,
            is_group INTEGER DEFAULT 0,
            team_id TEXT,
            team_name TEXT
        )
    )sql");

    exec(R"sql(
        CREATE TABLE IF NOT EXISTS workflow_states (
            id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            color TEXT NOT NULL,
            type TEXT NOT NULL,
            position REAL DEFAULT 0.0,
            team_id TEXT,
            team_name TEXT,
            description TEXT
        )
    )sql");

    // Indices for frequent lookup patterns
    exec("CREATE INDEX IF NOT EXISTS idx_teams_key ON teams(key)");
    exec("CREATE INDEX IF NOT EXISTS idx_teams_name ON teams(name)");
    exec("CREATE INDEX IF NOT EXISTS idx_users_display_name ON users(display_name)");
    exec("CREATE INDEX IF NOT EXISTS idx_users_email ON users(email)");
    exec("CREATE INDEX IF NOT EXISTS idx_labels_name ON labels(name)");
    exec("CREATE INDEX IF NOT EXISTS idx_states_team_id ON workflow_states(team_id)");
    exec("CREATE INDEX IF NOT EXISTS idx_states_name ON workflow_states(name)");
}

void Cache::update_timestamp(const std::string& table) {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "INSERT OR REPLACE INTO cache_meta (table_name, updated_at) VALUES (?, ?)",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, table.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(now));
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// ---------------------------------------------------------------------------
// is_open
// ---------------------------------------------------------------------------

bool Cache::is_open() const {
    return db_ != nullptr;
}

// ---------------------------------------------------------------------------
// Cache management
// ---------------------------------------------------------------------------

bool Cache::is_stale(const std::string& table, int max_age_minutes) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT updated_at FROM cache_meta WHERE table_name = ?",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, table.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_int64 updated = sqlite3_column_int64(stmt, 0);
        sqlite3_finalize(stmt);

        auto now = std::chrono::system_clock::now();
        auto updated_time = std::chrono::system_clock::from_time_t(
            static_cast<std::time_t>(updated)
        );
        auto age = std::chrono::duration_cast<std::chrono::minutes>(now - updated_time);
        return age.count() >= max_age_minutes;
    }

    sqlite3_finalize(stmt);
    return true;  // No record means stale
}

void Cache::invalidate(const std::string& table) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "DELETE FROM cache_meta WHERE table_name = ?",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, table.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void Cache::invalidate_all() {
    exec("DELETE FROM cache_meta");
}

// ---------------------------------------------------------------------------
// Teams
// ---------------------------------------------------------------------------

void Cache::store_teams(const std::vector<Team>& teams) {
    exec("BEGIN TRANSACTION");
    exec("DELETE FROM teams");

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        R"sql(
            INSERT INTO teams
                (id, name, key, description, color, display_name,
                 cycles_enabled, triage_enabled, issue_count)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
        )sql",
        -1, &stmt, nullptr
    );

    for (const auto& t : teams) {
        sqlite3_bind_text(stmt, 1, t.id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, t.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, t.key.c_str(), -1, SQLITE_TRANSIENT);

        if (t.description.has_value()) {
            sqlite3_bind_text(stmt, 4, t.description->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 4);
        }

        if (t.color.has_value()) {
            sqlite3_bind_text(stmt, 5, t.color->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 5);
        }

        sqlite3_bind_text(stmt, 6, t.display_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 7, t.cycles_enabled ? 1 : 0);
        sqlite3_bind_int(stmt, 8, t.triage_enabled ? 1 : 0);
        sqlite3_bind_int(stmt, 9, t.issue_count);

        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    update_timestamp("teams");
    exec("COMMIT");
}

static Team row_to_team(sqlite3_stmt* stmt) {
    Team t;
    t.id           = col_text(stmt, 0);
    t.name         = col_text(stmt, 1);
    t.key          = col_text(stmt, 2);
    t.description  = col_opt_text(stmt, 3);
    t.color        = col_opt_text(stmt, 4);
    t.display_name = col_text(stmt, 5);
    t.cycles_enabled  = sqlite3_column_int(stmt, 6) != 0;
    t.triage_enabled  = sqlite3_column_int(stmt, 7) != 0;
    t.issue_count     = sqlite3_column_int(stmt, 8);
    return t;
}

std::vector<Team> Cache::get_teams() {
    std::vector<Team> result;

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, key, description, color, display_name, "
        "cycles_enabled, triage_enabled, issue_count FROM teams ORDER BY name",
        -1, &stmt, nullptr
    );

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.push_back(row_to_team(stmt));
    }

    sqlite3_finalize(stmt);
    return result;
}

std::optional<Team> Cache::find_team_by_key(const std::string& key) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, key, description, color, display_name, "
        "cycles_enabled, triage_enabled, issue_count FROM teams WHERE key = ?",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);

    std::optional<Team> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = row_to_team(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
}

std::optional<Team> Cache::find_team_by_name(const std::string& name) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, key, description, color, display_name, "
        "cycles_enabled, triage_enabled, issue_count FROM teams "
        "WHERE name = ? COLLATE NOCASE",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

    std::optional<Team> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = row_to_team(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
}

// ---------------------------------------------------------------------------
// Users
// ---------------------------------------------------------------------------

void Cache::store_users(const std::vector<User>& users) {
    exec("BEGIN TRANSACTION");
    exec("DELETE FROM users");

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        R"sql(
            INSERT INTO users (id, name, display_name, email, active, admin)
            VALUES (?, ?, ?, ?, ?, ?)
        )sql",
        -1, &stmt, nullptr
    );

    for (const auto& u : users) {
        sqlite3_bind_text(stmt, 1, u.id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, u.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, u.display_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, u.email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 5, u.active ? 1 : 0);
        sqlite3_bind_int(stmt, 6, u.admin ? 1 : 0);

        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    update_timestamp("users");
    exec("COMMIT");
}

static User row_to_user(sqlite3_stmt* stmt) {
    User u;
    u.id           = col_text(stmt, 0);
    u.name         = col_text(stmt, 1);
    u.display_name = col_text(stmt, 2);
    u.email        = col_text(stmt, 3);
    u.active       = sqlite3_column_int(stmt, 4) != 0;
    u.admin        = sqlite3_column_int(stmt, 5) != 0;
    return u;
}

std::vector<User> Cache::get_users() {
    std::vector<User> result;

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, display_name, email, active, admin FROM users "
        "ORDER BY display_name",
        -1, &stmt, nullptr
    );

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.push_back(row_to_user(stmt));
    }

    sqlite3_finalize(stmt);
    return result;
}

std::optional<User> Cache::find_user_by_name(const std::string& display_name) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, display_name, email, active, admin FROM users "
        "WHERE display_name = ? COLLATE NOCASE",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, display_name.c_str(), -1, SQLITE_TRANSIENT);

    std::optional<User> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = row_to_user(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
}

std::optional<User> Cache::find_user_by_email(const std::string& email) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, display_name, email, active, admin FROM users "
        "WHERE email = ? COLLATE NOCASE",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    std::optional<User> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = row_to_user(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
}

// ---------------------------------------------------------------------------
// Labels
// ---------------------------------------------------------------------------

void Cache::store_labels(const std::vector<IssueLabel>& labels) {
    exec("BEGIN TRANSACTION");
    exec("DELETE FROM labels");

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        R"sql(
            INSERT INTO labels (id, name, color, description, is_group, team_id, team_name)
            VALUES (?, ?, ?, ?, ?, ?, ?)
        )sql",
        -1, &stmt, nullptr
    );

    for (const auto& l : labels) {
        sqlite3_bind_text(stmt, 1, l.id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, l.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, l.color.c_str(), -1, SQLITE_TRANSIENT);

        if (l.description.has_value()) {
            sqlite3_bind_text(stmt, 4, l.description->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 4);
        }

        sqlite3_bind_int(stmt, 5, l.is_group ? 1 : 0);

        if (l.team_id.has_value()) {
            sqlite3_bind_text(stmt, 6, l.team_id->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 6);
        }

        if (l.team_name.has_value()) {
            sqlite3_bind_text(stmt, 7, l.team_name->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 7);
        }

        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    update_timestamp("labels");
    exec("COMMIT");
}

static IssueLabel row_to_label(sqlite3_stmt* stmt) {
    IssueLabel l;
    l.id          = col_text(stmt, 0);
    l.name        = col_text(stmt, 1);
    l.color       = col_text(stmt, 2);
    l.description = col_opt_text(stmt, 3);
    l.is_group    = sqlite3_column_int(stmt, 4) != 0;
    l.team_id     = col_opt_text(stmt, 5);
    l.team_name   = col_opt_text(stmt, 6);
    return l;
}

std::vector<IssueLabel> Cache::get_labels() {
    std::vector<IssueLabel> result;

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, color, description, is_group, team_id, team_name "
        "FROM labels ORDER BY name",
        -1, &stmt, nullptr
    );

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.push_back(row_to_label(stmt));
    }

    sqlite3_finalize(stmt);
    return result;
}

std::optional<IssueLabel> Cache::find_label_by_name(const std::string& name) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, color, description, is_group, team_id, team_name "
        "FROM labels WHERE name = ? COLLATE NOCASE",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

    std::optional<IssueLabel> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = row_to_label(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
}

// ---------------------------------------------------------------------------
// Workflow States
// ---------------------------------------------------------------------------

void Cache::store_states(const std::vector<WorkflowState>& states) {
    exec("BEGIN TRANSACTION");
    exec("DELETE FROM workflow_states");

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        R"sql(
            INSERT INTO workflow_states
                (id, name, color, type, position, team_id, team_name, description)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?)
        )sql",
        -1, &stmt, nullptr
    );

    for (const auto& s : states) {
        sqlite3_bind_text(stmt, 1, s.id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, s.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, s.color.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, s.type.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 5, s.position);

        if (s.team_id.has_value()) {
            sqlite3_bind_text(stmt, 6, s.team_id->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 6);
        }

        if (s.team_name.has_value()) {
            sqlite3_bind_text(stmt, 7, s.team_name->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 7);
        }

        if (s.description.has_value()) {
            sqlite3_bind_text(stmt, 8, s.description->c_str(), -1, SQLITE_TRANSIENT);
        } else {
            sqlite3_bind_null(stmt, 8);
        }

        sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    update_timestamp("workflow_states");
    exec("COMMIT");
}

static WorkflowState row_to_state(sqlite3_stmt* stmt) {
    WorkflowState s;
    s.id          = col_text(stmt, 0);
    s.name        = col_text(stmt, 1);
    s.color       = col_text(stmt, 2);
    s.type        = col_text(stmt, 3);
    s.position    = sqlite3_column_double(stmt, 4);
    s.team_id     = col_opt_text(stmt, 5);
    s.team_name   = col_opt_text(stmt, 6);
    s.description = col_opt_text(stmt, 7);
    return s;
}

std::vector<WorkflowState> Cache::get_states(const std::string& team_id) {
    std::vector<WorkflowState> result;

    sqlite3_stmt* stmt = nullptr;
    if (team_id.empty()) {
        sqlite3_prepare_v2(
            db_,
            "SELECT id, name, color, type, position, team_id, team_name, description "
            "FROM workflow_states ORDER BY team_id, position",
            -1, &stmt, nullptr
        );
    } else {
        sqlite3_prepare_v2(
            db_,
            "SELECT id, name, color, type, position, team_id, team_name, description "
            "FROM workflow_states WHERE team_id = ? ORDER BY position",
            -1, &stmt, nullptr
        );
        sqlite3_bind_text(stmt, 1, team_id.c_str(), -1, SQLITE_TRANSIENT);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.push_back(row_to_state(stmt));
    }

    sqlite3_finalize(stmt);
    return result;
}

std::optional<WorkflowState> Cache::find_state_by_name(
    const std::string& team_id,
    const std::string& name
) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(
        db_,
        "SELECT id, name, color, type, position, team_id, team_name, description "
        "FROM workflow_states WHERE team_id = ? AND name = ? COLLATE NOCASE",
        -1, &stmt, nullptr
    );
    sqlite3_bind_text(stmt, 1, team_id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);

    std::optional<WorkflowState> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = row_to_state(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
}

// ---------------------------------------------------------------------------
// Singleton
// ---------------------------------------------------------------------------

Cache& get_cache() {
    static Cache instance;
    return instance;
}

}  // namespace cache
