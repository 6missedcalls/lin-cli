#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Comment {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string body;                              // Markdown content
    std::optional<std::string> edited_at;
    std::optional<std::string> resolved_at;
    std::string url;
    std::optional<std::string> user_id;
    std::optional<std::string> user_name;
    std::optional<std::string> parent_id;
    std::optional<std::string> issue_id;
    std::optional<std::string> project_update_id;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Comment& c) {
    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return def;
    };

    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    j.at("id").get_to(c.id);
    c.body = safe_str("body");
    c.url = safe_str("url");
    c.created_at = safe_str("createdAt");
    c.updated_at = safe_str("updatedAt");

    c.edited_at = opt_str("editedAt");
    c.resolved_at = opt_str("resolvedAt");
    c.project_update_id = opt_str("projectUpdateId");

    // Flatten nested: user { id displayName }
    if (j.contains("user") && !j["user"].is_null()) {
        const auto& u = j["user"];
        c.user_id = u.value("id", "");
        c.user_name = u.value("displayName", "");
    }

    // Flatten nested: parent { id }
    if (j.contains("parent") && !j["parent"].is_null()) {
        c.parent_id = j["parent"].value("id", "");
    }

    // Flatten nested: issue { id }
    if (j.contains("issue") && !j["issue"].is_null()) {
        c.issue_id = j["issue"].value("id", "");
    }
}
