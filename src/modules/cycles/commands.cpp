#include "modules/cycles/commands.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/filter.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/cycles/api.h"
#include "modules/cycles/model.h"
#include "modules/teams/api.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

std::string format_progress(double progress) {
    int pct = static_cast<int>(std::round(progress * 100.0));
    return std::to_string(pct) + "%";
}

std::string cycle_status(const Cycle& c) {
    if (c.is_active) return color::green("Active");
    if (c.is_next) return color::cyan("Next");
    if (c.is_previous) return color::gray("Previous");
    if (c.is_future) return color::blue("Future");
    if (c.is_past) return color::gray("Past");
    if (c.completed_at.has_value()) return color::gray("Completed");
    return "";
}

std::string cycle_label(const Cycle& c) {
    if (c.name.has_value() && !c.name.value().empty()) {
        return c.name.value();
    }
    return "Cycle " + std::to_string(static_cast<int>(c.number));
}

void render_cycle_table(const std::vector<Cycle>& cycles) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NUMBER", "NAME", "START", "END", "PROGRESS", "STATUS"});
        for (const auto& c : cycles) {
            output_csv_row({
                std::to_string(static_cast<int>(c.number)),
                c.name.value_or(""),
                c.starts_at,
                c.ends_at,
                format_progress(c.progress),
                c.is_active ? "Active" : (c.is_future ? "Future" : (c.is_past ? "Past" : ""))
            });
        }
        return;
    }

    TableRenderer table({
        {"NUMBER",   4, 8,  true},
        {"NAME",     4, 30, false},
        {"START",    6, 12, false},
        {"END",      6, 12, false},
        {"PROGRESS", 4, 10, false},
        {"STATUS",   4, 12, false}
    });

    for (const auto& c : cycles) {
        table.add_row({
            std::to_string(static_cast<int>(c.number)),
            c.name.value_or(""),
            c.starts_at.substr(0, 10),
            c.ends_at.substr(0, 10),
            format_progress(c.progress),
            cycle_status(c)
        });
    }

    if (table.empty()) {
        print_warning("No cycles found.");
        return;
    }

    table.render(std::cout);
}

