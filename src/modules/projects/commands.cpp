#include "modules/projects/commands.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/config.h"
#include "core/error.h"
#include "core/filter.h"
#include "core/output.h"
#include "modules/projects/api.h"
#include "modules/projects/model.h"
#include "modules/teams/api.h"
#include "modules/users/api.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

std::string format_progress(double progress) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0) << (progress * 100.0) << "%";
    return oss.str();
}

std::string health_label(const std::optional<std::string>& health) {
    if (!health.has_value()) return "";
    const auto& h = health.value();
    if (h == "onTrack") return color::green("On Track");
    if (h == "atRisk")  return color::yellow("At Risk");
    if (h == "offTrack") return color::red("Off Track");
    return h;
}

std::string status_label(
    const std::optional<std::string>& status_name,
    const std::optional<std::string>& status_type
) {
    if (!status_name.has_value()) return "";
    const std::string& name = status_name.value();
    if (!status_type.has_value()) return name;
    const std::string& type = status_type.value();
    if (type == "completed") return color::green(name);
    if (type == "canceled")  return color::gray(name);
    if (type == "started")   return color::yellow(name);
    return name;
}

void render_project_table(const std::vector<Project>& projects) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "STATUS", "HEALTH", "LEAD", "PROGRESS", "TARGET DATE"});
        for (const auto& p : projects) {
            output_csv_row({
                p.name,
                p.status_name.value_or(""),
                p.health.value_or(""),
                p.lead_name.value_or(""),
                format_progress(p.progress),
                p.target_date.value_or("")
            });
        }
        return;
    }

    TableRenderer table({
        {"NAME",        8, 40, false},
        {"STATUS",      4, 16, false},
        {"HEALTH",      4, 12, false},
        {"LEAD",        4, 20, false},
        {"PROGRESS",    4,  9, false},
        {"TARGET DATE", 4, 12, false}
    });

    for (const auto& p : projects) {
        table.add_row({
            p.name,
            status_label(p.status_name, p.status_type),
            health_label(p.health),
            p.lead_name.value_or(""),
            format_progress(p.progress),
            p.target_date.value_or("")
        });
    }

    if (table.empty()) {
        print_warning("No projects found.");
        return;
    }

    table.render(std::cout);
}

