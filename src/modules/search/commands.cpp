#include "modules/search/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "modules/search/api.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

// Print a bold section header separator
void print_section_header(const std::string& title) {
    std::cout << "\n" << color::bold("=== " + title + " ===") << "\n";
}

// Render a table of issue nodes from raw JSON
void render_issues_section(const json& issues_data) {
    if (!issues_data.contains("nodes") || !issues_data["nodes"].is_array()) {
        return;
    }

    const auto& nodes = issues_data["nodes"];
    if (nodes.empty()) {
        std::cout << color::dim("  (no issues found)") << "\n";
        return;
    }

    TableRenderer table({
        {"IDENTIFIER", 6,  12, false},
        {"PRIORITY",   4,  10, false},
        {"TITLE",      8,  60, false},
        {"STATE",      4,  16, false},
        {"ASSIGNEE",   4,  20, false},
        {"TEAM",       3,  10, false}
    });

    for (const auto& node : nodes) {
        auto identifier    = node.value("identifier", "");
        auto title         = node.value("title", "");
        auto priority_val  = node.contains("priority") && !node["priority"].is_null()
                                 ? static_cast<int>(node["priority"].get<double>()) : 0;
        auto priority_lbl  = node.value("priorityLabel", "");
        std::string state_name;
        std::string state_type;
        std::string assignee_name;
        std::string team_key;

        if (node.contains("state") && !node["state"].is_null()) {
            state_name = node["state"].value("name", "");
            state_type = node["state"].value("type", "");
        }
        if (node.contains("assignee") && !node["assignee"].is_null()) {
            assignee_name = node["assignee"].value("displayName", "");
        }
        if (node.contains("team") && !node["team"].is_null()) {
            team_key = node["team"].value("key", "");
        }

        std::string priority_str = color::priority(priority_val, priority_lbl);
        std::string state_str    = state_type.empty()
                                       ? state_name
                                       : color::state_type(state_type, state_name);
        std::string assignee_str = assignee_name.empty() ? "Unassigned" : assignee_name;

        table.add_row({identifier, priority_str, title, state_str, assignee_str, team_key});
    }

    table.render(std::cout);
}

// Render a table of project nodes from raw JSON
void render_projects_section(const json& projects_data) {
    if (!projects_data.contains("nodes") || !projects_data["nodes"].is_array()) {
        return;
    }

    const auto& nodes = projects_data["nodes"];
    if (nodes.empty()) {
        std::cout << color::dim("  (no projects found)") << "\n";
        return;
    }

    TableRenderer table({
        {"NAME",     8, 40, false},
        {"STATUS",   4, 16, false},
        {"HEALTH",   4, 10, false},
        {"PROGRESS", 4,  8, false},
        {"LEAD",     4, 20, false}
    });

    for (const auto& node : nodes) {
        auto name     = node.value("name", "");
        auto health   = node.value("health", "");
        auto progress = node.contains("progress") && !node["progress"].is_null()
                            ? std::to_string(static_cast<int>(node["progress"].get<double>() * 100)) + "%"
                            : "";
        std::string status_name;
        std::string status_type;
        std::string lead_name;

        if (node.contains("status") && !node["status"].is_null()) {
            status_name = node["status"].value("name", "");
            status_type = node["status"].value("type", "");
        }
        if (node.contains("lead") && !node["lead"].is_null()) {
            lead_name = node["lead"].value("displayName", "");
        }

        std::string status_str = status_type.empty()
                                     ? status_name
                                     : color::state_type(status_type, status_name);
        std::string health_str;
        if (health == "onTrack") {
            health_str = color::green("On Track");
        } else if (health == "atRisk") {
            health_str = color::yellow("At Risk");
        } else if (health == "offTrack") {
            health_str = color::red("Off Track");
        } else {
            health_str = health;
        }

        table.add_row({name, status_str, health_str, progress, lead_name});
    }

    table.render(std::cout);
}

// Render a table of document nodes from raw JSON
void render_documents_section(const json& docs_data) {
    if (!docs_data.contains("nodes") || !docs_data["nodes"].is_array()) {
        return;
    }

    const auto& nodes = docs_data["nodes"];
    if (nodes.empty()) {
        std::cout << color::dim("  (no documents found)") << "\n";
        return;
    }

    TableRenderer table({
        {"TITLE",   10, 50, false},
        {"PROJECT",  4, 30, false},
        {"CREATOR",  4, 20, false},
        {"UPDATED",  4, 24, false}
    });

    for (const auto& node : nodes) {
        auto title      = node.value("title", "");
        auto updated_at = node.value("updatedAt", "");
        std::string project_name;
        std::string creator_name;

        if (node.contains("project") && !node["project"].is_null()) {
            project_name = node["project"].value("name", "");
        }
        if (node.contains("creator") && !node["creator"].is_null()) {
            creator_name = node["creator"].value("displayName", "");
        }

        table.add_row({title, project_name, creator_name, updated_at});
    }

    table.render(std::cout);
}

