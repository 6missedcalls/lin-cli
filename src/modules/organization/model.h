#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Organization {
    std::string id;
    std::string created_at;
    std::string name;
    std::string url_key;
    std::optional<std::string> logo_url;
    int user_count = 0;
    int created_issue_count = 0;
    std::optional<std::string> git_branch_format;
    bool git_linkback_messages_enabled = false;
    bool saml_enabled = false;
    bool scim_enabled = false;
    std::optional<std::string> trial_ends_at;
    std::optional<std::string> subscription_type;
};

struct RateLimitStatus {
    int requests_remaining = 0;
    int requests_limit = 0;
    double reset_at = 0;  // Unix timestamp
};

// --- from_json implementations (inline) ---

inline void from_json(const json& j, Organization& o) {
    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return def;
    };
    auto safe_int = [&](const char* key, int def = 0) -> int {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<int>();
        return def;
    };
    auto safe_bool = [&](const char* key, bool def = false) -> bool {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<bool>();
        return def;
    };
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    j.at("id").get_to(o.id);
    o.name = safe_str("name");
    o.url_key = safe_str("urlKey");
    o.created_at = safe_str("createdAt");
    o.user_count = safe_int("userCount");
    o.created_issue_count = safe_int("createdIssueCount");
    o.git_linkback_messages_enabled = safe_bool("gitLinkbackMessagesEnabled");
    o.saml_enabled = safe_bool("samlEnabled");
    o.scim_enabled = safe_bool("scimEnabled");

    o.logo_url = opt_str("logoUrl");
    o.git_branch_format = opt_str("gitBranchFormat");
    o.trial_ends_at = opt_str("trialEndsAt");

    // Flatten nested subscription
    if (j.contains("subscription") && !j["subscription"].is_null()) {
        const auto& sub = j["subscription"];
        if (sub.contains("type") && !sub["type"].is_null()) {
            o.subscription_type = sub["type"].get<std::string>();
        }
    }
}

inline void from_json(const json& j, RateLimitStatus& r) {
    auto safe_int = [&](const char* key, int def = 0) -> int {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<int>();
        return def;
    };
    auto safe_double = [&](const char* key, double def = 0.0) -> double {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<double>();
        return def;
    };

    r.requests_remaining = safe_int("requestsRemaining");
    r.requests_limit = safe_int("requestsLimit");
    r.reset_at = safe_double("resetAt");
}
