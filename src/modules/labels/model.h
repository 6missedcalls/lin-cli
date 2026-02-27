#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct IssueLabel {
    std::string id;
    std::string created_at;
    std::string name;
    std::optional<std::string> description;
    std::string color;
    bool is_group = false;
    std::optional<std::string> parent_id;
    std::optional<std::string> parent_name;
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
};

inline void from_json(const json& j, IssueLabel& l) {
    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
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

    j.at("id").get_to(l.id);
    l.name = safe_str("name");
    l.color = safe_str("color");
    l.created_at = safe_str("createdAt");
    l.is_group = safe_bool("isGroup");
    l.description = opt_str("description");

    // Flatten nested: parent { id name }
    if (j.contains("parent") && !j["parent"].is_null()) {
        const auto& p = j["parent"];
        l.parent_id = p.value("id", "");
        l.parent_name = p.value("name", "");
    }

    // Flatten nested: team { id name }
    if (j.contains("team") && !j["team"].is_null()) {
        const auto& t = j["team"];
        l.team_id = t.value("id", "");
        l.team_name = t.value("name", "");
    }
}
