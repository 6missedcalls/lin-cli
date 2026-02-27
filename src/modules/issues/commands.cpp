#include "modules/issues/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/filter.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/issues/api.h"
#include "modules/issues/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

void render_issue_table(const std::vector<Issue>& issues) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"IDENTIFIER", "PRIORITY", "TITLE", "STATE", "ASSIGNEE", "DUE DATE"});
        for (const auto& issue : issues) {
            output_csv_row({
                issue.identifier,
                issue.priority_label,
                issue.title,
                issue.state_name.value_or(""),
                issue.assignee_name.value_or("Unassigned"),
                issue.due_date.value_or("")
            });
        }
        return;
    }

    TableRenderer table({
        {"IDENTIFIER", 6, 12, false},
        {"PRIORITY",   4, 10, false},
        {"TITLE",      8, 60, false},
        {"STATE",      4, 16, false},
        {"ASSIGNEE",   4, 20, false},
        {"DUE DATE",   4, 12, false}
    });

    for (const auto& issue : issues) {
        auto priority_val = static_cast<int>(issue.priority);
        std::string priority_str = color::priority(priority_val, issue.priority_label);
        std::string state_str = issue.state_type.has_value()
            ? color::state_type(issue.state_type.value(), issue.state_name.value_or(""))
            : issue.state_name.value_or("");

        table.add_row({
            issue.identifier,
            priority_str,
            issue.title,
            state_str,
            issue.assignee_name.value_or("Unassigned"),
            issue.due_date.value_or("")
        });
    }

    if (table.empty()) {
        print_warning("No issues found.");
        return;
    }

    table.render(std::cout);
}

