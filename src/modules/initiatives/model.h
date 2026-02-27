#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Initiative {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::string url;
    std::optional<std::string> status;       // Planned, Active, Completed
    std::optional<std::string> health;       // onTrack, atRisk, offTrack
    std::optional<std::string> target_date;
    std::optional<std::string> owner_id;
    std::optional<std::string> owner_name;
    std::optional<std::string> started_at;
    std::optional<std::string> completed_at;
    bool trashed = false;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Initiative& i) {
    // Null-safe required fields
    j.at("id").get_to(i.id);
    j.at("name").get_to(i.name);

    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return def;
    };
    auto safe_bool = [&](const char* key, bool def = false) -> bool {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<bool>();
        return def;
    };
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return std::nullopt;
    };

    i.created_at = safe_str("createdAt");
    i.updated_at = safe_str("updatedAt");
    i.slug_id    = safe_str("slugId");
    i.url        = safe_str("url");
    i.trashed    = safe_bool("trashed");

    i.description  = opt_str("description");
    i.icon         = opt_str("icon");
    i.color        = opt_str("color");
    i.status       = opt_str("status");
    i.health       = opt_str("health");
    i.target_date  = opt_str("targetDate");
    i.started_at   = opt_str("startedAt");
    i.completed_at = opt_str("completedAt");

    // Flatten nested: owner { id displayName }
    if (j.contains("owner") && !j["owner"].is_null()) {
        const auto& o = j["owner"];
        i.owner_id   = o.value("id", "");
        i.owner_name = o.value("displayName", "");
    }
}
