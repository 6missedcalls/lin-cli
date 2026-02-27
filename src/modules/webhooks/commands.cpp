#include "modules/webhooks/commands.h"

#include <iostream>
#include <memory>
#include <optional>
#include <string>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/teams/api.h"
#include "modules/webhooks/api.h"
#include "modules/webhooks/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

std::string enabled_str(bool enabled) {
    return enabled ? "yes" : "no";
}

void render_webhook_table(const std::vector<Webhook>& webhooks) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"ID", "LABEL", "URL", "ENABLED"});
        for (const auto& w : webhooks) {
            output_csv_row({
                w.id,
                w.label.value_or(""),
                w.url.value_or(""),
                enabled_str(w.enabled)
            });
        }
        return;
    }

    TableRenderer table({
        {"ID",      8, 36, false},
        {"LABEL",   4, 24, false},
        {"URL",     8, 60, false},
        {"ENABLED", 4,  7, false}
    });

    for (const auto& w : webhooks) {
        table.add_row({
            w.id,
            w.label.value_or(""),
            w.url.value_or(""),
            enabled_str(w.enabled)
        });
    }

    if (table.empty()) {
        print_warning("No webhooks found.");
        return;
    }

    table.render(std::cout);
}

void render_webhook_json(const std::vector<Webhook>& webhooks) {
    json arr = json::array();
    for (const auto& w : webhooks) {
        json j;
        j["id"] = w.id;
        j["label"] = w.label.has_value() ? json(w.label.value()) : json(nullptr);
        j["url"] = w.url.has_value() ? json(w.url.value()) : json(nullptr);
        j["enabled"] = w.enabled;
        j["teamId"] = w.team_id.has_value() ? json(w.team_id.value()) : json(nullptr);
        j["creatorId"] = w.creator_id.has_value() ? json(w.creator_id.value()) : json(nullptr);
        j["creatorName"] = w.creator_name.has_value() ? json(w.creator_name.value()) : json(nullptr);
        j["createdAt"] = w.created_at;
        j["updatedAt"] = w.updated_at;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_webhook_detail(const Webhook& w) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = w.id;
        j["label"] = w.label.has_value() ? json(w.label.value()) : json(nullptr);
        j["url"] = w.url.has_value() ? json(w.url.value()) : json(nullptr);
        j["enabled"] = w.enabled;
        j["teamId"] = w.team_id.has_value() ? json(w.team_id.value()) : json(nullptr);
        j["creatorId"] = w.creator_id.has_value() ? json(w.creator_id.value()) : json(nullptr);
        j["creatorName"] = w.creator_name.has_value() ? json(w.creator_name.value()) : json(nullptr);
        j["createdAt"] = w.created_at;
        j["updatedAt"] = w.updated_at;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section("Webhook " + w.id);

    if (w.label.has_value() && !w.label.value().empty()) {
        detail.add_field("Label", w.label.value());
    }
    detail.add_field("URL", w.url.value_or(""));
    detail.add_field("Enabled", enabled_str(w.enabled));

    if (w.team_id.has_value()) {
        detail.add_field("Team ID", w.team_id.value());
    }
    if (w.creator_name.has_value()) {
        detail.add_field("Creator", w.creator_name.value());
    }

    detail.add_field("Created", w.created_at);
    detail.add_field("Updated", w.updated_at);

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void webhooks_commands::register_commands(CLI::App& app) {
    auto* webhooks = app.add_subcommand("webhooks", "Manage webhooks");
    webhooks->require_subcommand(1);

    // -----------------------------------------------------------------------
    // webhooks list
    // -----------------------------------------------------------------------
    {
        auto* cmd = webhooks->add_subcommand("list", "List all webhooks");

        struct ListOpts {
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--limit,-n", opts->limit, "Maximum number of webhooks to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = opts->limit;
                    pag_opts.fetch_all = true;
                    pag_opts.limit = opts->limit;

                    Paginator<Webhook> paginator(
                        [](const PaginationOptions& po) -> Connection<Webhook> {
                            return webhooks_api::list_webhooks(po.first, po.after);
                        },
                        pag_opts
                    );

                    auto all_webhooks = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_webhook_json(all_webhooks);
                    } else {
                        render_webhook_table(all_webhooks);
                    }
                } else {
                    auto connection = webhooks_api::list_webhooks(opts->limit);
                    if (get_output_format() == OutputFormat::Json) {
                        render_webhook_json(connection.nodes);
                    } else {
                        render_webhook_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More webhooks available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // webhooks show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = webhooks->add_subcommand("show", "Show webhook details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Webhook ID")->required();

        cmd->callback([id]() {
            try {
                auto webhook = webhooks_api::get_webhook(*id);
                render_webhook_detail(webhook);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // webhooks create
    // -----------------------------------------------------------------------
    {
        auto* cmd = webhooks->add_subcommand("create", "Create a new webhook");

        struct CreateOpts {
            std::string url;
            std::vector<std::string> resource_types;
            std::string label;
            std::string team;
            bool enabled = true;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("--url", opts->url, "Webhook URL")->required();
        cmd->add_option("--resource-types,-r", opts->resource_types, "Resource types to subscribe to (e.g., Issue, Project, Comment)")->required();
        cmd->add_option("--label", opts->label, "Webhook label");
        cmd->add_option("--team", opts->team, "Team name, key, or ID");
        cmd->add_flag("--enabled,!--disabled", opts->enabled, "Enable or disable the webhook (default: enabled)");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> label_opt = opts->label.empty()
                    ? std::nullopt
                    : std::make_optional(opts->label);
                std::optional<std::string> team_opt = opts->team.empty()
                    ? std::nullopt
                    : std::make_optional(teams_api::resolve_team_id(opts->team));

                auto webhook = webhooks_api::create_webhook(
                    opts->url,
                    opts->resource_types,
                    label_opt,
                    team_opt,
                    opts->enabled
                );

                print_success("Created webhook " + webhook.id);
                render_webhook_detail(webhook);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // webhooks update <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = webhooks->add_subcommand("update", "Update a webhook");

        struct UpdateOpts {
            std::string id;
            std::string url;
            std::string label;
            std::string enabled_str;
        };
        auto opts = std::make_shared<UpdateOpts>();

        cmd->add_option("id", opts->id, "Webhook ID")->required();
        cmd->add_option("--url", opts->url, "New webhook URL");
        cmd->add_option("--label", opts->label, "New webhook label");
        cmd->add_option("--enabled", opts->enabled_str, "Enable or disable the webhook (true/false)");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> url_opt = opts->url.empty()
                    ? std::nullopt
                    : std::make_optional(opts->url);
                std::optional<std::string> label_opt = opts->label.empty()
                    ? std::nullopt
                    : std::make_optional(opts->label);

                std::optional<bool> enabled_opt;
                if (!opts->enabled_str.empty()) {
                    if (opts->enabled_str == "true" || opts->enabled_str == "1" || opts->enabled_str == "yes") {
                        enabled_opt = true;
                    } else if (opts->enabled_str == "false" || opts->enabled_str == "0" || opts->enabled_str == "no") {
                        enabled_opt = false;
                    } else {
                        print_error("Invalid value for --enabled: " + opts->enabled_str + ". Use: true, false");
                        return;
                    }
                }

                auto webhook = webhooks_api::update_webhook(
                    opts->id,
                    url_opt,
                    label_opt,
                    enabled_opt
                );

                print_success("Updated webhook " + webhook.id);
                render_webhook_detail(webhook);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // webhooks delete <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = webhooks->add_subcommand("delete", "Delete a webhook");

        struct DeleteOpts {
            std::string id;
            bool yes = false;
        };
        auto opts = std::make_shared<DeleteOpts>();

        cmd->add_option("id", opts->id, "Webhook ID")->required();
        cmd->add_flag("--yes,-y", opts->yes, "Skip confirmation");

        cmd->callback([opts]() {
            try {
                if (!opts->yes) {
                    std::cerr << "Are you sure you want to delete webhook " << opts->id << "? [y/N] ";
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (confirm != "y" && confirm != "Y" && confirm != "yes") {
                        print_warning("Aborted.");
                        return;
                    }
                }

                webhooks_api::delete_webhook(opts->id);
                print_success("Deleted webhook " + opts->id);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
