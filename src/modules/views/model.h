#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct CustomView {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::optional<std::string> model_name;
    bool shared = false;
    std::optional<json> filter_data;
    std::optional<std::string> owner_id;
    std::optional<std::string> owner_name;
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, CustomView& v) {
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    j.at("id").get_to(v.id);
    v.created_at = j.contains("createdAt") && !j["createdAt"].is_null()
        ? j["createdAt"].get<std::string>() : "";
    v.updated_at = j.contains("updatedAt") && !j["updatedAt"].is_null()
        ? j["updatedAt"].get<std::string>() : "";
    v.name = j.contains("name") && !j["name"].is_null()
        ? j["name"].get<std::string>() : "";
    v.slug_id = j.contains("slugId") && !j["slugId"].is_null()
        ? j["slugId"].get<std::string>() : "";
    v.shared = j.contains("shared") && !j["shared"].is_null()
        ? j["shared"].get<bool>() : false;

    v.description = opt_str("description");
    v.icon = opt_str("icon");
    v.color = opt_str("color");
    v.model_name = opt_str("modelName");

    // Store raw filterData as json blob
    if (j.contains("filterData") && !j["filterData"].is_null()) {
        v.filter_data = j["filterData"];
    }

    // Flatten nested: owner { id displayName }
    if (j.contains("owner") && !j["owner"].is_null()) {
        const auto& o = j["owner"];
        if (o.contains("id") && !o["id"].is_null()) {
            v.owner_id = o["id"].get<std::string>();
        }
        if (o.contains("displayName") && !o["displayName"].is_null()) {
            v.owner_name = o["displayName"].get<std::string>();
        }
    }

    // Flatten nested: team { id name }
    if (j.contains("team") && !j["team"].is_null()) {
        const auto& t = j["team"];
        if (t.contains("id") && !t["id"].is_null()) {
            v.team_id = t["id"].get<std::string>();
        }
        if (t.contains("name") && !t["name"].is_null()) {
            v.team_name = t["name"].get<std::string>();
        }
    }
}
