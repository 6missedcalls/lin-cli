#include "modules/teams/commands.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/teams/api.h"
#include "modules/teams/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

std::string format_percent(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << (value * 100.0) << "%";
    return oss.str();
}

std::string bool_str(bool value) {
    return value ? "yes" : "no";
}

// ---------------------------------------------------------------------------
// Team renderers
// ---------------------------------------------------------------------------

void render_team_table(const std::vector<Team>& teams) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"KEY", "NAME", "ISSUES", "CYCLES", "TRIAGE"});
        for (const auto& team : teams) {
            output_csv_row({
                team.key,
                team.name,
                std::to_string(team.issue_count),
                bool_str(team.cycles_enabled),
                bool_str(team.triage_enabled)
            });
        }
        return;
    }

    TableRenderer table({
        {"KEY",    3, 10, false},
        {"NAME",   4, 40, false},
        {"ISSUES", 4, 8,  true},
        {"CYCLES", 4, 8,  false},
        {"TRIAGE", 4, 8,  false}
    });

    for (const auto& team : teams) {
        table.add_row({
            team.key,
            team.name,
            std::to_string(team.issue_count),
            bool_str(team.cycles_enabled),
            bool_str(team.triage_enabled)
        });
    }

    if (table.empty()) {
        print_warning("No teams found.");
        return;
    }

    table.render(std::cout);
}

void render_team_json(const std::vector<Team>& teams) {
    json arr = json::array();
    for (const auto& team : teams) {
        json j;
        j["id"] = team.id;
        j["name"] = team.name;
        j["key"] = team.key;
        j["displayName"] = team.display_name;
        j["description"] = team.description.has_value() ? json(team.description.value()) : json(nullptr);
        j["icon"] = team.icon.has_value() ? json(team.icon.value()) : json(nullptr);
        j["color"] = team.color.has_value() ? json(team.color.value()) : json(nullptr);
        j["timezone"] = team.timezone.has_value() ? json(team.timezone.value()) : json(nullptr);
        j["cyclesEnabled"] = team.cycles_enabled;
        j["triageEnabled"] = team.triage_enabled;
        j["private"] = team.private_team;
        j["issueCount"] = team.issue_count;
        j["cycleStartDay"] = team.cycle_start_day;
        j["cycleDuration"] = team.cycle_duration;
        j["cycleCooldownTime"] = team.cycle_cooldown_time;
        j["issueEstimationType"] = team.issue_estimation_type;
        j["createdAt"] = team.created_at;
        j["updatedAt"] = team.updated_at;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_team_detail(const Team& team) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = team.id;
        j["name"] = team.name;
        j["key"] = team.key;
        j["displayName"] = team.display_name;
        j["description"] = team.description.has_value() ? json(team.description.value()) : json(nullptr);
        j["icon"] = team.icon.has_value() ? json(team.icon.value()) : json(nullptr);
        j["color"] = team.color.has_value() ? json(team.color.value()) : json(nullptr);
        j["timezone"] = team.timezone.has_value() ? json(team.timezone.value()) : json(nullptr);
        j["cyclesEnabled"] = team.cycles_enabled;
        j["triageEnabled"] = team.triage_enabled;
        j["private"] = team.private_team;
        j["issueCount"] = team.issue_count;
        j["cycleStartDay"] = team.cycle_start_day;
        j["cycleDuration"] = team.cycle_duration;
        j["cycleCooldownTime"] = team.cycle_cooldown_time;
        j["issueEstimationType"] = team.issue_estimation_type;
        j["createdAt"] = team.created_at;
        j["updatedAt"] = team.updated_at;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section("[" + team.key + "]  " + team.name);

    if (team.description.has_value() && !team.description.value().empty()) {
        detail.add_field("Description", team.description.value());
    }
    if (team.timezone.has_value()) {
        detail.add_field("Timezone", team.timezone.value());
    }
    detail.add_field("Issues", std::to_string(team.issue_count));
    detail.add_field("Cycles Enabled", bool_str(team.cycles_enabled));
    detail.add_field("Triage Enabled", bool_str(team.triage_enabled));
    detail.add_field("Private", bool_str(team.private_team));
    detail.add_field("Estimation", team.issue_estimation_type);

    if (team.cycles_enabled) {
        detail.add_field("Cycle Duration", std::to_string(static_cast<int>(team.cycle_duration)) + " weeks");
        detail.add_field("Cycle Cooldown", std::to_string(static_cast<int>(team.cycle_cooldown_time)) + " days");
    }

    detail.add_field("Created", team.created_at);
    detail.add_field("Updated", team.updated_at);

    detail.render(std::cout);
}

// ---------------------------------------------------------------------------
// WorkflowState renderers
// ---------------------------------------------------------------------------

void render_states_table(const std::vector<WorkflowState>& states) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "TYPE", "COLOR", "POSITION"});
        for (const auto& state : states) {
            output_csv_row({
                state.name,
                state.type,
                state.color,
                std::to_string(static_cast<int>(state.position))
            });
        }
        return;
    }

    TableRenderer table({
        {"NAME",     4, 30, false},
        {"TYPE",     4, 12, false},
        {"COLOR",    4, 10, false},
        {"POSITION", 4, 8,  true}
    });

    for (const auto& state : states) {
        std::string type_str = color::state_type(state.type, state.type);
        std::string color_str = state.color.empty()
            ? state.color
            : color::from_hex(state.color, state.color);

        table.add_row({
            state.name,
            type_str,
            color_str,
            std::to_string(static_cast<int>(state.position))
        });
    }

    if (table.empty()) {
        print_warning("No workflow states found.");
        return;
    }

    table.render(std::cout);
}