void render_cycle_json(const std::vector<Cycle>& cycles) {
    json arr = json::array();
    for (const auto& c : cycles) {
        json j;
        j["id"] = c.id;
        j["number"] = c.number;
        j["name"] = c.name.value_or("");
        j["description"] = c.description.value_or("");
        j["startsAt"] = c.starts_at;
        j["endsAt"] = c.ends_at;
        j["completedAt"] = c.completed_at.value_or("");
        j["progress"] = c.progress;
        j["isActive"] = c.is_active;
        j["isFuture"] = c.is_future;
        j["isPast"] = c.is_past;
        j["isNext"] = c.is_next;
        j["isPrevious"] = c.is_previous;
        j["teamId"] = c.team_id.value_or("");
        j["teamName"] = c.team_name.value_or("");
        j["createdAt"] = c.created_at;
        j["updatedAt"] = c.updated_at;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_cycle_detail(const Cycle& c) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = c.id;
        j["number"] = c.number;
        j["name"] = c.name.value_or("");
        j["description"] = c.description.value_or("");
        j["startsAt"] = c.starts_at;
        j["endsAt"] = c.ends_at;
        j["completedAt"] = c.completed_at.value_or("");
        j["progress"] = c.progress;
        j["isActive"] = c.is_active;
        j["isFuture"] = c.is_future;
        j["isPast"] = c.is_past;
        j["isNext"] = c.is_next;
        j["isPrevious"] = c.is_previous;
        j["teamId"] = c.team_id.value_or("");
        j["teamName"] = c.team_name.value_or("");
        j["createdAt"] = c.created_at;
        j["updatedAt"] = c.updated_at;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(cycle_label(c));

    detail.add_field("Number", std::to_string(static_cast<int>(c.number)));
    detail.add_field("Status", cycle_status(c));
    detail.add_field("Team", c.team_name.value_or(""));
    detail.add_field("Starts", c.starts_at.substr(0, 10));
    detail.add_field("Ends", c.ends_at.substr(0, 10));
    detail.add_field("Progress", format_progress(c.progress));

    if (c.completed_at.has_value()) {
        detail.add_field("Completed", c.completed_at.value().substr(0, 10));
    }

    detail.add_field("Created", c.created_at);
    detail.add_field("Updated", c.updated_at);

    if (c.description.has_value() && !c.description.value().empty()) {
        detail.add_blank_line();
        detail.add_section("Description");
        detail.add_markdown(c.description.value());
    }

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void cycles_commands::register_commands(CLI::App& app) {
    auto* cycles = app.add_subcommand("cycles", "Manage cycles");
    cycles->require_subcommand(1);

    // -----------------------------------------------------------------------
    // cycles list [--team KEY] [--active] [--upcoming] [--past]
    // -----------------------------------------------------------------------
    {
        auto* cmd = cycles->add_subcommand("list", "List cycles");

        struct ListOpts {
            std::string team;
            bool active = false;
            bool upcoming = false;
            bool past = false;
            bool all = false;
            int limit = 50;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--team", opts->team, "Filter by team ID or key");
        cmd->add_flag("--active", opts->active, "Show only the active cycle");
        cmd->add_flag("--upcoming", opts->upcoming, "Show only upcoming (future) cycles");
        cmd->add_flag("--past", opts->past, "Show only past cycles");
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of cycles to return")->default_val(50);

        cmd->callback([opts]() {
            try {
                std::optional<std::string> team_opt;
                if (!opts->team.empty()) {
                    team_opt = teams_api::resolve_team_id(opts->team);
                }

                bool active_only = opts->active;

                json filter = build_cycle_filter(team_opt, active_only);

                // Apply additional status filters
                if (opts->upcoming) {
                    if (filter.is_null()) filter = json::object();
                    filter["isFuture"] = json::object({{"eq", true}});
                } else if (opts->past) {
                    if (filter.is_null()) filter = json::object();
                    filter["isPast"] = json::object({{"eq", true}});
                }

                CycleListOptions list_opts;
                list_opts.first = opts->limit;
                list_opts.filter = filter;

                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = list_opts.first;
                    pag_opts.fetch_all = true;
                    pag_opts.limit = opts->limit;

                    Paginator<Cycle> paginator(
                        [&](const PaginationOptions& po) -> Connection<Cycle> {
                            CycleListOptions lo = list_opts;
                            lo.first = po.first;
                            lo.after = po.after;
                            return cycles_api::list_cycles(lo);
                        },
                        pag_opts
                    );

                    auto all_cycles = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_cycle_json(all_cycles);
                    } else {
                        render_cycle_table(all_cycles);
                    }
                } else {
                    auto connection = cycles_api::list_cycles(list_opts);
                    if (get_output_format() == OutputFormat::Json) {
                        render_cycle_json(connection.nodes);
                    } else {
                        render_cycle_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More cycles available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // cycles show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = cycles->add_subcommand("show", "Show cycle details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Cycle number, name, or ID")->required();

        cmd->callback([id]() {
            try {
                auto resolved = cycles_api::resolve_cycle_id(*id);
                auto cycle = cycles_api::get_cycle(resolved);
                render_cycle_detail(cycle);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // cycles current [--team KEY]
    // -----------------------------------------------------------------------
    {
        auto* cmd = cycles->add_subcommand("current", "Show the active cycle");

        struct CurrentOpts {
            std::string team;
        };
        auto opts = std::make_shared<CurrentOpts>();

        cmd->add_option("--team", opts->team, "Filter by team ID or key");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> team_opt;
                if (!opts->team.empty()) {
                    team_opt = teams_api::resolve_team_id(opts->team);
                }

                json filter = build_cycle_filter(team_opt, true /* active_only */);

                CycleListOptions list_opts;
                list_opts.first = 1;
                list_opts.filter = filter;

                auto connection = cycles_api::list_cycles(list_opts);

                if (connection.nodes.empty()) {
                    print_warning("No active cycle found.");
                    return;
                }

                render_cycle_detail(connection.nodes.front());
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // cycles create --team KEY --starts-at DATE --ends-at DATE [--name] [--description]
    // -----------------------------------------------------------------------
    {
        auto* cmd = cycles->add_subcommand("create", "Create a new cycle");

        struct CreateOpts {
            std::string team;
            std::string starts_at;
            std::string ends_at;
            std::string name;
            std::string description;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("--team", opts->team, "Team name, key, or ID")->required();
        cmd->add_option("--starts-at", opts->starts_at, "Start date (YYYY-MM-DD or ISO 8601)")->required();
        cmd->add_option("--ends-at", opts->ends_at, "End date (YYYY-MM-DD or ISO 8601)")->required();
        cmd->add_option("--name", opts->name, "Cycle name");
        cmd->add_option("--description,-d", opts->description, "Cycle description");

        cmd->callback([opts]() {
            try {
                CycleCreateInput input;
                input.team_id = teams_api::resolve_team_id(opts->team);
                input.starts_at = opts->starts_at;
                input.ends_at = opts->ends_at;

                if (!opts->name.empty()) input.name = opts->name;
                if (!opts->description.empty()) input.description = opts->description;

                auto cycle = cycles_api::create_cycle(input);
                print_success("Created cycle #" + std::to_string(static_cast<int>(cycle.number)));
                render_cycle_detail(cycle);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // cycles update <id> [--name] [--starts-at] [--ends-at] [--description]
    // -----------------------------------------------------------------------
    {
        auto* cmd = cycles->add_subcommand("update", "Update a cycle");

        struct UpdateOpts {
            std::string id;
            std::string name;
            std::string starts_at;
            std::string ends_at;
            std::string description;
        };
        auto opts = std::make_shared<UpdateOpts>();

        cmd->add_option("id", opts->id, "Cycle number, name, or ID")->required();
        cmd->add_option("--name", opts->name, "New cycle name");
        cmd->add_option("--starts-at", opts->starts_at, "New start date (YYYY-MM-DD or ISO 8601)");
        cmd->add_option("--ends-at", opts->ends_at, "New end date (YYYY-MM-DD or ISO 8601)");
        cmd->add_option("--description,-d", opts->description, "New cycle description");

        cmd->callback([opts]() {
            try {
                auto resolved_id = cycles_api::resolve_cycle_id(opts->id);
                CycleUpdateInput input;

                if (!opts->name.empty()) input.name = opts->name;
                if (!opts->description.empty()) input.description = opts->description;
                if (!opts->starts_at.empty()) input.starts_at = opts->starts_at;
                if (!opts->ends_at.empty()) input.ends_at = opts->ends_at;

                auto cycle = cycles_api::update_cycle(resolved_id, input);
                print_success("Updated cycle #" + std::to_string(static_cast<int>(cycle.number)));
                render_cycle_detail(cycle);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // cycles archive <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = cycles->add_subcommand("archive", "Archive a cycle");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Cycle number, name, or ID")->required();

        cmd->callback([id]() {
            try {
                auto resolved = cycles_api::resolve_cycle_id(*id);
                cycles_api::archive_cycle(resolved);
                print_success("Archived cycle " + *id);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
