#include "modules/comments/commands.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/comments/api.h"
#include "modules/comments/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

// Truncate a string to max_len characters, appending "..." if truncated.
std::string truncate_body(const std::string& s, size_t max_len) {
    if (s.size() <= max_len) {
        return s;
    }
    return s.substr(0, max_len - 3) + "...";
}

// Shorten an ISO 8601 timestamp to just the date portion (YYYY-MM-DD).
std::string date_only(const std::string& ts) {
    if (ts.size() >= 10) {
        return ts.substr(0, 10);
    }
    return ts;
}

void render_comment_table(const std::vector<Comment>& comments) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"AUTHOR", "DATE", "BODY"});
        for (const auto& comment : comments) {
            output_csv_row({
                comment.user_name.value_or(""),
                date_only(comment.created_at),
                comment.body
            });
        }
        return;
    }

    TableRenderer table({
        {"AUTHOR", 6, 20, false},
        {"DATE",   4, 12, false},
        {"BODY",   8, 60, false}
    });

    for (const auto& comment : comments) {
        table.add_row({
            comment.user_name.value_or(""),
            date_only(comment.created_at),
            truncate_body(comment.body, 60)
        });
    }

    if (table.empty()) {
        print_warning("No comments found.");
        return;
    }

    table.render(std::cout);
}

void render_comment_json(const std::vector<Comment>& comments) {
    json arr = json::array();
    for (const auto& comment : comments) {
        json j;
        j["id"] = comment.id;
        j["body"] = comment.body;
        j["url"] = comment.url;
        j["author"] = comment.user_name.value_or("");
        j["authorId"] = comment.user_id.value_or("");
        j["issueId"] = comment.issue_id.value_or("");
        j["parentId"] = comment.parent_id.value_or("");
        j["createdAt"] = comment.created_at;
        j["updatedAt"] = comment.updated_at;
        j["editedAt"] = comment.edited_at.has_value() ? json(comment.edited_at.value()) : json(nullptr);
        j["resolvedAt"] = comment.resolved_at.has_value() ? json(comment.resolved_at.value()) : json(nullptr);
        arr.push_back(j);
    }
    output_json(arr);
}

void render_comment_detail(const Comment& comment) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = comment.id;
        j["body"] = comment.body;
        j["url"] = comment.url;
        j["author"] = comment.user_name.value_or("");
        j["authorId"] = comment.user_id.value_or("");
        j["issueId"] = comment.issue_id.value_or("");
        j["parentId"] = comment.parent_id.value_or("");
        j["createdAt"] = comment.created_at;
        j["updatedAt"] = comment.updated_at;
        j["editedAt"] = comment.edited_at.has_value() ? json(comment.edited_at.value()) : json(nullptr);
        j["resolvedAt"] = comment.resolved_at.has_value() ? json(comment.resolved_at.value()) : json(nullptr);
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section("Comment " + comment.id);

    detail.add_field("Author", comment.user_name.value_or(""));
    detail.add_field("Created", comment.created_at);
    detail.add_field("Updated", comment.updated_at);

    if (comment.edited_at.has_value()) {
        detail.add_field("Edited", comment.edited_at.value());
    }
    if (comment.resolved_at.has_value()) {
        detail.add_field("Resolved", comment.resolved_at.value());
    }
    if (comment.issue_id.has_value()) {
        detail.add_field("Issue ID", comment.issue_id.value());
    }
    if (comment.parent_id.has_value()) {
        detail.add_field("Parent Comment", comment.parent_id.value());
    }

    detail.add_field("URL", comment.url);

    detail.add_blank_line();
    detail.add_section("Body");
    detail.add_markdown(comment.body);

    detail.render(std::cout);
}

