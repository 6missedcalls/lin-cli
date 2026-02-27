#include "modules/integrations/commands.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "core/output.h"
#include "modules/integrations/api.h"
#include "modules/integrations/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

void render_integration_table(const std::vector<Integration>& integrations) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"SERVICE", "TEAM", "CREATOR", "DATE"});
        for (const auto& intg : integrations) {
            output_csv_row({
                intg.service,
                intg.team_name.value_or(""),
                intg.creator_name.value_or(""),
                intg.created_at
            });
        }
        return;
    }

    TableRenderer table({
        {"SERVICE", 4, 24, false},
        {"TEAM",    4, 24, false},
        {"CREATOR", 4, 24, false},
        {"DATE",    4, 28, false}
    });

    for (const auto& intg : integrations) {
        table.add_row({
            intg.service,
            intg.team_name.value_or(""),
            intg.creator_name.value_or(""),
            intg.created_at
        });
    }

    if (table.empty()) {
        print_warning("No integrations found.");
        return;
    }

    table.render(std::cout);
}

void render_integration_json(const std::vector<Integration>& integrations) {
    json arr = json::array();
    for (const auto& intg : integrations) {
        json j;
        j["id"] = intg.id;
        j["service"] = intg.service;
        j["createdAt"] = intg.created_at;
        j["teamId"] = intg.team_id.value_or("");
        j["teamName"] = intg.team_name.value_or("");
        j["creatorId"] = intg.creator_id.value_or("");
        j["creatorName"] = intg.creator_name.value_or("");
        arr.push_back(j);
    }
    output_json(arr);
}

void render_integration_detail(const Integration& intg) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = intg.id;
        j["service"] = intg.service;
        j["createdAt"] = intg.created_at;
        j["teamId"] = intg.team_id.value_or("");
        j["teamName"] = intg.team_name.value_or("");
        j["creatorId"] = intg.creator_id.value_or("");
        j["creatorName"] = intg.creator_name.value_or("");
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(intg.service);

    if (intg.team_name.has_value()) {
        detail.add_field("Team", intg.team_name.value());
    }
    if (intg.creator_name.has_value()) {
        detail.add_field("Creator", intg.creator_name.value());
    }

    detail.add_field("Created", intg.created_at);
    detail.add_field("ID", intg.id);

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void integrations_commands::register_commands(CLI::App& app) {
    auto* integrations = app.add_subcommand("integrations", "List active integrations");
    integrations->require_subcommand(1);

    // -----------------------------------------------------------------------
    // integrations list
    // -----------------------------------------------------------------------
    {
        auto* cmd = integrations->add_subcommand("list", "List integrations");

        struct ListOpts {
            int limit = 50;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--limit,-n", opts->limit, "Maximum number of integrations to return")->default_val(50);

        cmd->callback([opts]() {
            try {
                auto connection = integrations_api::list_integrations(opts->limit, std::nullopt);

                if (get_output_format() == OutputFormat::Json) {
                    render_integration_json(connection.nodes);
                } else {
                    render_integration_table(connection.nodes);
                    if (connection.page_info.has_next_page) {
                        print_warning("More integrations available. Use --limit to increase results.");
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // integrations show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = integrations->add_subcommand("show", "Show integration details");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Integration ID")->required();

        cmd->callback([id]() {
            try {
                auto intg = integrations_api::get_integration(*id);
                render_integration_detail(intg);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
