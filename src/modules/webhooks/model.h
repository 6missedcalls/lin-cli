#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Webhook {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::optional<std::string> label;
    std::optional<std::string> url;
    bool enabled = true;
    std::optional<std::string> team_id;
    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Webhook& w) {
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return def;
    };

    auto safe_bool = [&](const char* key, bool def = true) -> bool {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<bool>();
        return def;
    };

    j.at("id").get_to(w.id);
    w.created_at = safe_str("createdAt");
    w.updated_at = safe_str("updatedAt");
    w.label = opt_str("label");
    w.url = opt_str("url");
    w.enabled = safe_bool("enabled", true);

    // Flatten nested: team
    if (j.contains("team") && !j["team"].is_null()) {
        const auto& t = j["team"];
        if (t.contains("id") && !t["id"].is_null()) {
            w.team_id = t["id"].get<std::string>();
        }
    }

    // Flatten nested: creator
    if (j.contains("creator") && !j["creator"].is_null()) {
        const auto& c = j["creator"];
        if (c.contains("id") && !c["id"].is_null()) {
            w.creator_id = c["id"].get<std::string>();
        }
        if (c.contains("displayName") && !c["displayName"].is_null()) {
            w.creator_name = c["displayName"].get<std::string>();
        }
    }
}
