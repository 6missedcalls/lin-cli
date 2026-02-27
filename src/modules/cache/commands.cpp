#include "modules/cache/commands.h"

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/cache.h"
#include "core/error.h"
#include "core/output.h"
#include "modules/labels/api.h"
#include "modules/teams/api.h"
#include "modules/users/api.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Constants
// ---------------------------------------------------------------------------

namespace {

const std::set<std::string> VALID_TABLES = {
    "teams",
    "users",
    "labels",
    "workflow_states"
};

// ---------------------------------------------------------------------------
// Status renderers
// ---------------------------------------------------------------------------

struct TableStatus {
    std::string name;
    size_t record_count = 0;
    bool is_stale = false;
    bool is_empty = false;
};

void render_status_table(const std::vector<TableStatus>& statuses) {
    TableRenderer table({
        {"TABLE",        5, 20, false},
        {"RECORDS",      4, 10, true},
        {"STALE",        4, 8,  false}
    });

    for (const auto& s : statuses) {
        table.add_row({
            s.name,
            s.is_empty ? "0" : std::to_string(s.record_count),
            s.is_empty ? "never populated" : (s.is_stale ? "yes" : "no")
        });
    }

    table.render(std::cout);
}

void render_status_json(const std::vector<TableStatus>& statuses) {
    json arr = json::array();
    for (const auto& s : statuses) {
        json j;
        j["table"] = s.name;
        j["records"] = static_cast<int>(s.record_count);
        j["stale"] = s.is_stale;
        j["neverPopulated"] = s.is_empty;
        arr.push_back(j);
    }
    output_json(arr);
}

// ---------------------------------------------------------------------------
// Refresh helpers
// ---------------------------------------------------------------------------

std::vector<Team> fetch_all_teams() {
    std::vector<Team> all_teams;
    std::optional<std::string> cursor;

    while (true) {
        auto conn = teams_api::list_teams(50, cursor);
        for (auto& t : conn.nodes) {
            all_teams.push_back(std::move(t));
        }
        if (!conn.page_info.has_next_page || !conn.page_info.end_cursor.has_value()) {
            break;
        }
        cursor = conn.page_info.end_cursor;
    }

    return all_teams;
}

std::vector<User> fetch_all_users() {
    std::vector<User> all_users;
    std::optional<std::string> cursor;

    while (true) {
        auto conn = users_api::list_users(50, cursor);
        for (auto& u : conn.nodes) {
            all_users.push_back(std::move(u));
        }
        if (!conn.page_info.has_next_page || !conn.page_info.end_cursor.has_value()) {
            break;
        }
        cursor = conn.page_info.end_cursor;
    }

    return all_users;
}

std::vector<IssueLabel> fetch_all_labels() {
    std::vector<IssueLabel> all_labels;
    std::optional<std::string> cursor;

    while (true) {
        auto conn = labels_api::list_labels(50, cursor);
        for (auto& l : conn.nodes) {
            all_labels.push_back(std::move(l));
        }
        if (!conn.page_info.has_next_page || !conn.page_info.end_cursor.has_value()) {
            break;
        }
        cursor = conn.page_info.end_cursor;
    }

    return all_labels;
}

std::vector<WorkflowState> fetch_all_workflow_states(const std::vector<Team>& teams) {
    std::vector<WorkflowState> all_states;

    for (const auto& team : teams) {
        auto conn = teams_api::list_workflow_states(team.id);
        for (auto& s : conn.nodes) {
            all_states.push_back(std::move(s));
        }
    }

    return all_states;
}

void do_refresh_teams() {
    std::cout << "Refreshing teams..." << std::flush;
    auto teams = fetch_all_teams();
    cache::get_cache().store_teams(teams);
    std::cout << " done (" << teams.size() << " records)" << std::endl;
}

void do_refresh_users() {
    std::cout << "Refreshing users..." << std::flush;
    auto users = fetch_all_users();
    cache::get_cache().store_users(users);
    std::cout << " done (" << users.size() << " records)" << std::endl;
}

void do_refresh_labels() {
    std::cout << "Refreshing labels..." << std::flush;
    auto labels = fetch_all_labels();
    cache::get_cache().store_labels(labels);
    std::cout << " done (" << labels.size() << " records)" << std::endl;
}

void do_refresh_workflow_states() {
    std::cout << "Refreshing workflow_states..." << std::flush;
    auto cached_teams = cache::get_cache().get_teams();

    // If no teams cached, fetch them first so we can get states per team
    if (cached_teams.empty()) {
        cached_teams = fetch_all_teams();
        cache::get_cache().store_teams(cached_teams);
    }

    auto states = fetch_all_workflow_states(cached_teams);
    cache::get_cache().store_states(states);
    std::cout << " done (" << states.size() << " records)" << std::endl;
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void cache_commands::register_commands(CLI::App& app) {
    auto* cache_cmd = app.add_subcommand("cache", "Manage local cache of Linear data");
    cache_cmd->require_subcommand(1);

    // -----------------------------------------------------------------------
    // cache clear [--table <name>]
    // -----------------------------------------------------------------------
    {
        auto* cmd = cache_cmd->add_subcommand("clear", "Clear cached data");

        auto table_name = std::make_shared<std::string>();
        cmd->add_option("--table,-t", *table_name,
            "Table to clear (teams, users, labels, workflow_states). "
            "Clears all tables if omitted.");

        cmd->callback([table_name]() {
            try {
                if (!table_name->empty()) {
                    if (VALID_TABLES.find(*table_name) == VALID_TABLES.end()) {
                        print_error(
                            "Unknown cache table: '" + *table_name + "'. "
                            "Valid tables: teams, users, labels, workflow_states"
                        );
                        return;
                    }
                    cache::get_cache().invalidate(*table_name);
                    print_success("Cache table '" + *table_name + "' cleared.");
                } else {
                    cache::get_cache().invalidate_all();
                    print_success("Cache cleared.");
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            } catch (const std::exception& e) {
                print_error(std::string("Failed to clear cache: ") + e.what());
                throw std::runtime_error(std::string("Cache clear failed: ") + e.what());
            }
        });
    }

    // -----------------------------------------------------------------------
    // cache status
    // -----------------------------------------------------------------------
    {
        auto* cmd = cache_cmd->add_subcommand("status", "Show staleness status for all cache tables");

        cmd->callback([]() {
            try {
                auto& c = cache::get_cache();

                const std::vector<std::string> table_names = {
                    "teams", "users", "labels", "workflow_states"
                };

                std::vector<TableStatus> statuses;
                statuses.reserve(table_names.size());

                for (const auto& name : table_names) {
                    TableStatus status;
                    status.name = name;
                    status.is_stale = c.is_stale(name);

                    if (name == "teams") {
                        auto records = c.get_teams();
                        status.record_count = records.size();
                        status.is_empty = records.empty();
                    } else if (name == "users") {
                        auto records = c.get_users();
                        status.record_count = records.size();
                        status.is_empty = records.empty();
                    } else if (name == "labels") {
                        auto records = c.get_labels();
                        status.record_count = records.size();
                        status.is_empty = records.empty();
                    } else if (name == "workflow_states") {
                        auto records = c.get_states();
                        status.record_count = records.size();
                        status.is_empty = records.empty();
                    }

                    statuses.push_back(std::move(status));
                }

                if (get_output_format() == OutputFormat::Json) {
                    render_status_json(statuses);
                } else {
                    render_status_table(statuses);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            } catch (const std::exception& e) {
                print_error(std::string("Failed to read cache status: ") + e.what());
                throw std::runtime_error(std::string("Cache status failed: ") + e.what());
            }
        });
    }

    // -----------------------------------------------------------------------
    // cache refresh [--table <name>]
    // -----------------------------------------------------------------------
    {
        auto* cmd = cache_cmd->add_subcommand("refresh", "Fetch fresh data from the API and store in cache");

        auto table_name = std::make_shared<std::string>();
        cmd->add_option("--table,-t", *table_name,
            "Table to refresh (teams, users, labels, workflow_states, states). "
            "Refreshes all tables if omitted.");

        cmd->callback([table_name]() {
            try {
                if (!table_name->empty()) {
                    // Normalise "states" alias
                    const std::string& tbl = *table_name;

                    if (tbl == "teams") {
                        do_refresh_teams();
                    } else if (tbl == "users") {
                        do_refresh_users();
                    } else if (tbl == "labels") {
                        do_refresh_labels();
                    } else if (tbl == "workflow_states" || tbl == "states") {
                        do_refresh_workflow_states();
                    } else {
                        print_error(
                            "Unknown cache table: '" + tbl + "'. "
                            "Valid tables: teams, users, labels, workflow_states, states"
                        );
                        return;
                    }
                } else {
                    // Refresh all — teams first so workflow_states can reuse them
                    do_refresh_teams();
                    do_refresh_users();
                    do_refresh_labels();
                    do_refresh_workflow_states();
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            } catch (const std::exception& e) {
                print_error(std::string("Failed to refresh cache: ") + e.what());
                throw std::runtime_error(std::string("Cache refresh failed: ") + e.what());
            }
        });
    }
}
