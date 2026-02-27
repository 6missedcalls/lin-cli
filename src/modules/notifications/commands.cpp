#include "modules/notifications/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/notifications/api.h"
#include "modules/notifications/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

// Returns a short display-friendly type label from the raw notification type string.
// e.g. "issueAssignedToYou" -> "ASSIGNED"
std::string format_notification_type(const std::string& type) {
    if (type == "issueAssignedToYou") return "ASSIGNED";
    if (type == "issueCommentMention") return "COMMENT";
    if (type == "issueCommentReaction") return "REACTION";
    if (type == "issueCreated") return "CREATED";
    if (type == "issueStatusChanged") return "STATUS";
    if (type == "issuePriorityUrgent") return "URGENT";
    if (type == "issueDue") return "DUE";
    if (type == "issueMention") return "MENTION";
    if (type == "issueSubscribed") return "SUBSCRIBED";
    if (type == "issueUnassignedFromYou") return "UNASSIGNED";
    if (type == "projectUpdateCreated") return "PROJECT";
    if (type == "projectUpdateMention") return "PR-MENTION";
    return type;
}

void render_notification_table(const std::vector<Notification>& notifications) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"READ", "TYPE", "TITLE", "ACTOR", "DATE"});
        for (const auto& n : notifications) {
            output_csv_row({
                n.read_at.has_value() ? "" : "*",
                format_notification_type(n.type),
                n.title.value_or(""),
                n.actor_name.value_or(""),
                n.updated_at
            });
        }
        return;
    }

    // Table columns: unread marker | TYPE | TITLE | ACTOR | DATE
    TableRenderer table({
        {"",       1, 1,  false},   // unread marker "*"
        {"TYPE",   6, 12, false},
        {"TITLE",  8, 60, false},
        {"ACTOR",  4, 20, false},
        {"DATE",   4, 24, false}
    });

    for (const auto& n : notifications) {
        std::string unread_marker = n.read_at.has_value() ? " " : "*";
        table.add_row({
            unread_marker,
            format_notification_type(n.type),
            n.title.value_or("(no title)"),
            n.actor_name.value_or(""),
            n.updated_at
        });
    }

    if (table.empty()) {
        print_warning("No notifications found.");
        return;
    }

    table.render(std::cout);
}

void render_notification_json(const std::vector<Notification>& notifications) {
    json arr = json::array();
    for (const auto& n : notifications) {
        json j;
        j["id"] = n.id;
        j["type"] = n.type;
        j["createdAt"] = n.created_at;
        j["updatedAt"] = n.updated_at;
        j["readAt"] = n.read_at.has_value() ? json(n.read_at.value()) : json(nullptr);
        j["snoozedUntilAt"] = n.snoozed_until_at.has_value() ? json(n.snoozed_until_at.value()) : json(nullptr);
        j["archivedAt"] = n.archived_at.has_value() ? json(n.archived_at.value()) : json(nullptr);
        j["actorId"] = n.actor_id.has_value() ? json(n.actor_id.value()) : json(nullptr);
        j["actorName"] = n.actor_name.has_value() ? json(n.actor_name.value()) : json(nullptr);
        j["title"] = n.title.has_value() ? json(n.title.value()) : json(nullptr);
        j["subtitle"] = n.subtitle.has_value() ? json(n.subtitle.value()) : json(nullptr);
        j["url"] = n.url.has_value() ? json(n.url.value()) : json(nullptr);
        arr.push_back(j);
    }
    output_json(arr);
}

