#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct User {
    std::string id;
    std::string created_at;
    std::string name;
    std::string display_name;
    std::string email;
    std::optional<std::string> avatar_url;
    std::optional<std::string> description;
    std::optional<std::string> timezone;
    std::optional<std::string> last_seen;
    std::optional<std::string> status_emoji;
    std::optional<std::string> status_label;
    bool active = true;
    bool admin = false;
    bool guest = false;
    bool is_me = false;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, User& u) {
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

    j.at("id").get_to(u.id);
    u.created_at = safe_str("createdAt");
    u.name = safe_str("name");
    u.display_name = safe_str("displayName");
    u.email = safe_str("email");

    u.avatar_url = opt_str("avatarUrl");
    u.description = opt_str("description");
    u.timezone = opt_str("timezone");
    u.last_seen = opt_str("lastSeen");
    u.status_emoji = opt_str("statusEmoji");
    u.status_label = opt_str("statusLabel");

    u.active = safe_bool("active", true);
    u.admin = safe_bool("admin", false);
    u.guest = safe_bool("guest", false);
    u.is_me = safe_bool("isMe", false);
}