void render_project_json(const std::vector<Project>& projects) {
    json arr = json::array();
    for (const auto& p : projects) {
        json j;
        j["id"] = p.id;
        j["name"] = p.name;
        j["slugId"] = p.slug_id;
        j["url"] = p.url;
        j["status"] = p.status_name.value_or("");
        j["statusType"] = p.status_type.value_or("");
        j["health"] = p.health.value_or("");
        j["lead"] = p.lead_name.value_or("");
        j["progress"] = p.progress;
        j["targetDate"] = p.target_date.value_or("");
        j["startDate"] = p.start_date.value_or("");
        j["createdAt"] = p.created_at;
        j["updatedAt"] = p.updated_at;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_project_detail(const Project& p) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = p.id;
        j["name"] = p.name;
        j["slugId"] = p.slug_id;
        j["url"] = p.url;
        j["description"] = p.description.value_or("");
        j["icon"] = p.icon.value_or("");
        j["color"] = p.color.value_or("");
        j["priority"] = p.priority;
        j["priorityLabel"] = p.priority_label.value_or("");
        j["status"] = p.status_name.value_or("");
        j["statusType"] = p.status_type.value_or("");
        j["health"] = p.health.value_or("");
        j["lead"] = p.lead_name.value_or("");
        j["creator"] = p.creator_name.value_or("");
        j["progress"] = p.progress;
        j["scope"] = p.scope;
        j["startDate"] = p.start_date.value_or("");
        j["targetDate"] = p.target_date.value_or("");
        j["startedAt"] = p.started_at.value_or("");
        j["completedAt"] = p.completed_at.value_or("");
        j["canceledAt"] = p.canceled_at.value_or("");
        j["createdAt"] = p.created_at;
        j["updatedAt"] = p.updated_at;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(p.name);

    detail.add_field("Status", status_label(p.status_name, p.status_type));
    detail.add_field("Health", health_label(p.health));

    if (p.lead_name.has_value()) {
        detail.add_field("Lead", p.lead_name.value());
    }
    if (p.creator_name.has_value()) {
        detail.add_field("Creator", p.creator_name.value());
    }
    if (p.priority_label.has_value()) {
        detail.add_field("Priority", color::priority(p.priority, p.priority_label.value()));
    }

    detail.add_field("Progress", format_progress(p.progress));

    if (p.start_date.has_value()) {
        detail.add_field("Start Date", p.start_date.value());
    }
    if (p.target_date.has_value()) {
        detail.add_field("Target Date", p.target_date.value());
    }
    if (p.started_at.has_value()) {
        detail.add_field("Started", p.started_at.value());
    }
    if (p.completed_at.has_value()) {
        detail.add_field("Completed", p.completed_at.value());
    }
    if (p.canceled_at.has_value()) {
        detail.add_field("Canceled", p.canceled_at.value());
    }

    detail.add_field("Created", p.created_at);
    detail.add_field("Updated", p.updated_at);
    detail.add_field("URL", p.url);

    if (p.description.has_value() && !p.description.value().empty()) {
        detail.add_blank_line();
        detail.add_section("Description");
        detail.add_markdown(p.description.value());
    }

    detail.render(std::cout);
}

void render_milestone_table(const std::vector<ProjectMilestone>& milestones) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"NAME", "STATUS", "TARGET DATE", "PROGRESS"});
        for (const auto& m : milestones) {
            output_csv_row({
                m.name,
                m.status,
                m.target_date.value_or(""),
                format_progress(m.progress)
            });
        }
        return;
    }

    TableRenderer table({
        {"NAME",        8, 40, false},
        {"STATUS",      4, 12, false},
        {"TARGET DATE", 4, 12, false},
        {"PROGRESS",    4,  9, false}
    });

    for (const auto& m : milestones) {
        std::string status_str;
        if (m.status == "done")    status_str = color::green(m.status);
        else if (m.status == "overdue") status_str = color::red(m.status);
        else if (m.status == "next")    status_str = color::yellow(m.status);
        else                            status_str = m.status;

        table.add_row({
            m.name,
            status_str,
            m.target_date.value_or(""),
            format_progress(m.progress)
        });
    }

    if (table.empty()) {
        print_warning("No milestones found.");
        return;
    }

    table.render(std::cout);
}