void render_issue_json(const std::vector<Issue>& issues) {
    json arr = json::array();
    for (const auto& issue : issues) {
        json j;
        j["id"] = issue.id;
        j["identifier"] = issue.identifier;
        j["title"] = issue.title;
        j["priority"] = issue.priority;
        j["priorityLabel"] = issue.priority_label;
        j["state"] = issue.state_name.value_or("");
        j["stateType"] = issue.state_type.value_or("");
        j["assignee"] = issue.assignee_name.value_or("");
        j["dueDate"] = issue.due_date.value_or("");
        j["url"] = issue.url;
        j["branchName"] = issue.branch_name;
        j["teamKey"] = issue.team_key.value_or("");
        j["createdAt"] = issue.created_at;
        j["updatedAt"] = issue.updated_at;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_issue_detail(const Issue& issue) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = issue.id;
        j["identifier"] = issue.identifier;
        j["title"] = issue.title;
        j["priority"] = issue.priority;
        j["priorityLabel"] = issue.priority_label;
        j["state"] = issue.state_name.value_or("");
        j["stateType"] = issue.state_type.value_or("");
        j["assignee"] = issue.assignee_name.value_or("");
        j["assigneeId"] = issue.assignee_id.value_or("");
        j["team"] = issue.team_name.value_or("");
        j["teamKey"] = issue.team_key.value_or("");
        j["project"] = issue.project_name.value_or("");
        j["dueDate"] = issue.due_date.value_or("");
        j["estimate"] = issue.estimate.has_value() ? json(issue.estimate.value()) : json(nullptr);
        j["url"] = issue.url;
        j["branchName"] = issue.branch_name;
        j["description"] = issue.description.value_or("");
        j["labels"] = issue.label_names;
        j["parentIdentifier"] = issue.parent_identifier.value_or("");
        j["createdAt"] = issue.created_at;
        j["updatedAt"] = issue.updated_at;
        j["completedAt"] = issue.completed_at.value_or("");
        j["canceledAt"] = issue.canceled_at.value_or("");
        j["archivedAt"] = issue.archived_at.value_or("");
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(issue.identifier + "  " + issue.title);

    auto priority_val = static_cast<int>(issue.priority);
    detail.add_field("Priority", color::priority(priority_val, issue.priority_label));

    std::string state_str = issue.state_type.has_value()
        ? color::state_type(issue.state_type.value(), issue.state_name.value_or(""))
        : issue.state_name.value_or("");
    detail.add_field("State", state_str);

    detail.add_field("Assignee", issue.assignee_name.value_or("Unassigned"));
    detail.add_field("Team", issue.team_name.value_or(""));

    if (issue.project_name.has_value()) {
        detail.add_field("Project", issue.project_name.value());
    }
    if (issue.cycle_number.has_value()) {
        detail.add_field("Cycle", std::to_string(static_cast<int>(issue.cycle_number.value())));
    }
    if (issue.parent_identifier.has_value()) {
        detail.add_field("Parent", issue.parent_identifier.value());
    }
    if (issue.estimate.has_value()) {
        detail.add_field("Estimate", std::to_string(static_cast<int>(issue.estimate.value())));
    }
    if (issue.due_date.has_value()) {
        detail.add_field("Due Date", issue.due_date.value());
    }
    if (!issue.label_names.empty()) {
        std::string labels;
        for (size_t i = 0; i < issue.label_names.size(); ++i) {
            if (i > 0) labels += ", ";
            labels += issue.label_names[i];
        }
        detail.add_field("Labels", labels);
    }

    detail.add_field("Created", issue.created_at);
    detail.add_field("Updated", issue.updated_at);

    if (issue.completed_at.has_value()) {
        detail.add_field("Completed", issue.completed_at.value());
    }
    if (issue.canceled_at.has_value()) {
        detail.add_field("Canceled", issue.canceled_at.value());
    }
    if (issue.archived_at.has_value()) {
        detail.add_field("Archived", issue.archived_at.value());
    }

    detail.add_field("URL", issue.url);
    detail.add_field("Branch", issue.branch_name);

    if (issue.description.has_value() && !issue.description.value().empty()) {
        detail.add_blank_line();
        detail.add_section("Description");
        detail.add_markdown(issue.description.value());
    }

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void issues_commands::register_commands(CLI::App& app) {
    auto* issues = app.add_subcommand("issues", "Manage issues");
    issues->require_subcommand(1);

    // -----------------------------------------------------------------------
    // issues list
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("list", "List issues");

        struct ListOpts {
            std::string team;
            std::string assignee;
            bool me = false;
            std::string state;
            std::string state_type;
            std::string priority;
            std::string label;
            std::string project;
            std::string cycle;
            std::string creator;
            bool include_archived = false;
            bool all = false;
            int limit = 50;
            std::string sort;
            std::string order;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--team", opts->team, "Filter by team ID or key");
        cmd->add_option("--assignee", opts->assignee, "Filter by assignee ID");
        cmd->add_flag("--me", opts->me, "Filter to issues assigned to me");
        cmd->add_option("--state", opts->state, "Filter by state name or ID");
        cmd->add_option("--state-type", opts->state_type, "Filter by state type (triage, backlog, unstarted, started, completed, canceled)");
        cmd->add_option("--priority", opts->priority, "Filter by priority (none, urgent, high, normal, low)");
        cmd->add_option("--label", opts->label, "Filter by label ID or name");
        cmd->add_option("--project", opts->project, "Filter by project ID");
        cmd->add_option("--cycle", opts->cycle, "Filter by cycle ID");
        cmd->add_option("--creator", opts->creator, "Filter by creator ID");
        cmd->add_flag("--include-archived", opts->include_archived, "Include archived issues");
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of issues to return")->default_val(50);
        cmd->add_option("--sort", opts->sort, "Sort field (created, updated, priority)");
        cmd->add_option("--order", opts->order, "Sort order (asc, desc)");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> team_opt = opts->team.empty() ? std::nullopt : std::make_optional(opts->team);
                std::optional<std::string> assignee_opt = opts->assignee.empty() ? std::nullopt : std::make_optional(opts->assignee);
                std::optional<std::string> state_opt = opts->state.empty() ? std::nullopt : std::make_optional(opts->state);
                std::optional<std::string> state_type_opt = opts->state_type.empty() ? std::nullopt : std::make_optional(opts->state_type);
                std::optional<std::string> priority_opt = opts->priority.empty() ? std::nullopt : std::make_optional(opts->priority);
                std::optional<std::string> label_opt = opts->label.empty() ? std::nullopt : std::make_optional(opts->label);
                std::optional<std::string> project_opt = opts->project.empty() ? std::nullopt : std::make_optional(opts->project);
                std::optional<std::string> cycle_opt = opts->cycle.empty() ? std::nullopt : std::make_optional(opts->cycle);
                std::optional<std::string> creator_opt = opts->creator.empty() ? std::nullopt : std::make_optional(opts->creator);

                if (opts->me) {
                    auto viewer = issues_api::get_viewer();
                    assignee_opt = viewer.id;
                }

                json filter = build_issue_filter(
                    team_opt, assignee_opt, state_opt, state_type_opt,
                    priority_opt, label_opt, project_opt, cycle_opt, creator_opt
                );

                std::optional<std::string> order_by;
                if (!opts->sort.empty()) {
                    std::string sort_val = opts->sort;
                    if (!opts->order.empty()) {
                        // Capitalize first letter for the API
                        std::string dir = opts->order;
                        if (dir == "asc") {
                            sort_val = "createdAt";
                            if (opts->sort == "updated") sort_val = "updatedAt";
                            if (opts->sort == "priority") sort_val = "priority";
                        }
                    }
                    order_by = sort_val;
                }

                IssueListOptions list_opts;
                list_opts.first = opts->limit;
                list_opts.filter = filter;
                list_opts.order_by = order_by;

                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = list_opts.first;
                    pag_opts.fetch_all = true;
                    pag_opts.limit = opts->limit;

                    Paginator<Issue> paginator(
                        [&](const PaginationOptions& po) -> Connection<Issue> {
                            IssueListOptions lo = list_opts;
                            lo.first = po.first;
                            lo.after = po.after;
                            return issues_api::list_issues(lo);
                        },
                        pag_opts
                    );

                    auto all_issues = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_issue_json(all_issues);
                    } else {
                        render_issue_table(all_issues);
                    }
                } else {
                    auto connection = issues_api::list_issues(list_opts);
                    if (get_output_format() == OutputFormat::Json) {
                        render_issue_json(connection.nodes);
                    } else {
                        render_issue_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More issues available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues show <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("show", "Show issue details");
        auto identifier = std::make_shared<std::string>();
        cmd->add_option("identifier", *identifier, "Issue identifier (e.g., ENG-123)")->required();

        cmd->callback([identifier]() {
            try {
                auto issue = issues_api::get_issue(*identifier);
                render_issue_detail(issue);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues create
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("create", "Create a new issue");

        struct CreateOpts {
            std::string title;
            std::string team;
            std::string description;
            std::string assignee;
            std::string priority;
            std::string state;
            std::vector<std::string> labels;
            std::string project;
            std::string cycle;
            std::string parent;
            double estimate = -1;
            std::string due_date;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("--title,-t", opts->title, "Issue title")->required();
        cmd->add_option("--team", opts->team, "Team ID (required unless default set)")->required();
        cmd->add_option("--description,-d", opts->description, "Issue description");
        cmd->add_option("--assignee", opts->assignee, "Assignee ID");
        cmd->add_option("--priority,-p", opts->priority, "Priority (none, urgent, high, normal, low)");
        cmd->add_option("--state", opts->state, "State ID");
        cmd->add_option("--label,-l", opts->labels, "Label ID (repeatable)");
        cmd->add_option("--project", opts->project, "Project ID");
        cmd->add_option("--cycle", opts->cycle, "Cycle ID");
        cmd->add_option("--parent", opts->parent, "Parent issue ID");
        cmd->add_option("--estimate", opts->estimate, "Point estimate");
        cmd->add_option("--due-date", opts->due_date, "Due date (YYYY-MM-DD)");

        cmd->callback([opts]() {
            try {
                IssueCreateInput input;
                input.title = opts->title;
                input.team_id = opts->team;

                if (!opts->description.empty()) input.description = opts->description;
                if (!opts->assignee.empty()) input.assignee_id = opts->assignee;
                if (!opts->state.empty()) input.state_id = opts->state;
                if (!opts->project.empty()) input.project_id = opts->project;
                if (!opts->cycle.empty()) input.cycle_id = opts->cycle;
                if (!opts->parent.empty()) input.parent_id = opts->parent;
                if (!opts->due_date.empty()) input.due_date = opts->due_date;
                if (opts->estimate >= 0) input.estimate = opts->estimate;

                if (!opts->priority.empty()) {
                    auto prio = priority_name_to_number(opts->priority);
                    if (prio.has_value()) {
                        input.priority = prio.value();
                    } else {
                        print_error("Invalid priority: " + opts->priority + ". Use: none, urgent, high, normal, low");
                        return;
                    }
                }

                input.label_ids = opts->labels;

                auto issue = issues_api::create_issue(input);
                print_success("Created " + issue.identifier);
                render_issue_detail(issue);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues update <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("update", "Update an issue");

        struct UpdateOpts {
            std::string identifier;
            std::string title;
            std::string description;
            std::string assignee;
            std::string priority;
            std::string state;
            std::string project;
            std::string cycle;
            std::string parent;
            double estimate = -1;
            std::string due_date;
        };
        auto opts = std::make_shared<UpdateOpts>();

        cmd->add_option("identifier", opts->identifier, "Issue identifier (e.g., ENG-123)")->required();
        cmd->add_option("--title,-t", opts->title, "New title");
        cmd->add_option("--description,-d", opts->description, "New description");
        cmd->add_option("--assignee", opts->assignee, "New assignee ID");
        cmd->add_option("--priority,-p", opts->priority, "New priority (none, urgent, high, normal, low)");
        cmd->add_option("--state", opts->state, "New state ID");
        cmd->add_option("--project", opts->project, "New project ID");
        cmd->add_option("--cycle", opts->cycle, "New cycle ID");
        cmd->add_option("--parent", opts->parent, "New parent issue ID");
        cmd->add_option("--estimate", opts->estimate, "New point estimate");
        cmd->add_option("--due-date", opts->due_date, "New due date (YYYY-MM-DD)");

        cmd->callback([opts]() {
            try {
                auto issue = issues_api::get_issue(opts->identifier);

                IssueUpdateInput input;
                if (!opts->title.empty()) input.title = opts->title;
                if (!opts->description.empty()) input.description = opts->description;
                if (!opts->assignee.empty()) input.assignee_id = opts->assignee;
                if (!opts->state.empty()) input.state_id = opts->state;
                if (!opts->project.empty()) input.project_id = opts->project;
                if (!opts->cycle.empty()) input.cycle_id = opts->cycle;
                if (!opts->parent.empty()) input.parent_id = opts->parent;
                if (!opts->due_date.empty()) input.due_date = opts->due_date;
                if (opts->estimate >= 0) input.estimate = opts->estimate;

                if (!opts->priority.empty()) {
                    auto prio = priority_name_to_number(opts->priority);
                    if (prio.has_value()) {
                        input.priority = prio.value();
                    } else {
                        print_error("Invalid priority: " + opts->priority + ". Use: none, urgent, high, normal, low");
                        return;
                    }
                }

                auto updated = issues_api::update_issue(issue.id, input);
                print_success("Updated " + updated.identifier);
                render_issue_detail(updated);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues delete <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("delete", "Delete an issue");

        struct DeleteOpts {
            std::string identifier;
            bool permanent = false;
            bool yes = false;
        };
        auto opts = std::make_shared<DeleteOpts>();

        cmd->add_option("identifier", opts->identifier, "Issue identifier (e.g., ENG-123)")->required();
        cmd->add_flag("--permanent", opts->permanent, "Permanently delete (not just trash)");
        cmd->add_flag("--yes,-y", opts->yes, "Skip confirmation");

        cmd->callback([opts]() {
            try {
                auto issue = issues_api::get_issue(opts->identifier);

                if (!opts->yes) {
                    std::string action = opts->permanent ? "permanently delete" : "delete";
                    std::cerr << "Are you sure you want to " << action
                              << " " << issue.identifier << " (" << issue.title << ")? [y/N] ";
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (confirm != "y" && confirm != "Y" && confirm != "yes") {
                        print_warning("Aborted.");
                        return;
                    }
                }

                issues_api::delete_issue(issue.id, opts->permanent);
                std::string action = opts->permanent ? "Permanently deleted" : "Deleted";
                print_success(action + " " + issue.identifier);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues archive <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("archive", "Archive an issue");
        auto identifier = std::make_shared<std::string>();
        cmd->add_option("identifier", *identifier, "Issue identifier (e.g., ENG-123)")->required();

        cmd->callback([identifier]() {
            try {
                auto issue = issues_api::get_issue(*identifier);
                issues_api::archive_issue(issue.id);
                print_success("Archived " + issue.identifier);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues unarchive <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("unarchive", "Unarchive an issue");
        auto identifier = std::make_shared<std::string>();
        cmd->add_option("identifier", *identifier, "Issue identifier (e.g., ENG-123)")->required();

        cmd->callback([identifier]() {
            try {
                auto issue = issues_api::get_issue(*identifier);
                issues_api::unarchive_issue(issue.id);
                print_success("Unarchived " + issue.identifier);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues search <query>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("search", "Search issues");

        struct SearchOpts {
            std::string query;
            std::string team;
            bool include_comments = false;
            int limit = 20;
        };
        auto opts = std::make_shared<SearchOpts>();

        cmd->add_option("query", opts->query, "Search query text")->required();
        cmd->add_option("--team", opts->team, "Filter by team ID");
        cmd->add_flag("--include-comments", opts->include_comments, "Include comment text in search");
        cmd->add_option("--limit,-n", opts->limit, "Maximum results")->default_val(20);

        cmd->callback([opts]() {
            try {
                std::optional<std::string> team_opt = opts->team.empty() ? std::nullopt : std::make_optional(opts->team);

                auto connection = issues_api::search_issues(
                    opts->query, team_opt, opts->include_comments, opts->limit
                );

                if (get_output_format() == OutputFormat::Json) {
                    render_issue_json(connection.nodes);
                } else {
                    render_issue_table(connection.nodes);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues assign <identifier> <assignee>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("assign", "Assign an issue");

        struct AssignOpts {
            std::string identifier;
            std::string assignee;
            bool me = false;
        };
        auto opts = std::make_shared<AssignOpts>();

        cmd->add_option("identifier", opts->identifier, "Issue identifier (e.g., ENG-123)")->required();
        cmd->add_option("assignee", opts->assignee, "Assignee user ID");
        cmd->add_flag("--me", opts->me, "Assign to yourself");

        cmd->callback([opts]() {
            try {
                auto issue = issues_api::get_issue(opts->identifier);

                std::string assignee_id = opts->assignee;
                if (opts->me) {
                    auto viewer = issues_api::get_viewer();
                    assignee_id = viewer.id;
                }

                if (assignee_id.empty()) {
                    print_error("Provide an assignee ID or use --me");
                    return;
                }

                IssueUpdateInput input;
                input.assignee_id = assignee_id;

                auto updated = issues_api::update_issue(issue.id, input);
                print_success("Assigned " + updated.identifier + " to " + updated.assignee_name.value_or(assignee_id));
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues move <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("move", "Move an issue to a different state");

        struct MoveOpts {
            std::string identifier;
            std::string state;
        };
        auto opts = std::make_shared<MoveOpts>();

        cmd->add_option("identifier", opts->identifier, "Issue identifier (e.g., ENG-123)")->required();
        cmd->add_option("--state", opts->state, "Target state ID")->required();

        cmd->callback([opts]() {
            try {
                auto issue = issues_api::get_issue(opts->identifier);

                IssueUpdateInput input;
                input.state_id = opts->state;

                auto updated = issues_api::update_issue(issue.id, input);
                print_success("Moved " + updated.identifier + " to " + updated.state_name.value_or(opts->state));
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues label (subcommand group)
    // -----------------------------------------------------------------------
    {
        auto* label_cmd = issues->add_subcommand("label", "Manage issue labels");
        label_cmd->require_subcommand(1);

        // issues label add <identifier> <label>
        {
            auto* cmd = label_cmd->add_subcommand("add", "Add a label to an issue");

            struct LabelAddOpts {
                std::string identifier;
                std::string label;
            };
            auto opts = std::make_shared<LabelAddOpts>();

            cmd->add_option("identifier", opts->identifier, "Issue identifier (e.g., ENG-123)")->required();
            cmd->add_option("label", opts->label, "Label ID")->required();

            cmd->callback([opts]() {
                try {
                    auto issue = issues_api::get_issue(opts->identifier);
                    issues_api::add_label(issue.id, opts->label);
                    print_success("Added label to " + issue.identifier);
                } catch (const LinError& e) {
                    print_error(format_error(e));
                }
            });
        }

        // issues label remove <identifier> <label>
        {
            auto* cmd = label_cmd->add_subcommand("remove", "Remove a label from an issue");

            struct LabelRemoveOpts {
                std::string identifier;
                std::string label;
            };
            auto opts = std::make_shared<LabelRemoveOpts>();

            cmd->add_option("identifier", opts->identifier, "Issue identifier (e.g., ENG-123)")->required();
            cmd->add_option("label", opts->label, "Label ID")->required();

            cmd->callback([opts]() {
                try {
                    auto issue = issues_api::get_issue(opts->identifier);
                    issues_api::remove_label(issue.id, opts->label);
                    print_success("Removed label from " + issue.identifier);
                } catch (const LinError& e) {
                    print_error(format_error(e));
                }
            });
        }
    }

    // -----------------------------------------------------------------------
    // issues relate <identifier> <related>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("relate", "Create an issue relation");

        struct RelateOpts {
            std::string identifier;
            std::string related;
            std::string type = "related";
        };
        auto opts = std::make_shared<RelateOpts>();

        cmd->add_option("identifier", opts->identifier, "Source issue identifier")->required();
        cmd->add_option("related", opts->related, "Related issue identifier or ID")->required();
        cmd->add_option("--type", opts->type, "Relation type (related, blocks, duplicate, similar)")->default_val("related");

        cmd->callback([opts]() {
            try {
                auto issue = issues_api::get_issue(opts->identifier);
                auto related_issue = issues_api::get_issue(opts->related);

                auto relation = issues_api::create_relation(issue.id, related_issue.id, opts->type);
                print_success(
                    "Created " + opts->type + " relation between "
                    + issue.identifier + " and " + related_issue.identifier
                );

                if (get_output_format() == OutputFormat::Json) {
                    json j;
                    j["id"] = relation.id;
                    j["type"] = relation.type;
                    j["issueIdentifier"] = relation.issue_identifier.value_or("");
                    j["relatedIssueIdentifier"] = relation.related_issue_identifier.value_or("");
                    output_json(j);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues unrelate <relation_id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("unrelate", "Delete an issue relation");
        auto relation_id = std::make_shared<std::string>();
        cmd->add_option("relation_id", *relation_id, "Relation ID to delete")->required();

        cmd->callback([relation_id]() {
            try {
                issues_api::delete_relation(*relation_id);
                print_success("Deleted relation " + *relation_id);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues subscribe <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("subscribe", "Subscribe to an issue");
        auto identifier = std::make_shared<std::string>();
        cmd->add_option("identifier", *identifier, "Issue identifier (e.g., ENG-123)")->required();

        cmd->callback([identifier]() {
            try {
                auto issue = issues_api::get_issue(*identifier);
                issues_api::subscribe(issue.id);
                print_success("Subscribed to " + issue.identifier);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues unsubscribe <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("unsubscribe", "Unsubscribe from an issue");
        auto identifier = std::make_shared<std::string>();
        cmd->add_option("identifier", *identifier, "Issue identifier (e.g., ENG-123)")->required();

        cmd->callback([identifier]() {
            try {
                auto issue = issues_api::get_issue(*identifier);
                issues_api::unsubscribe(issue.id);
                print_success("Unsubscribed from " + issue.identifier);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues branch <identifier>
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("branch", "Print git branch name for an issue");
        auto identifier = std::make_shared<std::string>();
        cmd->add_option("identifier", *identifier, "Issue identifier (e.g., ENG-123)")->required();

        cmd->callback([identifier]() {
            try {
                auto issue = issues_api::get_issue(*identifier);
                std::cout << issue.branch_name << std::endl;
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues priorities — list workspace priority values
    // -----------------------------------------------------------------------
    {
        auto* cmd = issues->add_subcommand("priorities", "List workspace priority values");

        cmd->callback([]() {
            try {
                auto values = issues_api::list_priority_values();

                if (get_output_format() == OutputFormat::Json) {
                    json arr = json::array();
                    for (const auto& pv : values) {
                        arr.push_back({{"priority", pv.priority}, {"label", pv.label}});
                    }
                    output_json(arr);
                    return;
                }

                if (get_output_format() == OutputFormat::Csv) {
                    output_csv_header({"PRIORITY", "LABEL"});
                    for (const auto& pv : values) {
                        output_csv_row({std::to_string(pv.priority), pv.label});
                    }
                    return;
                }

                TableRenderer table({
                    {"PRIORITY", 4, 10, false},
                    {"LABEL",    4, 30, false},
                });
                for (const auto& pv : values) {
                    table.add_row({
                        color::priority(pv.priority, std::to_string(pv.priority)),
                        color::priority(pv.priority, pv.label),
                    });
                }
                table.render(std::cout);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // issues bulk (subcommand group)
    // -----------------------------------------------------------------------
    {
        auto* bulk_cmd = issues->add_subcommand("bulk", "Bulk operations on issues");
        bulk_cmd->require_subcommand(1);

        // issues bulk update <ids...>
        {
            auto* cmd = bulk_cmd->add_subcommand("update", "Bulk update multiple issues");

            struct BulkUpdateOpts {
                std::vector<std::string> identifiers;
                std::string state;
                std::string assignee;
                std::string priority;
                std::string label;
                std::string project;
            };
            auto opts = std::make_shared<BulkUpdateOpts>();

            cmd->add_option("identifiers", opts->identifiers, "Issue identifiers (e.g., ENG-123 ENG-456)")->required()->expected(-1);
            cmd->add_option("--state", opts->state, "New state ID");
            cmd->add_option("--assignee", opts->assignee, "New assignee ID");
            cmd->add_option("--priority", opts->priority, "New priority (none, urgent, high, normal, low)");
            cmd->add_option("--label", opts->label, "Label ID to add");
            cmd->add_option("--project", opts->project, "New project ID");

            cmd->callback([opts]() {
                try {
                    // Resolve identifiers to IDs
                    std::vector<std::string> ids;
                    ids.reserve(opts->identifiers.size());
                    for (const auto& ident : opts->identifiers) {
                        auto issue = issues_api::get_issue(ident);
                        ids.push_back(issue.id);
                    }

                    IssueUpdateInput input;
                    if (!opts->state.empty()) input.state_id = opts->state;
                    if (!opts->assignee.empty()) input.assignee_id = opts->assignee;
                    if (!opts->project.empty()) input.project_id = opts->project;

                    if (!opts->priority.empty()) {
                        auto prio = priority_name_to_number(opts->priority);
                        if (prio.has_value()) {
                            input.priority = prio.value();
                        } else {
                            print_error("Invalid priority: " + opts->priority + ". Use: none, urgent, high, normal, low");
                            return;
                        }
                    }

                    int count = issues_api::bulk_update(ids, input);
                    print_success("Updated " + std::to_string(count) + " issue" + (count == 1 ? "" : "s"));
                } catch (const LinError& e) {
                    print_error(format_error(e));
                }
            });
        }
    }
}
