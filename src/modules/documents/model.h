#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Document {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string title;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::string url;
    std::optional<std::string> content;  // Markdown
    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;
    std::optional<std::string> project_id;
    std::optional<std::string> project_name;
    std::optional<std::string> initiative_id;
    bool trashed = false;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Document& d) {
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

    j.at("id").get_to(d.id);
    j.at("title").get_to(d.title);
    d.created_at = safe_str("createdAt");
    d.updated_at = safe_str("updatedAt");
    d.slug_id = safe_str("slugId");
    d.url = safe_str("url");
    d.trashed = safe_bool("trashed");

    d.icon = opt_str("icon");
    d.color = opt_str("color");
    d.content = opt_str("content");

    // Flatten nested: creator { id displayName }
    if (j.contains("creator") && !j["creator"].is_null()) {
        const auto& c = j["creator"];
        d.creator_id = c.value("id", "");
        d.creator_name = c.value("displayName", "");
    }

    // Flatten nested: project { id name }
    if (j.contains("project") && !j["project"].is_null()) {
        const auto& p = j["project"];
        d.project_id = p.value("id", "");
        d.project_name = p.value("name", "");
    }

    // Flatten nested: initiative { id }
    if (j.contains("initiative") && !j["initiative"].is_null()) {
        d.initiative_id = j["initiative"].value("id", "");
    }
}