void render_states_json(const std::vector<WorkflowState>& states) {
    json arr = json::array();
    for (const auto& state : states) {
        json j;
        j["id"] = state.id;
        j["name"] = state.name;
        j["type"] = state.type;
        j["color"] = state.color;
        j["position"] = state.position;
        j["description"] = state.description.has_value() ? json(state.description.value()) : json(nullptr);
        j["teamId"] = state.team_id.has_value() ? json(state.team_id.value()) : json(nullptr);
        j["teamName"] = state.team_name.has_value() ? json(state.team_name.value()) : json(nullptr);
        j["createdAt"] = state.created_at;
        arr.push_back(j);
    }
    output_json(arr);
}

// ---------------------------------------------------------------------------
// Member renderers
// ---------------------------------------------------------------------------

void render_members_table(const std::vector<TeamMember>& members) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "EMAIL", "ADMIN", "ACTIVE"});
        for (const auto& m : members) {
            output_csv_row({m.display_name, m.email, bool_str(m.admin), bool_str(m.active)});
        }
        return;
    }

    TableRenderer table({
        {"NAME",   4, 30, false},
        {"EMAIL",  4, 40, false},
        {"ADMIN",  4, 8,  false},
        {"ACTIVE", 4, 8,  false}
    });

    for (const auto& m : members) {
        table.add_row({m.display_name, m.email, bool_str(m.admin), bool_str(m.active)});
    }

    if (table.empty()) {
        print_warning("No members found.");
        return;
    }

    table.render(std::cout);
}

void render_members_json(const std::vector<TeamMember>& members) {
    json arr = json::array();
    for (const auto& m : members) {
        json j;
        j["id"] = m.id;
        j["displayName"] = m.display_name;
        j["email"] = m.email;
        j["admin"] = m.admin;
        j["active"] = m.active;
        arr.push_back(j);
    }
    output_json(arr);
}

// ---------------------------------------------------------------------------
// Label renderers
// ---------------------------------------------------------------------------

void render_labels_table(const std::vector<TeamLabel>& labels) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "COLOR", "GROUP"});
        for (const auto& l : labels) {
            output_csv_row({l.name, l.color, l.parent_name.value_or("")});
        }
        return;
    }

    TableRenderer table({
        {"NAME",  4, 30, false},
        {"COLOR", 4, 12, false},
        {"GROUP", 4, 30, false}
    });

    for (const auto& l : labels) {
        std::string color_str = l.color.empty()
            ? l.color
            : color::from_hex(l.color, l.color);

        table.add_row({
            l.name,
            color_str,
            l.parent_name.value_or("")
        });
    }

    if (table.empty()) {
        print_warning("No labels found.");
        return;
    }

    table.render(std::cout);
}

void render_labels_json(const std::vector<TeamLabel>& labels) {
    json arr = json::array();
    for (const auto& l : labels) {
        json j;
        j["id"] = l.id;
        j["name"] = l.name;
        j["color"] = l.color;
        j["description"] = l.description.has_value() ? json(l.description.value()) : json(nullptr);
        j["parentId"] = l.parent_id.has_value() ? json(l.parent_id.value()) : json(nullptr);
        j["parentName"] = l.parent_name.has_value() ? json(l.parent_name.value()) : json(nullptr);
        arr.push_back(j);
    }
    output_json(arr);
}

// ---------------------------------------------------------------------------
// Cycle renderers
// ---------------------------------------------------------------------------