// Render search results as JSON — grouped by type
void render_all_json(const json& data) {
    json result = json::object();

    if (data.contains("searchIssues")) {
        result["issues"] = data["searchIssues"].value("nodes", json::array());
    }
    if (data.contains("projectSearch")) {
        result["projects"] = data["projectSearch"].value("nodes", json::array());
    }
    if (data.contains("searchDocuments")) {
        result["documents"] = data["searchDocuments"].value("nodes", json::array());
    }

    output_json(result);
}

// Render typed search results as JSON (single array of nodes)
void render_typed_json(const json& data, const std::string& key) {
    if (data.contains(key) && data[key].contains("nodes")) {
        output_json(data[key]["nodes"]);
    } else {
        output_json(json::array());
    }
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void search_commands::register_commands(CLI::App& app) {
    auto* search = app.add_subcommand("search", "Search across issues, projects, and documents");

    struct SearchOpts {
        std::string query;
        std::string type;
        std::string team;
        int limit = 20;
    };
    auto opts = std::make_shared<SearchOpts>();

    search->add_option("query", opts->query, "Search query text")->required();
    search->add_option("--type", opts->type,
        "Restrict search to a single type: issues, projects, docs");
    search->add_option("--team", opts->team,
        "Filter by team key (only applies when --type issues)");
    search->add_option("--limit,-n", opts->limit,
        "Maximum results per type")->default_val(20);

    search->callback([opts]() {
        try {
            if (opts->type == "issues") {
                std::optional<std::string> team_opt =
                    opts->team.empty() ? std::nullopt : std::make_optional(opts->team);

                auto data = search_api::search_issues(opts->query, team_opt, opts->limit);

                if (get_output_format() == OutputFormat::Json) {
                    render_typed_json(data, "searchIssues");
                    return;
                }

                print_section_header("Issues");
                if (data.contains("searchIssues")) {
                    render_issues_section(data["searchIssues"]);
                } else {
                    std::cout << color::dim("  (no issues found)") << "\n";
                }

            } else if (opts->type == "projects") {
                auto data = search_api::search_projects(opts->query, opts->limit);

                if (get_output_format() == OutputFormat::Json) {
                    render_typed_json(data, "projectSearch");
                    return;
                }

                print_section_header("Projects");
                if (data.contains("projectSearch")) {
                    render_projects_section(data["projectSearch"]);
                } else {
                    std::cout << color::dim("  (no projects found)") << "\n";
                }

            } else if (opts->type == "docs") {
                auto data = search_api::search_documents(opts->query, opts->limit);

                if (get_output_format() == OutputFormat::Json) {
                    render_typed_json(data, "searchDocuments");
                    return;
                }

                print_section_header("Documents");
                if (data.contains("searchDocuments")) {
                    render_documents_section(data["searchDocuments"]);
                } else {
                    std::cout << color::dim("  (no documents found)") << "\n";
                }

            } else {
                // No --type specified: cross-type semantic search
                if (!opts->team.empty()) {
                    print_warning("--team filter is only applied when using --type issues");
                }

                auto data = search_api::search_all(opts->query, opts->limit);

                if (get_output_format() == OutputFormat::Json) {
                    render_all_json(data);
                    return;
                }

                bool any_results = false;

                if (data.contains("searchIssues")) {
                    const auto& issues = data["searchIssues"];
                    if (issues.contains("nodes") && !issues["nodes"].empty()) {
                        any_results = true;
                    }
                    print_section_header("Issues");
                    render_issues_section(issues);
                }

                if (data.contains("searchDocuments")) {
                    const auto& docs = data["searchDocuments"];
                    if (docs.contains("nodes") && !docs["nodes"].empty()) {
                        any_results = true;
                    }
                    print_section_header("Documents");
                    render_documents_section(docs);
                }

                if (!any_results) {
                    print_warning("No results found for: " + opts->query);
                }
            }

            std::cout << "\n";

        } catch (const LinError& e) {
            print_error(format_error(e));
        }
    });
}
