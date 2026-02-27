#include "modules/initiatives/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "core/output.h"
#include "modules/initiatives/api.h"
#include "modules/initiatives/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

void render_initiatives_table(const std::vector<Initiative>& initiatives) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "STATUS", "HEALTH", "OWNER", "TARGET DATE"});
        for (const auto& initiative : initiatives) {
            output_csv_row({
                initiative.name,
                initiative.status.value_or(""),
                initiative.health.value_or(""),
                initiative.owner_name.value_or(""),
                initiative.target_date.value_or("")
            });
        }
        return;
    }

    TableRenderer table({
        {"NAME",        8, 50, false},
        {"STATUS",      4, 12, false},
        {"HEALTH",      4, 10, false},
        {"OWNER",       4, 24, false},
        {"TARGET DATE", 4, 12, false}
    });

    for (const auto& initiative : initiatives) {
        table.add_row({
            initiative.name,
            initiative.status.value_or(""),
            initiative.health.value_or(""),
            initiative.owner_name.value_or(""),
            initiative.target_date.value_or("")
        });
    }

    if (table.empty()) {
        print_warning("No initiatives found.");
        return;
    }

    table.render(std::cout);
}

void render_initiatives_json(const std::vector<Initiative>& initiatives) {
    json arr = json::array();
    for (const auto& initiative : initiatives) {
        json j;
        j["id"]          = initiative.id;
        j["name"]        = initiative.name;
        j["description"] = initiative.description.value_or("");
        j["icon"]        = initiative.icon.value_or("");
        j["color"]       = initiative.color.value_or("");
        j["slugId"]      = initiative.slug_id;
        j["url"]         = initiative.url;
        j["status"]      = initiative.status.value_or("");
        j["health"]      = initiative.health.value_or("");
        j["targetDate"]  = initiative.target_date.value_or("");
        j["ownerId"]     = initiative.owner_id.value_or("");
        j["ownerName"]   = initiative.owner_name.value_or("");
        j["startedAt"]   = initiative.started_at.value_or("");
        j["completedAt"] = initiative.completed_at.value_or("");
        j["createdAt"]   = initiative.created_at;
        j["updatedAt"]   = initiative.updated_at;
        j["trashed"]     = initiative.trashed;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_initiative_detail(const Initiative& initiative) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"]          = initiative.id;
        j["name"]        = initiative.name;
        j["description"] = initiative.description.value_or("");
        j["icon"]        = initiative.icon.value_or("");
        j["color"]       = initiative.color.value_or("");
        j["slugId"]      = initiative.slug_id;
        j["url"]         = initiative.url;
        j["status"]      = initiative.status.value_or("");
        j["health"]      = initiative.health.value_or("");
        j["targetDate"]  = initiative.target_date.value_or("");
        j["ownerId"]     = initiative.owner_id.value_or("");
        j["ownerName"]   = initiative.owner_name.value_or("");
        j["startedAt"]   = initiative.started_at.value_or("");
        j["completedAt"] = initiative.completed_at.value_or("");
        j["createdAt"]   = initiative.created_at;
        j["updatedAt"]   = initiative.updated_at;
        j["trashed"]     = initiative.trashed;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(initiative.name);

    if (initiative.status.has_value()) {
        detail.add_field("Status", initiative.status.value());
    }
    if (initiative.health.has_value()) {
        detail.add_field("Health", initiative.health.value());
    }
    if (initiative.owner_name.has_value()) {
        detail.add_field("Owner", initiative.owner_name.value());
    }
    if (initiative.target_date.has_value()) {
        detail.add_field("Target Date", initiative.target_date.value());
    }
    if (initiative.started_at.has_value()) {
        detail.add_field("Started", initiative.started_at.value());
    }
    if (initiative.completed_at.has_value()) {
        detail.add_field("Completed", initiative.completed_at.value());
    }
    if (initiative.color.has_value()) {
        detail.add_field("Color", initiative.color.value());
    }
    if (initiative.icon.has_value()) {
        detail.add_field("Icon", initiative.icon.value());
    }

    detail.add_field("Slug", initiative.slug_id);
    detail.add_field("URL", initiative.url);
    detail.add_field("Created", initiative.created_at);
    detail.add_field("Updated", initiative.updated_at);

    if (initiative.description.has_value() && !initiative.description.value().empty()) {
        detail.add_blank_line();
        detail.add_section("Description");
        detail.add_markdown(initiative.description.value());
    }

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void initiatives_commands::register_commands(CLI::App& app) {
    auto* initiatives = app.add_subcommand("initiatives", "Manage initiatives");
    initiatives->require_subcommand(1);

    // -----------------------------------------------------------------------
    // initiatives list [--status TYPE]
    // -----------------------------------------------------------------------
    {
        auto* cmd = initiatives->add_subcommand("list", "List initiatives");

        struct ListOpts {
            std::string status;
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--status", opts->status, "Filter by status (Planned, Active, Completed)");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of initiatives to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> status_opt =
                    opts->status.empty() ? std::nullopt : std::make_optional(opts->status);

                InitiativeListOptions list_opts;
                list_opts.first = opts->limit;
                list_opts.status_filter = status_opt;

                if (opts->all) {
                    std::vector<Initiative> all_initiatives;
                    std::optional<std::string> cursor;

                    do {
                        list_opts.after = cursor;
                        auto connection = initiatives_api::list_initiatives(list_opts);
                        for (auto& item : connection.nodes) {
                            all_initiatives.push_back(std::move(item));
                        }
                        if (connection.page_info.has_next_page && connection.page_info.end_cursor.has_value()) {
                            cursor = connection.page_info.end_cursor;
                        } else {
                            cursor = std::nullopt;
                        }
                    } while (cursor.has_value());

                    if (get_output_format() == OutputFormat::Json) {
                        render_initiatives_json(all_initiatives);
                    } else {
                        render_initiatives_table(all_initiatives);
                    }
                } else {
                    auto connection = initiatives_api::list_initiatives(list_opts);
                    if (get_output_format() == OutputFormat::Json) {
                        render_initiatives_json(connection.nodes);
                    } else {
                        render_initiatives_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More initiatives available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // initiatives show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = initiatives->add_subcommand("show", "Show initiative details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Initiative ID")->required();

        cmd->callback([id]() {
            try {
                auto initiative = initiatives_api::get_initiative(*id);
                render_initiative_detail(initiative);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
