#include "modules/views/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "core/output.h"
#include "modules/views/api.h"
#include "modules/views/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

void render_views_table(const std::vector<CustomView>& views) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "OWNER", "SHARED", "MODEL"});
        for (const auto& v : views) {
            output_csv_row({
                v.name,
                v.owner_name.value_or(""),
                v.shared ? "yes" : "no",
                v.model_name.value_or("")
            });
        }
        return;
    }

    TableRenderer table({
        {"NAME",   6, 40, false},
        {"OWNER",  4, 24, false},
        {"SHARED", 4,  6, false},
        {"MODEL",  4, 20, false}
    });

    for (const auto& v : views) {
        table.add_row({
            v.name,
            v.owner_name.value_or(""),
            v.shared ? "yes" : "no",
            v.model_name.value_or("")
        });
    }

    if (table.empty()) {
        print_warning("No custom views found.");
        return;
    }

    table.render(std::cout);
}

void render_view_json_list(const std::vector<CustomView>& views) {
    json arr = json::array();
    for (const auto& v : views) {
        json j;
        j["id"] = v.id;
        j["name"] = v.name;
        j["description"] = v.description.value_or("");
        j["icon"] = v.icon.value_or("");
        j["color"] = v.color.value_or("");
        j["slugId"] = v.slug_id;
        j["modelName"] = v.model_name.value_or("");
        j["shared"] = v.shared;
        j["owner"] = v.owner_name.value_or("");
        j["ownerId"] = v.owner_id.value_or("");
        j["team"] = v.team_name.value_or("");
        j["teamId"] = v.team_id.value_or("");
        j["createdAt"] = v.created_at;
        j["updatedAt"] = v.updated_at;
        if (v.filter_data.has_value()) {
            j["filterData"] = v.filter_data.value();
        } else {
            j["filterData"] = nullptr;
        }
        arr.push_back(j);
    }
    output_json(arr);
}

