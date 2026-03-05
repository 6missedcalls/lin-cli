#include "modules/users/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/users/api.h"
#include "modules/users/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

void render_user_table(const std::vector<User>& users) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "EMAIL", "ACTIVE", "ADMIN"});
        for (const auto& user : users) {
            output_csv_row({
                user.display_name,
                user.email,
                user.active ? "yes" : "no",
                user.admin ? "yes" : "no"
            });
        }
        return;
    }

    TableRenderer table({
        {"NAME",   6, 30, false},
        {"EMAIL",  6, 40, false},
        {"ACTIVE", 6, 8,  false},
        {"ADMIN",  5, 8,  false}
    });

    for (const auto& user : users) {
        table.add_row({
            user.display_name,
            user.email,
            user.active ? "yes" : "no",
            user.admin ? "yes" : "no"
        });
    }

    if (table.empty()) {
        print_warning("No users found.");
        return;
    }

    table.render(std::cout);
}

void render_user_json(const std::vector<User>& users) {
    json arr = json::array();
    for (const auto& user : users) {
        json j;
        j["id"] = user.id;
        j["name"] = user.name;
        j["displayName"] = user.display_name;
        j["email"] = user.email;
        j["active"] = user.active;
        j["admin"] = user.admin;
        j["guest"] = user.guest;
        j["isMe"] = user.is_me;
        j["avatarUrl"] = user.avatar_url.value_or("");
        j["description"] = user.description.value_or("");
        j["timezone"] = user.timezone.value_or("");
        j["lastSeen"] = user.last_seen.value_or("");
        j["statusEmoji"] = user.status_emoji.value_or("");
        j["statusLabel"] = user.status_label.value_or("");
        j["createdAt"] = user.created_at;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_user_detail(const User& user) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = user.id;
        j["name"] = user.name;
        j["displayName"] = user.display_name;
        j["email"] = user.email;
        j["active"] = user.active;
        j["admin"] = user.admin;
        j["guest"] = user.guest;
        j["isMe"] = user.is_me;
        j["avatarUrl"] = user.avatar_url.value_or("");
        j["description"] = user.description.value_or("");
        j["timezone"] = user.timezone.value_or("");
        j["lastSeen"] = user.last_seen.value_or("");
        j["statusEmoji"] = user.status_emoji.value_or("");
        j["statusLabel"] = user.status_label.value_or("");
        j["createdAt"] = user.created_at;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(user.display_name);

    detail.add_field("Name", user.name);
    detail.add_field("Email", user.email);
    detail.add_field("Active", user.active ? "yes" : "no");
    detail.add_field("Admin", user.admin ? "yes" : "no");
    detail.add_field("Guest", user.guest ? "yes" : "no");

    if (user.status_emoji.has_value() || user.status_label.has_value()) {
        std::string status;
        if (user.status_emoji.has_value()) {
            status += user.status_emoji.value() + " ";
        }
        if (user.status_label.has_value()) {
            status += user.status_label.value();
        }
        detail.add_field("Status", status);
    }

    if (user.timezone.has_value()) {
        detail.add_field("Timezone", user.timezone.value());
    }
    if (user.last_seen.has_value()) {
        detail.add_field("Last Seen", user.last_seen.value());
    }
    if (user.description.has_value() && !user.description.value().empty()) {
        detail.add_field("Description", user.description.value());
    }

    detail.add_field("Created", user.created_at);
    detail.add_field("ID", user.id);

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void users_commands::register_commands(CLI::App& app) {
    auto* users = app.add_subcommand("users", "Manage workspace users");
    users->require_subcommand(1);

    // -----------------------------------------------------------------------
    // users list
    // -----------------------------------------------------------------------
    {
        auto* cmd = users->add_subcommand("list", "List workspace users");

        struct ListOpts {
            bool include_disabled = false;
            bool all = false;
            int limit = 50;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_flag("--include-disabled", opts->include_disabled, "Include disabled users");
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of users to return")->default_val(50);

        cmd->callback([opts]() {
            try {
                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = opts->limit;
                    pag_opts.fetch_all = true;
                    pag_opts.limit = opts->limit;

                    Paginator<User> paginator(
                        [&](const PaginationOptions& po) -> Connection<User> {
                            return users_api::list_users(
                                po.first,
                                po.after,
                                opts->include_disabled
                            );
                        },
                        pag_opts
                    );

                    auto all_users = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_user_json(all_users);
                    } else {
                        render_user_table(all_users);
                    }
                } else {
                    auto connection = users_api::list_users(
                        opts->limit,
                        std::nullopt,
                        opts->include_disabled
                    );
                    if (get_output_format() == OutputFormat::Json) {
                        render_user_json(connection.nodes);
                    } else {
                        render_user_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More users available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // users show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = users->add_subcommand("show", "Show user details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "User ID")->required();

        cmd->callback([id]() {
            try {
                auto resolved_id = users_api::resolve_user_id(*id);
                auto user = users_api::get_user(resolved_id);
                render_user_detail(user);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
