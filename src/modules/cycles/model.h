#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Cycle {
    std::string id;
    std::string created_at;
    std::string updated_at;
    double number = 0;
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::string starts_at;
    std::string ends_at;
    std::optional<std::string> completed_at;
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
    bool is_active = false;
    bool is_future = false;
    bool is_past = false;
    bool is_next = false;
    bool is_previous = false;
    double progress = 0.0;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Cycle& c) {
    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return def;
    };
    auto safe_double = [&](const char* key, double def = 0.0) -> double {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<double>();
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

    j.at("id").get_to(c.id);
    c.created_at = safe_str("createdAt");
    c.updated_at = safe_str("updatedAt");
    c.number = safe_double("number");
    c.starts_at = safe_str("startsAt");
    c.ends_at = safe_str("endsAt");
    c.progress = safe_double("progress");
    c.is_active = safe_bool("isActive");
    c.is_future = safe_bool("isFuture");
    c.is_past = safe_bool("isPast");
    c.is_next = safe_bool("isNext");
    c.is_previous = safe_bool("isPrevious");

    c.name = opt_str("name");
    c.description = opt_str("description");
    c.completed_at = opt_str("completedAt");

    // Flatten nested: team { id name }
    if (j.contains("team") && !j["team"].is_null()) {
        const auto& t = j["team"];
        c.team_id = t.value("id", "");
        c.team_name = t.value("name", "");
    }
}
