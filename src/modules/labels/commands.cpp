#include "modules/labels/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "modules/labels/api.h"
#include "modules/labels/model.h"
#include "modules/teams/api.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

void render_label_table(const std::vector<IssueLabel>& labels) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "COLOR", "TEAM", "GROUP"});
        for (const auto& label : labels) {
            output_csv_row({
                label.name,
                label.color,
                label.team_name.value_or(""),
                label.is_group ? "yes" : "no"
            });
        }
        return;
    }

    TableRenderer table({
        {"NAME",  6, 32, false},
        {"COLOR", 4, 10, false},
        {"TEAM",  4, 20, false},
        {"GROUP", 4,  6, false}
    });

    for (const auto& label : labels) {
        std::string color_str = color::from_hex(label.color, label.color);
        std::string group_str = label.is_group ? color::green("yes") : "no";

        table.add_row({
            label.name,
            color_str,
            label.team_name.value_or(""),
            group_str
        });
    }

    if (table.empty()) {
        print_warning("No labels found.");
        return;
    }

    table.render(std::cout);
}

void render_label_json(const std::vector<IssueLabel>& labels) {
    json arr = json::array();
    for (const auto& label : labels) {
        json j;
        j["id"] = label.id;
        j["name"] = label.name;
        j["color"] = label.color;
        j["isGroup"] = label.is_group;
        j["description"] = label.description.value_or("");
        j["parentId"] = label.parent_id.value_or("");
        j["parentName"] = label.parent_name.value_or("");
        j["teamId"] = label.team_id.value_or("");
        j["teamName"] = label.team_name.value_or("");
        j["createdAt"] = label.created_at;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_label_detail(const IssueLabel& label) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = label.id;
        j["name"] = label.name;
        j["color"] = label.color;
        j["isGroup"] = label.is_group;
        j["description"] = label.description.value_or("");
        j["parentId"] = label.parent_id.value_or("");
        j["parentName"] = label.parent_name.value_or("");
        j["teamId"] = label.team_id.value_or("");
        j["teamName"] = label.team_name.value_or("");
        j["createdAt"] = label.created_at;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(label.name);

    detail.add_field("Color", color::from_hex(label.color, label.color));
    detail.add_field("Group", label.is_group ? "yes" : "no");

    if (label.description.has_value() && !label.description.value().empty()) {
        detail.add_field("Description", label.description.value());
    }
    if (label.team_name.has_value()) {
        detail.add_field("Team", label.team_name.value());
    }
    if (label.parent_name.has_value()) {
        detail.add_field("Parent", label.parent_name.value());
    }

    detail.add_field("ID", label.id);
    detail.add_field("Created", label.created_at);

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void labels_commands::register_commands(CLI::App& app) {
    auto* labels = app.add_subcommand("labels", "Manage issue labels");
    labels->require_subcommand(1);

    // -----------------------------------------------------------------------
    // labels list
    // -----------------------------------------------------------------------
    {
        auto* cmd = labels->add_subcommand("list", "List labels");

        struct ListOpts {
            std::string team;
            bool group_only = false;
            int limit = 50;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--team", opts->team, "Filter by team ID or key");
        cmd->add_flag("--group", opts->group_only, "Show only group labels");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of labels to return")->default_val(50);

        cmd->callback([opts]() {
            try {
                std::optional<std::string> team_opt = opts->team.empty()
                    ? std::nullopt
                    : std::make_optional(opts->team);

                auto connection = labels_api::list_labels(opts->limit, std::nullopt, team_opt);

                std::vector<IssueLabel> filtered;
                filtered.reserve(connection.nodes.size());
                for (const auto& label : connection.nodes) {
                    if (!opts->group_only || label.is_group) {
                        filtered.push_back(label);
                    }
                }

                if (get_output_format() == OutputFormat::Json) {
                    render_label_json(filtered);
                } else {
                    render_label_table(filtered);
                    if (connection.page_info.has_next_page) {
                        print_warning("More labels available. Use --limit to increase results.");
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // labels show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = labels->add_subcommand("show", "Show label details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Label ID")->required();

        cmd->callback([id]() {
            try {
                auto resolved_id = labels_api::resolve_label_id(*id);
                auto label = labels_api::get_label(resolved_id);
                render_label_detail(label);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // labels create
    // -----------------------------------------------------------------------
    {
        auto* cmd = labels->add_subcommand("create", "Create a new label");

        struct CreateOpts {
            std::string name;
            std::string color;
            std::string team;
            std::string description;
            std::string parent;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("--name", opts->name, "Label name")->required();
        cmd->add_option("--color", opts->color, "Label color as hex (e.g. #FF0000)")->required();
        cmd->add_option("--team", opts->team, "Team name, key, or ID");
        cmd->add_option("--description", opts->description, "Label description");
        cmd->add_option("--parent", opts->parent, "Parent label ID");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> team_opt = opts->team.empty()
                    ? std::nullopt
                    : std::make_optional(teams_api::resolve_team_id(opts->team));
                std::optional<std::string> desc_opt = opts->description.empty()
                    ? std::nullopt
                    : std::make_optional(opts->description);
                std::optional<std::string> parent_opt = opts->parent.empty()
                    ? std::nullopt
                    : std::make_optional(opts->parent);

                auto label = labels_api::create_label(
                    opts->name,
                    opts->color,
                    team_opt,
                    desc_opt,
                    parent_opt
                );

                print_success("Created label \"" + label.name + "\"");
                render_label_detail(label);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // labels update <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = labels->add_subcommand("update", "Update a label");

        struct UpdateOpts {
            std::string id;
            std::string name;
            std::string color;
            std::string description;
        };
        auto opts = std::make_shared<UpdateOpts>();

        cmd->add_option("id", opts->id, "Label ID")->required();
        cmd->add_option("--name", opts->name, "New label name");
        cmd->add_option("--color", opts->color, "New label color as hex (e.g. #FF0000)");
        cmd->add_option("--description", opts->description, "New label description");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> name_opt = opts->name.empty()
                    ? std::nullopt
                    : std::make_optional(opts->name);
                std::optional<std::string> color_opt = opts->color.empty()
                    ? std::nullopt
                    : std::make_optional(opts->color);
                std::optional<std::string> desc_opt = opts->description.empty()
                    ? std::nullopt
                    : std::make_optional(opts->description);

                auto label = labels_api::update_label(
                    opts->id,
                    name_opt,
                    color_opt,
                    desc_opt
                );

                print_success("Updated label \"" + label.name + "\"");
                render_label_detail(label);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // labels delete <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = labels->add_subcommand("delete", "Delete a label");

        struct DeleteOpts {
            std::string id;
            bool yes = false;
        };
        auto opts = std::make_shared<DeleteOpts>();

        cmd->add_option("id", opts->id, "Label ID")->required();
        cmd->add_flag("--yes,-y", opts->yes, "Skip confirmation");

        cmd->callback([opts]() {
            try {
                auto label = labels_api::get_label(opts->id);

                if (!opts->yes) {
                    std::cerr << "Are you sure you want to delete label \""
                              << label.name << "\"? [y/N] ";
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (confirm != "y" && confirm != "Y" && confirm != "yes") {
                        print_warning("Aborted.");
                        return;
                    }
                }

                labels_api::delete_label(label.id);
                print_success("Deleted label \"" + label.name + "\"");
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