std::string read_file_content(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw LinError(ErrorKind::Validation, "Cannot open file: " + path);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void comments_commands::register_commands(CLI::App& app) {
    auto* comments = app.add_subcommand("comments", "Manage issue comments");
    comments->require_subcommand(1);

    // -----------------------------------------------------------------------
    // comments list <issue>
    // -----------------------------------------------------------------------
    {
        auto* cmd = comments->add_subcommand("list", "List comments on an issue");

        struct ListOpts {
            std::string issue;
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("issue", opts->issue, "Issue ID or identifier (e.g., ENG-123)")->required();
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of comments to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = opts->limit;
                    pag_opts.fetch_all = true;
                    pag_opts.limit = opts->limit;

                    Paginator<Comment> paginator(
                        [&](const PaginationOptions& po) -> Connection<Comment> {
                            return comments_api::list_comments(opts->issue, po.first, po.after);
                        },
                        pag_opts
                    );

                    auto all_comments = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_comment_json(all_comments);
                    } else {
                        render_comment_table(all_comments);
                    }
                } else {
                    auto connection = comments_api::list_comments(opts->issue, opts->limit, std::nullopt);
                    if (get_output_format() == OutputFormat::Json) {
                        render_comment_json(connection.nodes);
                    } else {
                        render_comment_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More comments available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // comments show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = comments->add_subcommand("show", "Show full comment body");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Comment ID")->required();

        cmd->callback([id]() {
            try {
                auto comment = comments_api::get_comment(*id);
                render_comment_detail(comment);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // comments create <issue> --body TEXT [--body-file PATH]
    // -----------------------------------------------------------------------
    {
        auto* cmd = comments->add_subcommand("create", "Create a comment on an issue");

        struct CreateOpts {
            std::string issue;
            std::string body;
            std::string body_file;
            std::string parent_id;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("issue", opts->issue, "Issue ID or identifier (e.g., ENG-123)")->required();
        cmd->add_option("--body,-b", opts->body, "Comment body text (Markdown supported)");
        cmd->add_option("--body-file", opts->body_file, "Path to a file containing the comment body");
        cmd->add_option("--parent", opts->parent_id, "Parent comment ID (for replies)");

        cmd->callback([opts]() {
            try {
                if (opts->body.empty() && opts->body_file.empty()) {
                    print_error("Provide comment text via --body or --body-file");
                    return;
                }
                if (!opts->body.empty() && !opts->body_file.empty()) {
                    print_error("Provide only one of --body or --body-file, not both");
                    return;
                }

                std::string body_text = opts->body.empty()
                    ? read_file_content(opts->body_file)
                    : opts->body;

                std::optional<std::string> parent_opt = opts->parent_id.empty()
                    ? std::nullopt
                    : std::make_optional(opts->parent_id);

                auto comment = comments_api::create_comment(opts->issue, body_text, parent_opt);
                print_success("Created comment " + comment.id);
                render_comment_detail(comment);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // comments update <id> --body TEXT
    // -----------------------------------------------------------------------
    {
        auto* cmd = comments->add_subcommand("update", "Update a comment's body");

        struct UpdateOpts {
            std::string id;
            std::string body;
            std::string body_file;
        };
        auto opts = std::make_shared<UpdateOpts>();

        cmd->add_option("id", opts->id, "Comment ID")->required();
        cmd->add_option("--body,-b", opts->body, "New comment body text (Markdown supported)");
        cmd->add_option("--body-file", opts->body_file, "Path to a file containing the new comment body");

        cmd->callback([opts]() {
            try {
                if (opts->body.empty() && opts->body_file.empty()) {
                    print_error("Provide new comment text via --body or --body-file");
                    return;
                }
                if (!opts->body.empty() && !opts->body_file.empty()) {
                    print_error("Provide only one of --body or --body-file, not both");
                    return;
                }

                std::string body_text = opts->body.empty()
                    ? read_file_content(opts->body_file)
                    : opts->body;

                auto comment = comments_api::update_comment(opts->id, body_text);
                print_success("Updated comment " + comment.id);
                render_comment_detail(comment);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // comments delete <id> [--yes]
    // -----------------------------------------------------------------------
    {
        auto* cmd = comments->add_subcommand("delete", "Delete a comment");

        struct DeleteOpts {
            std::string id;
            bool yes = false;
        };
        auto opts = std::make_shared<DeleteOpts>();

        cmd->add_option("id", opts->id, "Comment ID")->required();
        cmd->add_flag("--yes,-y", opts->yes, "Skip confirmation prompt");

        cmd->callback([opts]() {
            try {
                if (!opts->yes) {
                    std::cerr << "Are you sure you want to delete comment " << opts->id << "? [y/N] ";
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (confirm != "y" && confirm != "Y" && confirm != "yes") {
                        print_warning("Aborted.");
                        return;
                    }
                }

                comments_api::delete_comment(opts->id);
                print_success("Deleted comment " + opts->id);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
