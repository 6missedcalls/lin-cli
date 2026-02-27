#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Integration {
    std::string id;
    std::string created_at;
    std::string service;

    std::optional<std::string> team_id;
    std::optional<std::string> team_name;

    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Integration& i) {
    j.at("id").get_to(i.id);
    i.service = j.value("service", "");
    i.created_at = j.value("createdAt", "");

    // Flatten nested: team
    if (j.contains("team") && !j["team"].is_null()) {
        const auto& t = j["team"];
        i.team_id = t.value("id", "");
        i.team_name = t.value("name", "");
    }

    // Flatten nested: creator
    if (j.contains("creator") && !j["creator"].is_null()) {
        const auto& c = j["creator"];
        i.creator_id = c.value("id", "");
        i.creator_name = c.value("displayName", "");
    }
}
