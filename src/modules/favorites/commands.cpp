#include "modules/favorites/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "core/output.h"
#include "modules/cycles/api.h"
#include "modules/favorites/api.h"
#include "modules/favorites/model.h"
#include "modules/issues/api.h"
#include "modules/labels/api.h"
#include "modules/projects/api.h"
#include "modules/views/api.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

// Derive a display title from a Favorite: prefer explicit title, fall back
// to the type + associated ID so the table is never empty.
std::string favorite_display_title(const Favorite& fav) {
    if (fav.title.has_value() && !fav.title.value().empty()) {
        return fav.title.value();
    }
    // Build a synthetic label from whichever nested ID is present
    if (fav.issue_id.has_value()) {
        return "Issue: " + fav.issue_id.value();
    }
    if (fav.project_id.has_value()) {
        return "Project: " + fav.project_id.value();
    }
    if (fav.cycle_id.has_value()) {
        return "Cycle: " + fav.cycle_id.value();
    }
    if (fav.custom_view_id.has_value()) {
        return "View: " + fav.custom_view_id.value();
    }
    if (fav.document_id.has_value()) {
        return "Document: " + fav.document_id.value();
    }
    if (fav.label_id.has_value()) {
        return "Label: " + fav.label_id.value();
    }
    return "";
}

void render_favorites_table(const std::vector<Favorite>& favorites) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"TYPE", "TITLE", "URL"});
        for (const auto& fav : favorites) {
            output_csv_row({
                fav.type,
                favorite_display_title(fav),
                fav.url.value_or("")
            });
        }
        return;
    }

    TableRenderer table({
        {"TYPE",  4, 16, false},
        {"TITLE", 8, 60, false},
        {"URL",   4, 60, false}
    });

    for (const auto& fav : favorites) {
        table.add_row({
            fav.type,
            favorite_display_title(fav),
            fav.url.value_or("")
        });
    }

    if (table.empty()) {
        print_warning("No favorites found.");
        return;
    }

    table.render(std::cout);
}

void render_favorites_json(const std::vector<Favorite>& favorites) {
    json arr = json::array();
    for (const auto& fav : favorites) {
        json j;
        j["id"] = fav.id;
        j["type"] = fav.type;
        j["createdAt"] = fav.created_at;
        j["sortOrder"] = fav.sort_order;
        j["folderName"] = fav.folder_name.has_value() ? json(fav.folder_name.value()) : json(nullptr);
        j["title"] = fav.title.has_value() ? json(fav.title.value()) : json(nullptr);
        j["url"] = fav.url.has_value() ? json(fav.url.value()) : json(nullptr);
        j["issueId"] = fav.issue_id.has_value() ? json(fav.issue_id.value()) : json(nullptr);
        j["projectId"] = fav.project_id.has_value() ? json(fav.project_id.value()) : json(nullptr);
        j["cycleId"] = fav.cycle_id.has_value() ? json(fav.cycle_id.value()) : json(nullptr);
        j["customViewId"] = fav.custom_view_id.has_value() ? json(fav.custom_view_id.value()) : json(nullptr);
        j["documentId"] = fav.document_id.has_value() ? json(fav.document_id.value()) : json(nullptr);
        j["labelId"] = fav.label_id.has_value() ? json(fav.label_id.value()) : json(nullptr);
        arr.push_back(std::move(j));
    }
    output_json(arr);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void favorites_commands::register_commands(CLI::App& app) {
    auto* favorites = app.add_subcommand("favorites", "Manage favorites");
    favorites->require_subcommand(1);

    // -----------------------------------------------------------------------
    // favorites list
    // -----------------------------------------------------------------------
    {
        auto* cmd = favorites->add_subcommand("list", "List favorites");

        struct ListOpts {
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--limit,-n", opts->limit, "Maximum number of favorites to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                if (opts->all) {
                    std::vector<Favorite> all_favorites;
                    std::optional<std::string> cursor;

                    do {
                        auto connection = favorites_api::list_favorites(opts->limit, cursor);
                        for (auto& fav : connection.nodes) {
                            all_favorites.push_back(std::move(fav));
                        }
                        if (connection.page_info.has_next_page && connection.page_info.end_cursor.has_value()) {
                            cursor = connection.page_info.end_cursor;
                        } else {
                            cursor = std::nullopt;
                        }
                    } while (cursor.has_value());

                    if (get_output_format() == OutputFormat::Json) {
                        render_favorites_json(all_favorites);
                    } else {
                        render_favorites_table(all_favorites);
                    }
                } else {
                    auto connection = favorites_api::list_favorites(opts->limit);
                    if (get_output_format() == OutputFormat::Json) {
                        render_favorites_json(connection.nodes);
                    } else {
                        render_favorites_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More favorites available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // favorites add
    // -----------------------------------------------------------------------
    {
        auto* cmd = favorites->add_subcommand("add", "Add a favorite");

        struct AddOpts {
            std::string issue;
            std::string project;
            std::string cycle;
            std::string view;
            std::string document;
            std::string label;
        };
        auto opts = std::make_shared<AddOpts>();

        cmd->add_option("--issue", opts->issue, "Issue identifier (e.g. ENG-123) or ID to favorite");
        cmd->add_option("--project", opts->project, "Project name or ID to favorite");
        cmd->add_option("--cycle", opts->cycle, "Cycle name or ID to favorite");
        cmd->add_option("--view", opts->view, "Custom view name or ID to favorite");
        cmd->add_option("--document", opts->document, "Document ID to favorite");
        cmd->add_option("--label", opts->label, "Label name or ID to favorite");

        cmd->callback([opts]() {
            try {
                // Validate exactly one target is provided
                int provided = 0;
                if (!opts->issue.empty()) ++provided;
                if (!opts->project.empty()) ++provided;
                if (!opts->cycle.empty()) ++provided;
                if (!opts->view.empty()) ++provided;
                if (!opts->document.empty()) ++provided;
                if (!opts->label.empty()) ++provided;

                if (provided == 0) {
                    print_error("Provide exactly one of: --issue, --project, --cycle, --view, --document, --label");
                    return;
                }
                if (provided > 1) {
                    print_error("Provide exactly one target — multiple flags were set");
                    return;
                }

                FavoriteCreateInput input;
                if (!opts->issue.empty()) input.issue_id = issues_api::get_issue(opts->issue).id;
                if (!opts->project.empty()) input.project_id = projects_api::resolve_project_id(opts->project);
                if (!opts->cycle.empty()) input.cycle_id = cycles_api::resolve_cycle_id(opts->cycle);
                if (!opts->view.empty()) input.custom_view_id = views_api::resolve_view_id(opts->view);
                if (!opts->document.empty()) input.document_id = opts->document;
                if (!opts->label.empty()) input.label_id = labels_api::resolve_label_id(opts->label);

                auto fav = favorites_api::create_favorite(input);
                print_success("Added favorite " + fav.id);

                if (get_output_format() == OutputFormat::Json) {
                    render_favorites_json({fav});
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // favorites remove <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = favorites->add_subcommand("remove", "Remove a favorite by ID");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Favorite ID to remove")->required();

        cmd->callback([id]() {
            try {
                favorites_api::delete_favorite(*id);
                print_success("Removed favorite " + *id);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
