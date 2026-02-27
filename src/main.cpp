#include <iostream>
#include <string>

#include <CLI/CLI.hpp>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "modules/issues/api.h"
#include "modules/issues/commands.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CLI::App app{"lin — Linear CLI client"};
    app.require_subcommand(1);

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

    // lin me — show current user info
    auto* me_cmd = app.add_subcommand("me", "Show current user info");
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

    CLI11_PARSE(app, argc, argv);

    curl_global_cleanup();
    return 0;
}
