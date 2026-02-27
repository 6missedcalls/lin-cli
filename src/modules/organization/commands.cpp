#include "modules/organization/commands.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/color.h"
#include "core/error.h"
#include "core/output.h"
#include "modules/organization/api.h"
#include "modules/organization/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

std::string format_unix_timestamp(double ts) {
    if (ts <= 0) return "";
    auto t = static_cast<std::time_t>(ts);
    std::tm* tm_info = std::gmtime(&t);
    if (!tm_info) return "";
    std::ostringstream oss;
    oss << std::put_time(tm_info, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}

void render_organization_detail(const Organization& org) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = org.id;
        j["name"] = org.name;
        j["urlKey"] = org.url_key;
        j["logoUrl"] = org.logo_url.has_value() ? json(org.logo_url.value()) : json(nullptr);
        j["userCount"] = org.user_count;
        j["createdIssueCount"] = org.created_issue_count;
        j["gitBranchFormat"] = org.git_branch_format.has_value() ? json(org.git_branch_format.value()) : json(nullptr);
        j["gitLinkbackMessagesEnabled"] = org.git_linkback_messages_enabled;
        j["samlEnabled"] = org.saml_enabled;
        j["scimEnabled"] = org.scim_enabled;
        j["trialEndsAt"] = org.trial_ends_at.has_value() ? json(org.trial_ends_at.value()) : json(nullptr);
        j["subscriptionType"] = org.subscription_type.has_value() ? json(org.subscription_type.value()) : json(nullptr);
        j["createdAt"] = org.created_at;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(org.name);

    detail.add_field("URL Key", org.url_key);
    detail.add_field("Users", std::to_string(org.user_count));
    detail.add_field("Issues Created", std::to_string(org.created_issue_count));

    if (org.subscription_type.has_value()) {
        detail.add_field("Plan", org.subscription_type.value());
    }
    if (org.trial_ends_at.has_value()) {
        detail.add_field("Trial Ends", org.trial_ends_at.value());
    }
    if (org.git_branch_format.has_value()) {
        detail.add_field("Branch Format", org.git_branch_format.value());
    }

    detail.add_field("Git Linkback", org.git_linkback_messages_enabled ? "enabled" : "disabled");
    detail.add_field("SAML SSO", org.saml_enabled ? "enabled" : "disabled");
    detail.add_field("SCIM", org.scim_enabled ? "enabled" : "disabled");

    if (org.logo_url.has_value()) {
        detail.add_field("Logo", org.logo_url.value());
    }

    detail.add_field("ID", org.id);
    detail.add_field("Created", org.created_at);

    detail.render(std::cout);
}

void render_rate_limit_detail(const RateLimitStatus& status) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["requestsRemaining"] = status.requests_remaining;
        j["requestsLimit"] = status.requests_limit;
        j["resetAt"] = status.reset_at;
        j["resetAtFormatted"] = format_unix_timestamp(status.reset_at);
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section("API Rate Limit");

    std::string remaining_str = std::to_string(status.requests_remaining)
        + " / " + std::to_string(status.requests_limit);

    // Color the remaining count: red if low, yellow if moderate, green if healthy
    std::string remaining_colored;
    if (status.requests_limit > 0) {
        double ratio = static_cast<double>(status.requests_remaining) / status.requests_limit;
        if (ratio < 0.1) {
            remaining_colored = color::red(remaining_str);
        } else if (ratio < 0.3) {
            remaining_colored = color::yellow(remaining_str);
        } else {
            remaining_colored = color::green(remaining_str);
        }
    } else {
        remaining_colored = remaining_str;
    }

    detail.add_field("Remaining", remaining_colored);

    std::string reset_str = format_unix_timestamp(status.reset_at);
    if (!reset_str.empty()) {
        detail.add_field("Resets At", reset_str);
    }

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void organization_commands::register_commands(CLI::App& app) {
    // -------------------------------------------------------------------------
    // lin org — show organization detail
    // -------------------------------------------------------------------------
    {
        auto* cmd = app.add_subcommand("org", "Show organization info");

        cmd->callback([]() {
            try {
                auto org = organization_api::get_organization();
                render_organization_detail(org);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -------------------------------------------------------------------------
    // lin rate-limit — show API rate limit status
    // -------------------------------------------------------------------------
    {
        auto* cmd = app.add_subcommand("rate-limit", "Show API rate limit status");

        cmd->callback([]() {
            try {
                auto status = organization_api::get_rate_limit();
                render_rate_limit_detail(status);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
