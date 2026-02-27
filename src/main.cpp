#include <iostream>
#include <string>

#include <CLI/CLI.hpp>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "core/version.h"
#include "modules/issues/api.h"
#include "modules/issues/commands.h"
#include "modules/teams/commands.h"
#include "modules/labels/commands.h"
#include "modules/users/commands.h"
#include "modules/projects/commands.h"
#include "modules/cycles/commands.h"
#include "modules/comments/commands.h"
#include "modules/documents/commands.h"
#include "modules/views/commands.h"
#include "modules/notifications/commands.h"
#include "modules/favorites/commands.h"
#include "modules/initiatives/commands.h"
#include "modules/search/commands.h"
#include "modules/webhooks/commands.h"
#include "modules/organization/commands.h"
#include "modules/integrations/commands.h"
#include "modules/config/commands.h"
#include "modules/cache/commands.h"
#include "tui/app.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
    // Bare `lin` with no arguments — show splash screen
    if (argc == 1) {
        std::cout << R"(
  ██╗     ██╗███╗   ██╗
  ██║     ██║████╗  ██║
  ██║     ██║██╔██╗ ██║
  ██║     ██║██║╚██╗██║
  ███████╗██║██║ ╚████║
  ╚══════╝╚═╝╚═╝  ╚═══╝

  fast, terminal-native Linear client
  built by 6missedcalls

  Run 'lin --help' for available commands
  Run 'lin <command> --help' for command details
)" << std::endl;
        return 0;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);

    CLI::App app{"lin \xe2\x80\x94 fast, terminal-native Linear client"};
    app.set_version_flag("--version", std::string("lin ") + LIN_VERSION);
    app.require_subcommand(1);
    app.fallthrough();
    app.get_formatter()->column_width(32);

    // Global flags
    bool json_output = false;
    bool csv_output = false;
    bool no_color = false;
    bool verbose = false;
    std::string global_team;

    app.add_flag("--json", json_output, "Output raw JSON");
    app.add_flag("--csv", csv_output, "Output CSV");
    app.add_flag("--no-color", no_color, "Disable colors");
    app.add_flag("--verbose", verbose, "Show debug info");
    app.add_option("--team", global_team, "Override default team");

    // Apply global flags before any subcommand callback runs
    app.parse_complete_callback([&]() {
        if (json_output) set_output_format(OutputFormat::Json);
        if (csv_output) set_output_format(OutputFormat::Csv);
        if (no_color) color::set_enabled(false);
    });

    // Register module commands
    issues_commands::register_commands(app);
    teams_commands::register_commands(app);
    labels_commands::register_commands(app);
    users_commands::register_commands(app);
    projects_commands::register_commands(app);
    cycles_commands::register_commands(app);
    comments_commands::register_commands(app);
    documents_commands::register_commands(app);
    views_commands::register_commands(app);
    notifications_commands::register_commands(app);
    favorites_commands::register_commands(app);
    initiatives_commands::register_commands(app);
    search_commands::register_commands(app);
    webhooks_commands::register_commands(app);
    organization_commands::register_commands(app);
    integrations_commands::register_commands(app);
    config_commands::register_commands(app);
    cache_commands::register_commands(app);

    // lin tui — launch interactive TUI
    auto* tui_cmd = app.add_subcommand("tui", "Launch interactive kanban board");
    std::string tui_team;
    tui_cmd->add_option("--team", tui_team, "Start with team view");
    tui_cmd->callback([&]() {
        curl_global_cleanup();
        curl_global_init(CURL_GLOBAL_DEFAULT);
        tui::run(tui_team.empty() ? global_team : tui_team);
    });

    // lin me — show current user info
    auto* me_cmd = app.add_subcommand("me", "Show your profile and assigned work");
    me_cmd->callback([&]() {
        try {
            auto viewer = issues_api::get_viewer();

            if (get_output_format() == OutputFormat::Json) {
                json j;
                j["id"] = viewer.id;
                j["name"] = viewer.name;
                j["email"] = viewer.email;
                j["displayName"] = viewer.display_name;
                output_json(j);
            } else {
                DetailRenderer detail;
                detail.add_section("Current User");
                detail.add_field("Name", viewer.display_name);
                detail.add_field("Email", viewer.email);
                detail.add_field("ID", viewer.id);
                detail.render(std::cout);
            }
        } catch (const LinError& e) {
            print_error(format_error(e));
        }
    });

    // --- Group subcommands (Cobra-style) ---
    app.get_subcommand("issues")->group("Work Items");
    app.get_subcommand("projects")->group("Work Items");
    app.get_subcommand("cycles")->group("Work Items");
    app.get_subcommand("search")->group("Work Items");

    app.get_subcommand("teams")->group("Workspace");
    app.get_subcommand("labels")->group("Workspace");
    app.get_subcommand("users")->group("Workspace");
    app.get_subcommand("views")->group("Workspace");
    app.get_subcommand("initiatives")->group("Workspace");

    app.get_subcommand("comments")->group("Collaborate");
    app.get_subcommand("docs")->group("Collaborate");
    app.get_subcommand("notifications")->group("Collaborate");
    app.get_subcommand("favorites")->group("Collaborate");
    app.get_subcommand("webhooks")->group("Collaborate");

    app.get_subcommand("org")->group("Admin");
    app.get_subcommand("rate-limit")->group("Admin");
    app.get_subcommand("integrations")->group("Admin");
    app.get_subcommand("config")->group("Admin");
    app.get_subcommand("cache")->group("Admin");

    me_cmd->group("Interactive");
    tui_cmd->group("Interactive");

    try {
        app.parse(argc, argv);
    } catch (const CLI::RequiredError& e) {
        // When a subcommand group is invoked without a subcommand (e.g. `lin issues`),
        // show help for that group instead of erroring.
        // Find the parsed subcommand that triggered the error.
        for (auto* sub : app.get_subcommands()) {
            if (sub->parsed()) {
                std::cout << sub->help() << std::endl;
                curl_global_cleanup();
                return 0;
            }
        }
        // Fallback: show top-level help
        std::cout << app.help() << std::endl;
        curl_global_cleanup();
        return 0;
    } catch (const CLI::ParseError& e) {
        int ret = app.exit(e);
        curl_global_cleanup();
        return ret;
    }

    curl_global_cleanup();
    return 0;
}