void render_update_table(const std::vector<ProjectUpdate>& updates) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"HEALTH", "USER", "DATE", "BODY"});
        for (const auto& u : updates) {
            std::string body = u.body.size() > 80 ? u.body.substr(0, 77) + "..." : u.body;
            output_csv_row({
                u.health.value_or(""),
                u.user_name.value_or(""),
                u.created_at,
                body
            });
        }
        return;
    }

    TableRenderer table({
        {"HEALTH", 4, 12, false},
        {"USER",   4, 20, false},
        {"DATE",   4, 24, false},
        {"BODY",   8, 60, false}
    });

    for (const auto& u : updates) {
        std::string health_str = health_label(u.health);
        std::string body = u.body.size() > 60 ? u.body.substr(0, 57) + "..." : u.body;

        table.add_row({
            health_str,
            u.user_name.value_or(""),
            u.created_at,
            body
        });
    }

    if (table.empty()) {
        print_warning("No updates found.");
        return;
    }

    table.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void projects_commands::register_commands(CLI::App& app) {
    auto* projects = app.add_subcommand("projects", "Manage projects");
    projects->require_subcommand(1);

    // -----------------------------------------------------------------------
    // projects list
    // -----------------------------------------------------------------------
    {
        auto* cmd = projects->add_subcommand("list", "List projects");

        struct ListOpts {
            std::string status;
            std::string lead;
            std::string health;
            int limit = 50;
            bool all = false;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--status", opts->status, "Filter by status type (backlog, planned, started, paused, completed, canceled)");
        cmd->add_option("--lead", opts->lead, "Filter by lead user ID");
        cmd->add_option("--health", opts->health, "Filter by health (onTrack, atRisk, offTrack)");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of projects to return")->default_val(50);
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");

        cmd->callback([opts]() {
            try {
                std::optional<std::string> status_opt = opts->status.empty() ? std::nullopt : std::make_optional(opts->status);
                std::optional<std::string> lead_opt   = opts->lead.empty()   ? std::nullopt : std::make_optional(opts->lead);
                std::optional<std::string> health_opt = opts->health.empty() ? std::nullopt : std::make_optional(opts->health);

                json filter = build_project_filter(status_opt, lead_opt, health_opt);

                ProjectListOptions list_opts;
                list_opts.first = opts->limit;
                list_opts.filter = filter;

                auto connection = projects_api::list_projects(list_opts);
                if (get_output_format() == OutputFormat::Json) {
                    render_project_json(connection.nodes);
                } else {
                    render_project_table(connection.nodes);
                    if (connection.page_info.has_next_page) {
                        print_warning("More projects available. Use --all to fetch all pages.");
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // projects show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = projects->add_subcommand("show", "Show project details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Project ID")->required();

        cmd->callback([id]() {
            try {
                auto project = projects_api::get_project(*id);
                render_project_detail(project);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // projects create
    // -----------------------------------------------------------------------
    {
        auto* cmd = projects->add_subcommand("create", "Create a new project");

        struct CreateOpts {
            std::string name;
            std::string description;
            std::string icon;
            std::string color;
            std::string lead;
            std::string status;
            std::string priority;
            std::string start_date;
            std::string target_date;
            std::vector<std::string> team_ids;
            std::vector<std::string> member_ids;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("--name,-n", opts->name, "Project name")->required();
        cmd->add_option("--description,-d", opts->description, "Project description");
        cmd->add_option("--icon", opts->icon, "Project icon emoji");
        cmd->add_option("--color", opts->color, "Project color (hex)");
        cmd->add_option("--lead", opts->lead, "Lead user ID");
        cmd->add_option("--status", opts->status, "Project status ID");
        cmd->add_option("--priority,-p", opts->priority, "Priority (none, urgent, high, normal, low)");
        cmd->add_option("--start-date", opts->start_date, "Start date (YYYY-MM-DD)");
        cmd->add_option("--target-date", opts->target_date, "Target date (YYYY-MM-DD)");
        cmd->add_option("--team", opts->team_ids, "Team name, key, or ID (repeatable)");
        cmd->add_option("--member", opts->member_ids, "Member user ID (repeatable)");

        cmd->callback([opts]() {
            try {
                ProjectCreateInput input;
                input.name = opts->name;

                if (!opts->description.empty()) input.description = opts->description;
                if (!opts->icon.empty())        input.icon = opts->icon;
                if (!opts->color.empty())       input.color = opts->color;
                if (!opts->lead.empty())        input.lead_id = users_api::resolve_user_id(opts->lead);
                if (!opts->status.empty())      input.status_id = opts->status;
                if (!opts->start_date.empty())  input.start_date = opts->start_date;
                if (!opts->target_date.empty()) input.target_date = opts->target_date;

                // Resolve teams: explicit flag > config default > auto-detect single team
                std::vector<std::string> team_inputs = opts->team_ids;
                if (team_inputs.empty()) {
                    const Config config = load_config();
                    if (config.defaults.team.has_value() && !config.defaults.team->empty()) {
                        team_inputs.push_back(*config.defaults.team);
                    } else {
                        auto teams = teams_api::list_teams(2);
                        if (teams.nodes.size() == 1) {
                            team_inputs.push_back(teams.nodes.front().id);
                        } else {
                            print_error("No team specified. Use --team or set a default with: lin config set defaults.team \"YourTeam\"");
                            return;
                        }
                    }
                }
                std::vector<std::string> resolved_teams;
                resolved_teams.reserve(team_inputs.size());
                for (const auto& t : team_inputs) {
                    resolved_teams.push_back(teams_api::resolve_team_id(t));
                }
                input.team_ids = resolved_teams;

                // Resolve member names/emails to IDs
                std::vector<std::string> resolved_members;
                resolved_members.reserve(opts->member_ids.size());
                for (const auto& m : opts->member_ids) {
                    resolved_members.push_back(users_api::resolve_user_id(m));
                }
                input.member_ids = resolved_members;

                if (!opts->priority.empty()) {
                    auto prio = priority_name_to_number(opts->priority);
                    if (prio.has_value()) {
                        input.priority = prio.value();
                    } else {
                        print_error("Invalid priority: " + opts->priority + ". Use: none, urgent, high, normal, low");
                        return;
                    }
                }

                auto project = projects_api::create_project(input);
                print_success("Created project: " + project.name);
                render_project_detail(project);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // projects update <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = projects->add_subcommand("update", "Update a project");

        struct UpdateOpts {
            std::string id;
            std::string name;
            std::string description;
            std::string icon;
            std::string color;
            std::string lead;
            std::string status;
            std::string priority;
            std::string start_date;
            std::string target_date;
            std::string health;
        };
        auto opts = std::make_shared<UpdateOpts>();

        cmd->add_option("id", opts->id, "Project ID")->required();
        cmd->add_option("--name,-n", opts->name, "New project name");
        cmd->add_option("--description,-d", opts->description, "New description");
        cmd->add_option("--icon", opts->icon, "New icon emoji");
        cmd->add_option("--color", opts->color, "New color (hex)");
        cmd->add_option("--lead", opts->lead, "New lead user ID");
        cmd->add_option("--status", opts->status, "New status ID");
        cmd->add_option("--priority,-p", opts->priority, "New priority (none, urgent, high, normal, low)");
        cmd->add_option("--start-date", opts->start_date, "New start date (YYYY-MM-DD)");
        cmd->add_option("--target-date", opts->target_date, "New target date (YYYY-MM-DD)");
        cmd->add_option("--health", opts->health, "New health (onTrack, atRisk, offTrack)");

        cmd->callback([opts]() {
            try {
                ProjectUpdateInput input;

                if (!opts->name.empty())        input.name = opts->name;
                if (!opts->description.empty()) input.description = opts->description;
                if (!opts->icon.empty())        input.icon = opts->icon;
                if (!opts->color.empty())       input.color = opts->color;
                if (!opts->lead.empty())        input.lead_id = users_api::resolve_user_id(opts->lead);
                if (!opts->status.empty())      input.status_id = opts->status;
                if (!opts->start_date.empty())  input.start_date = opts->start_date;
                if (!opts->target_date.empty()) input.target_date = opts->target_date;
                if (!opts->health.empty())      input.health = opts->health;

                if (!opts->priority.empty()) {
                    auto prio = priority_name_to_number(opts->priority);
                    if (prio.has_value()) {
                        input.priority = prio.value();
                    } else {
                        print_error("Invalid priority: " + opts->priority + ". Use: none, urgent, high, normal, low");
                        return;
                    }
                }

                auto project = projects_api::update_project(opts->id, input);
                print_success("Updated project: " + project.name);
                render_project_detail(project);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // projects delete <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = projects->add_subcommand("delete", "Delete a project");

        struct DeleteOpts {
            std::string id;
            bool yes = false;
        };
        auto opts = std::make_shared<DeleteOpts>();

        cmd->add_option("id", opts->id, "Project ID")->required();
        cmd->add_flag("--yes,-y", opts->yes, "Skip confirmation");

        cmd->callback([opts]() {
            try {
                auto project = projects_api::get_project(opts->id);

                if (!opts->yes) {
                    std::cerr << "Are you sure you want to delete project \""
                              << project.name << "\"? [y/N] ";
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (confirm != "y" && confirm != "Y" && confirm != "yes") {
                        print_warning("Aborted.");
                        return;
                    }
                }

                projects_api::delete_project(project.id);
                print_success("Deleted project: " + project.name);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // projects search <query>
    // -----------------------------------------------------------------------
    {
        auto* cmd = projects->add_subcommand("search", "Search projects");

        struct SearchOpts {
            std::string query;
            int limit = 20;
        };
        auto opts = std::make_shared<SearchOpts>();

        cmd->add_option("query", opts->query, "Search query text")->required();
        cmd->add_option("--limit,-n", opts->limit, "Maximum results")->default_val(20);

        cmd->callback([opts]() {
            try {
                auto connection = projects_api::search_projects(opts->query, opts->limit);
                if (get_output_format() == OutputFormat::Json) {
                    render_project_json(connection.nodes);
                } else {
                    render_project_table(connection.nodes);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // projects milestones (subcommand group)
    // -----------------------------------------------------------------------
    {
        auto* milestones_cmd = projects->add_subcommand("milestones", "Manage project milestones");
        milestones_cmd->require_subcommand(0);

        // Default behavior: list milestones for a project
        {
            auto project_id = std::make_shared<std::string>();
            milestones_cmd->add_option("project_id", *project_id, "Project ID")->required();

            milestones_cmd->callback([project_id, milestones_cmd]() {
                if (milestones_cmd->get_subcommands().empty()) {
                    try {
                        auto connection = projects_api::list_milestones(*project_id);
                        if (get_output_format() == OutputFormat::Json) {
                            json arr = json::array();
                            for (const auto& m : connection.nodes) {
                                json j;
                                j["id"] = m.id;
                                j["name"] = m.name;
                                j["status"] = m.status;
                                j["targetDate"] = m.target_date.value_or("");
                                j["progress"] = m.progress;
                                j["description"] = m.description.value_or("");
                                arr.push_back(j);
                            }
                            output_json(arr);
                        } else {
                            render_milestone_table(connection.nodes);
                        }
                    } catch (const LinError& e) {
                        print_error(format_error(e));
                    }
                }
            });
        }

        // milestones create
        {
            auto* cmd = milestones_cmd->add_subcommand("create", "Create a milestone");

            struct CreateOpts {
                std::string project_id;
                std::string name;
                std::string description;
                std::string target_date;
            };
            auto opts = std::make_shared<CreateOpts>();

            cmd->add_option("--project", opts->project_id, "Project ID")->required();
            cmd->add_option("--name,-n", opts->name, "Milestone name")->required();
            cmd->add_option("--description,-d", opts->description, "Milestone description");
            cmd->add_option("--target-date", opts->target_date, "Target date (YYYY-MM-DD)");

            cmd->callback([opts]() {
                try {
                    ProjectMilestoneCreateInput input;
                    input.project_id = opts->project_id;
                    input.name = opts->name;

                    if (!opts->description.empty()) input.description = opts->description;
                    if (!opts->target_date.empty()) input.target_date = opts->target_date;

                    auto milestone = projects_api::create_milestone(input);
                    print_success("Created milestone: " + milestone.name);

                    if (get_output_format() == OutputFormat::Json) {
                        json j;
                        j["id"] = milestone.id;
                        j["name"] = milestone.name;
                        j["status"] = milestone.status;
                        j["targetDate"] = milestone.target_date.value_or("");
                        j["progress"] = milestone.progress;
                        output_json(j);
                    }
                } catch (const LinError& e) {
                    print_error(format_error(e));
                }
            });
        }

        // milestones update <id>
        {
            auto* cmd = milestones_cmd->add_subcommand("update", "Update a milestone");

            struct UpdateOpts {
                std::string id;
                std::string name;
                std::string description;
                std::string target_date;
            };
            auto opts = std::make_shared<UpdateOpts>();

            cmd->add_option("id", opts->id, "Milestone ID")->required();
            cmd->add_option("--name,-n", opts->name, "New name");
            cmd->add_option("--description,-d", opts->description, "New description");
            cmd->add_option("--target-date", opts->target_date, "New target date (YYYY-MM-DD)");

            cmd->callback([opts]() {
                try {
                    ProjectMilestoneUpdateInput input;

                    if (!opts->name.empty())        input.name = opts->name;
                    if (!opts->description.empty()) input.description = opts->description;
                    if (!opts->target_date.empty()) input.target_date = opts->target_date;

                    auto milestone = projects_api::update_milestone(opts->id, input);
                    print_success("Updated milestone: " + milestone.name);

                    if (get_output_format() == OutputFormat::Json) {
                        json j;
                        j["id"] = milestone.id;
                        j["name"] = milestone.name;
                        j["status"] = milestone.status;
                        j["targetDate"] = milestone.target_date.value_or("");
                        j["progress"] = milestone.progress;
                        output_json(j);
                    }
                } catch (const LinError& e) {
                    print_error(format_error(e));
                }
            });
        }

        // milestones delete <id>
        {
            auto* cmd = milestones_cmd->add_subcommand("delete", "Delete a milestone");
            auto id = std::make_shared<std::string>();
            cmd->add_option("id", *id, "Milestone ID")->required();

            cmd->callback([id]() {
                try {
                    projects_api::delete_milestone(*id);
                    print_success("Deleted milestone " + *id);
                } catch (const LinError& e) {
                    print_error(format_error(e));
                }
            });
        }
    }

    // -----------------------------------------------------------------------
    // projects updates (subcommand group)
    // -----------------------------------------------------------------------
    {
        auto* updates_cmd = projects->add_subcommand("updates", "Manage project updates");
        updates_cmd->require_subcommand(0);

        // Default behavior: list updates for a project
        {
            auto project_id = std::make_shared<std::string>();
            updates_cmd->add_option("project_id", *project_id, "Project ID")->required();

            updates_cmd->callback([project_id, updates_cmd]() {
                if (updates_cmd->get_subcommands().empty()) {
                    try {
                        auto connection = projects_api::list_updates(*project_id);
                        if (get_output_format() == OutputFormat::Json) {
                            json arr = json::array();
                            for (const auto& u : connection.nodes) {
                                json j;
                                j["id"] = u.id;
                                j["body"] = u.body;
                                j["health"] = u.health.value_or("");
                                j["user"] = u.user_name.value_or("");
                                j["createdAt"] = u.created_at;
                                j["url"] = u.url;
                                arr.push_back(j);
                            }
                            output_json(arr);
                        } else {
                            render_update_table(connection.nodes);
                        }
                    } catch (const LinError& e) {
                        print_error(format_error(e));
                    }
                }
            });
        }

        // updates create <project_id>
        {
            auto* cmd = updates_cmd->add_subcommand("create", "Create a project update");

            struct CreateOpts {
                std::string project_id;
                std::string body;
                std::string health;
            };
            auto opts = std::make_shared<CreateOpts>();

            cmd->add_option("project_id", opts->project_id, "Project ID")->required();
            cmd->add_option("--body,-b", opts->body, "Update body text")->required();
            cmd->add_option("--health", opts->health, "Health status (onTrack, atRisk, offTrack)");

            cmd->callback([opts]() {
                try {
                    ProjectUpdateCreateInput input;
                    input.project_id = opts->project_id;
                    input.body = opts->body;

                    if (!opts->health.empty()) input.health = opts->health;

                    auto update = projects_api::create_update(input);
                    print_success("Created project update");

                    if (get_output_format() == OutputFormat::Json) {
                        json j;
                        j["id"] = update.id;
                        j["body"] = update.body;
                        j["health"] = update.health.value_or("");
                        j["user"] = update.user_name.value_or("");
                        j["createdAt"] = update.created_at;
                        j["url"] = update.url;
                        output_json(j);
                    }
                } catch (const LinError& e) {
                    print_error(format_error(e));
                }
            });
        }
    }
}