void render_view_detail(const CustomView& v) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = v.id;
        j["name"] = v.name;
        j["description"] = v.description.value_or("");
        j["icon"] = v.icon.value_or("");
        j["color"] = v.color.value_or("");
        j["slugId"] = v.slug_id;
        j["modelName"] = v.model_name.value_or("");
        j["shared"] = v.shared;
        j["owner"] = v.owner_name.value_or("");
        j["ownerId"] = v.owner_id.value_or("");
        j["team"] = v.team_name.value_or("");
        j["teamId"] = v.team_id.value_or("");
        j["createdAt"] = v.created_at;
        j["updatedAt"] = v.updated_at;
        if (v.filter_data.has_value()) {
            j["filterData"] = v.filter_data.value();
        } else {
            j["filterData"] = nullptr;
        }
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(v.name);

    detail.add_field("ID", v.id);
    detail.add_field("Slug", v.slug_id);
    detail.add_field("Shared", v.shared ? "yes" : "no");

    if (v.description.has_value() && !v.description.value().empty()) {
        detail.add_field("Description", v.description.value());
    }
    if (v.owner_name.has_value()) {
        detail.add_field("Owner", v.owner_name.value());
    }
    if (v.team_name.has_value()) {
        detail.add_field("Team", v.team_name.value());
    }
    if (v.model_name.has_value() && !v.model_name.value().empty()) {
        detail.add_field("Model", v.model_name.value());
    }
    if (v.icon.has_value() && !v.icon.value().empty()) {
        detail.add_field("Icon", v.icon.value());
    }
    if (v.color.has_value() && !v.color.value().empty()) {
        detail.add_field("Color", v.color.value());
    }

    detail.add_field("Created", v.created_at);
    detail.add_field("Updated", v.updated_at);

    if (v.filter_data.has_value()) {
        detail.add_blank_line();
        detail.add_section("Filter Data");
        detail.add_markdown(v.filter_data.value().dump(2));
    }

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void views_commands::register_commands(CLI::App& app) {
    auto* views = app.add_subcommand("views", "Manage custom views");
    views->require_subcommand(1);

    // -----------------------------------------------------------------------
    // views list [--shared]
    // -----------------------------------------------------------------------
    {
        auto* cmd = views->add_subcommand("list", "List custom views");

        struct ListOpts {
            bool shared = false;
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_flag("--shared", opts->shared, "Show only shared views");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of views to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                std::optional<bool> shared_filter = opts->shared
                    ? std::make_optional(true)
                    : std::nullopt;

                if (opts->all) {
                    std::vector<CustomView> all_views;
                    std::optional<std::string> cursor;

                    do {
                        auto connection = views_api::list_views(opts->limit, cursor, shared_filter);
                        for (auto& v : connection.nodes) {
                            all_views.push_back(std::move(v));
                        }
                        if (connection.page_info.has_next_page && connection.page_info.end_cursor.has_value()) {
                            cursor = connection.page_info.end_cursor;
                        } else {
                            cursor = std::nullopt;
                        }
                    } while (cursor.has_value());

                    if (get_output_format() == OutputFormat::Json) {
                        render_view_json_list(all_views);
                    } else {
                        render_views_table(all_views);
                    }
                } else {
                    auto connection = views_api::list_views(opts->limit, std::nullopt, shared_filter);
                    if (get_output_format() == OutputFormat::Json) {
                        render_view_json_list(connection.nodes);
                    } else {
                        render_views_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More views available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // views show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = views->add_subcommand("show", "Show custom view details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Custom view ID")->required();

        cmd->callback([id]() {
            try {
                auto resolved_id = views_api::resolve_view_id(*id);
                auto view = views_api::get_view(resolved_id);
                render_view_detail(view);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // views create --name NAME [--description DESC] [--shared] [--filter JSON]
    // -----------------------------------------------------------------------
    {
        auto* cmd = views->add_subcommand("create", "Create a new custom view");

        struct CreateOpts {
            std::string name;
            std::string description;
            bool shared = false;
            std::string filter_json;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("--name,-n", opts->name, "View name")->required();
        cmd->add_option("--description,-d", opts->description, "View description");
        cmd->add_flag("--shared,-s", opts->shared, "Make the view shared");
        cmd->add_option("--filter,-f", opts->filter_json, "Filter data as JSON string");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> desc_opt = opts->description.empty()
                    ? std::nullopt
                    : std::make_optional(opts->description);

                std::optional<json> filter_opt;
                if (!opts->filter_json.empty()) {
                    try {
                        filter_opt = json::parse(opts->filter_json);
                    } catch (const json::parse_error& e) {
                        print_error(std::string("Invalid JSON for --filter: ") + e.what());
                        return;
                    }
                }

                auto view = views_api::create_view(opts->name, desc_opt, opts->shared, filter_opt);
                print_success("Created view: " + view.name);
                render_view_detail(view);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // views delete <id> [--yes]
    // -----------------------------------------------------------------------
    {
        auto* cmd = views->add_subcommand("delete", "Delete a custom view");

        struct DeleteOpts {
            std::string id;
            bool yes = false;
        };
        auto opts = std::make_shared<DeleteOpts>();

        cmd->add_option("id", opts->id, "Custom view ID")->required();
        cmd->add_flag("--yes,-y", opts->yes, "Skip confirmation");

        cmd->callback([opts]() {
            try {
                auto resolved_id = views_api::resolve_view_id(opts->id);
                auto view = views_api::get_view(resolved_id);

                if (!opts->yes) {
                    std::cerr << "Are you sure you want to delete view \""
                              << view.name << "\" (" << view.id << ")? [y/N] ";
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (confirm != "y" && confirm != "Y" && confirm != "yes") {
                        print_warning("Aborted.");
                        return;
                    }
                }

                views_api::delete_view(view.id);
                print_success("Deleted view: " + view.name);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
