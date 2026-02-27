#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Notification {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string type;
    std::optional<std::string> read_at;
    std::optional<std::string> snoozed_until_at;
    std::optional<std::string> archived_at;

    // Flattened from actor { id name }
    std::optional<std::string> actor_id;
    std::optional<std::string> actor_name;

    std::optional<std::string> title;
    std::optional<std::string> subtitle;
    std::optional<std::string> url;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Notification& n) {
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    j.at("id").get_to(n.id);
    n.type = j.value("type", "");
    n.created_at = j.value("createdAt", "");
    n.updated_at = j.value("updatedAt", "");

    n.read_at = opt_str("readAt");
    n.snoozed_until_at = opt_str("snoozedUntilAt");
    n.archived_at = opt_str("archivedAt");

    // Inline fields (some notification subtypes expose these directly)
    n.title = opt_str("title");
    n.subtitle = opt_str("subtitle");
    n.url = opt_str("url");

    // Flatten nested: actor { id name }
    if (j.contains("actor") && !j["actor"].is_null()) {
        const auto& a = j["actor"];
        if (a.contains("id") && !a["id"].is_null()) {
            n.actor_id = a["id"].get<std::string>();
        }
        if (a.contains("name") && !a["name"].is_null()) {
            n.actor_name = a["name"].get<std::string>();
        }
    }
}