void render_notification_detail(const Notification& n) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = n.id;
        j["type"] = n.type;
        j["createdAt"] = n.created_at;
        j["updatedAt"] = n.updated_at;
        j["readAt"] = n.read_at.has_value() ? json(n.read_at.value()) : json(nullptr);
        j["snoozedUntilAt"] = n.snoozed_until_at.has_value() ? json(n.snoozed_until_at.value()) : json(nullptr);
        j["archivedAt"] = n.archived_at.has_value() ? json(n.archived_at.value()) : json(nullptr);
        j["actorId"] = n.actor_id.has_value() ? json(n.actor_id.value()) : json(nullptr);
        j["actorName"] = n.actor_name.has_value() ? json(n.actor_name.value()) : json(nullptr);
        j["title"] = n.title.has_value() ? json(n.title.value()) : json(nullptr);
        j["subtitle"] = n.subtitle.has_value() ? json(n.subtitle.value()) : json(nullptr);
        j["url"] = n.url.has_value() ? json(n.url.value()) : json(nullptr);
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(n.title.value_or("Notification " + n.id));

    detail.add_field("Type", format_notification_type(n.type));
    detail.add_field("Status", n.read_at.has_value() ? "Read" : "Unread");

    if (n.actor_name.has_value()) {
        detail.add_field("Actor", n.actor_name.value());
    }
    if (n.subtitle.has_value()) {
        detail.add_field("Subtitle", n.subtitle.value());
    }
    if (n.url.has_value()) {
        detail.add_field("URL", n.url.value());
    }

    detail.add_field("Created", n.created_at);
    detail.add_field("Updated", n.updated_at);

    if (n.read_at.has_value()) {
        detail.add_field("Read At", n.read_at.value());
    }
    if (n.snoozed_until_at.has_value()) {
        detail.add_field("Snoozed Until", n.snoozed_until_at.value());
    }
    if (n.archived_at.has_value()) {
        detail.add_field("Archived At", n.archived_at.value());
    }

    detail.add_field("ID", n.id);

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void notifications_commands::register_commands(CLI::App& app) {
    auto* notifications = app.add_subcommand("notifications", "Manage notifications");
    notifications->require_subcommand(1);

    // -----------------------------------------------------------------------
    // notifications list [--unread] [--limit N]
    // -----------------------------------------------------------------------
    {
        auto* cmd = notifications->add_subcommand("list", "List notifications");

        struct ListOpts {
            bool unread = false;
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_flag("--unread,-u", opts->unread, "Show only unread notifications");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of notifications to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = opts->limit;
                    pag_opts.fetch_all = true;
                    pag_opts.limit = opts->limit;

                    bool unread_only = opts->unread;
                    Paginator<Notification> paginator(
                        [unread_only](const PaginationOptions& po) -> Connection<Notification> {
                            return notifications_api::list_notifications(po.first, po.after, unread_only);
                        },
                        pag_opts
                    );

                    auto all_notifications = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_notification_json(all_notifications);
                    } else {
                        render_notification_table(all_notifications);
                    }
                } else {
                    auto connection = notifications_api::list_notifications(opts->limit, std::nullopt, opts->unread);
                    if (get_output_format() == OutputFormat::Json) {
                        render_notification_json(connection.nodes);
                    } else {
                        render_notification_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More notifications available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // notifications show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = notifications->add_subcommand("show", "Show notification details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Notification ID")->required();

        cmd->callback([id]() {
            try {
                auto notification = notifications_api::get_notification(*id);
                render_notification_detail(notification);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // notifications count
    // -----------------------------------------------------------------------
    {
        auto* cmd = notifications->add_subcommand("count", "Print unread notification count");

        cmd->callback([]() {
            try {
                int count = notifications_api::get_unread_count();
                if (get_output_format() == OutputFormat::Json) {
                    json j;
                    j["unread"] = count;
                    output_json(j);
                } else {
                    std::cout << count << std::endl;
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // notifications read <id> | --all
    // -----------------------------------------------------------------------
    {
        auto* cmd = notifications->add_subcommand("read", "Mark notification(s) as read");

        struct ReadOpts {
            std::string id;
            bool all = false;
        };
        auto opts = std::make_shared<ReadOpts>();

        cmd->add_option("id", opts->id, "Notification ID to mark as read");
        cmd->add_flag("--all,-a", opts->all, "Mark all notifications as read");

        cmd->callback([opts]() {
            try {
                if (opts->all) {
                    notifications_api::mark_all_read();
                    print_success("Marked all notifications as read");
                } else if (!opts->id.empty()) {
                    notifications_api::mark_read(opts->id);
                    print_success("Marked notification as read: " + opts->id);
                } else {
                    print_error("Provide a notification ID or use --all");
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // notifications archive <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = notifications->add_subcommand("archive", "Archive a notification");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Notification ID")->required();

        cmd->callback([id]() {
            try {
                notifications_api::archive_notification(*id);
                print_success("Archived notification: " + *id);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // notifications snooze <id> --until DATETIME
    // -----------------------------------------------------------------------
    {
        auto* cmd = notifications->add_subcommand("snooze", "Snooze a notification until a specified time");

        struct SnoozeOpts {
            std::string id;
            std::string until;
        };
        auto opts = std::make_shared<SnoozeOpts>();

        cmd->add_option("id", opts->id, "Notification ID")->required();
        cmd->add_option("--until", opts->until, "ISO 8601 datetime to snooze until (e.g., 2026-03-01T09:00:00Z)")->required();

        cmd->callback([opts]() {
            try {
                notifications_api::snooze_notification(opts->id, opts->until);
                print_success("Snoozed notification " + opts->id + " until " + opts->until);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