void render_cycles_table(const std::vector<TeamCycle>& cycles) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NUMBER", "NAME", "START", "END", "PROGRESS", "ACTIVE"});
        for (const auto& c : cycles) {
            output_csv_row({
                std::to_string(c.number),
                c.name.value_or(""),
                c.starts_at,
                c.ends_at,
                format_percent(c.progress),
                bool_str(c.is_active)
            });
        }
        return;
    }

    TableRenderer table({
        {"NUMBER",   4, 8,  true},
        {"NAME",     4, 30, false},
        {"START",    4, 24, false},
        {"END",      4, 24, false},
        {"PROGRESS", 4, 10, true},
        {"ACTIVE",   4, 8,  false}
    });

    for (const auto& c : cycles) {
        std::string active_str = c.is_active ? color::green("yes") : "no";
        table.add_row({
            std::to_string(c.number),
            c.name.value_or(""),
            c.starts_at,
            c.ends_at,
            format_percent(c.progress),
            active_str
        });
    }

    if (table.empty()) {
        print_warning("No cycles found.");
        return;
    }

    table.render(std::cout);
}

void render_cycles_json(const std::vector<TeamCycle>& cycles) {
    json arr = json::array();
    for (const auto& c : cycles) {
        json j;
        j["id"] = c.id;
        j["number"] = c.number;
        j["name"] = c.name.has_value() ? json(c.name.value()) : json(nullptr);
        j["startsAt"] = c.starts_at;
        j["endsAt"] = c.ends_at;
        j["progress"] = c.progress;
        j["isActive"] = c.is_active;
        j["issueCount"] = c.issue_count;
        j["completedIssueCount"] = c.completed_issue_count;
        arr.push_back(j);
    }
    output_json(arr);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void teams_commands::register_commands(CLI::App& app) {
    auto* teams = app.add_subcommand("teams", "Manage teams");
    teams->require_subcommand(1);

    // -----------------------------------------------------------------------
    // teams list
    // -----------------------------------------------------------------------
    {
        auto* cmd = teams->add_subcommand("list", "List all teams");

        struct ListOpts {
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--limit,-n", opts->limit, "Maximum number of teams to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = opts->limit;
                    pag_opts.fetch_all = true;

                    Paginator<Team> paginator(
                        [&](const PaginationOptions& po) -> Connection<Team> {
                            return teams_api::list_teams(po.first, po.after);
                        },
                        pag_opts
                    );

                    auto all_teams = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_team_json(all_teams);
                    } else {
                        render_team_table(all_teams);
                    }
                } else {
                    auto connection = teams_api::list_teams(opts->limit);
                    if (get_output_format() == OutputFormat::Json) {
                        render_team_json(connection.nodes);
                    } else {
                        render_team_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More teams available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // teams show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = teams->add_subcommand("show", "Show team details");
        auto team_id = std::make_shared<std::string>();
        cmd->add_option("id", *team_id, "Team ID or key")->required();

        cmd->callback([team_id]() {
            try {
                auto team = teams_api::get_team(*team_id);
                render_team_detail(team);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // teams members <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = teams->add_subcommand("members", "List team members");
        auto team_id = std::make_shared<std::string>();
        cmd->add_option("id", *team_id, "Team ID or key")->required();

        cmd->callback([team_id]() {
            try {
                // Resolve key to ID if needed by fetching the team first
                auto team = teams_api::get_team(*team_id);
                auto members = teams_api::list_members(team.id);

                if (get_output_format() == OutputFormat::Json) {
                    render_members_json(members);
                } else {
                    render_members_table(members);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // teams states <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = teams->add_subcommand("states", "List workflow states for a team");
        auto team_id = std::make_shared<std::string>();
        cmd->add_option("id", *team_id, "Team ID or key")->required();

        cmd->callback([team_id]() {
            try {
                // Resolve key to ID if needed
                auto team = teams_api::get_team(*team_id);
                auto connection = teams_api::list_workflow_states(team.id);

                if (get_output_format() == OutputFormat::Json) {
                    render_states_json(connection.nodes);
                } else {
                    render_states_table(connection.nodes);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // teams labels <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = teams->add_subcommand("labels", "List labels for a team");
        auto team_id = std::make_shared<std::string>();
        cmd->add_option("id", *team_id, "Team ID or key")->required();

        cmd->callback([team_id]() {
            try {
                auto team = teams_api::get_team(*team_id);
                auto labels = teams_api::list_labels(team.id);

                if (get_output_format() == OutputFormat::Json) {
                    render_labels_json(labels);
                } else {
                    render_labels_table(labels);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // teams cycles <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = teams->add_subcommand("cycles", "List cycles for a team");
        auto team_id = std::make_shared<std::string>();
        cmd->add_option("id", *team_id, "Team ID or key")->required();

        cmd->callback([team_id]() {
            try {
                auto team = teams_api::get_team(*team_id);
                auto cycles = teams_api::list_cycles(team.id);

                if (get_output_format() == OutputFormat::Json) {
                    render_cycles_json(cycles);
                } else {
                    render_cycles_table(cycles);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
