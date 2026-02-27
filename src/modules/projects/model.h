#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Project {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::string slug_id;
    std::string url;
    int priority = 0;
    std::optional<std::string> priority_label;
    std::optional<std::string> status_id;
    std::optional<std::string> status_name;
    std::optional<std::string> status_type;  // backlog, planned, started, paused, completed, canceled
    std::optional<std::string> health;       // onTrack, atRisk, offTrack
    std::optional<std::string> health_updated_at;
    std::optional<std::string> lead_id;
    std::optional<std::string> lead_name;
    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;
    std::optional<std::string> start_date;
    std::optional<std::string> target_date;
    std::optional<std::string> started_at;
    std::optional<std::string> completed_at;
    std::optional<std::string> canceled_at;
    double progress = 0.0;
    double scope = 0.0;
    bool trashed = false;
};

struct ProjectMilestone {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> target_date;
    std::string status;  // unstarted, next, overdue, done
    double progress = 0.0;
    double sort_order = 0.0;
    std::optional<std::string> project_id;
    std::optional<std::string> project_name;
};

struct ProjectUpdate {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string body;
    std::optional<std::string> health;
    std::string url;
    std::string slug_id;
    std::optional<std::string> user_id;
    std::optional<std::string> user_name;
    std::optional<std::string> project_id;
    std::optional<std::string> project_name;
    std::optional<std::string> diff_markdown;
};

// --- from_json implementations (inline) ---

inline void from_json(const json& j, Project& p) {
    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return def;
    };
    auto safe_double = [&](const char* key, double def = 0.0) -> double {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<double>();
        return def;
    };
    auto safe_int = [&](const char* key, int def = 0) -> int {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<int>();
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

    j.at("id").get_to(p.id);
    p.created_at = safe_str("createdAt");
    p.updated_at = safe_str("updatedAt");
    j.at("name").get_to(p.name);
    p.slug_id = safe_str("slugId");
    p.url = safe_str("url");
    p.priority = safe_int("priority");
    p.progress = safe_double("progress");
    p.scope = safe_double("scope");
    p.trashed = safe_bool("trashed");

    p.description = opt_str("description");
    p.icon = opt_str("icon");
    p.color = opt_str("color");
    p.priority_label = opt_str("priorityLabel");
    p.health = opt_str("health");
    p.health_updated_at = opt_str("healthUpdatedAt");
    p.start_date = opt_str("startDate");
    p.target_date = opt_str("targetDate");
    p.started_at = opt_str("startedAt");
    p.completed_at = opt_str("completedAt");
    p.canceled_at = opt_str("canceledAt");

    // Flatten nested: status
    if (j.contains("status") && !j["status"].is_null()) {
        const auto& s = j["status"];
        p.status_id = s.value("id", "");
        p.status_name = s.value("name", "");
        p.status_type = s.value("type", "");
    }

    // Flatten nested: lead
    if (j.contains("lead") && !j["lead"].is_null()) {
        const auto& l = j["lead"];
        p.lead_id = l.value("id", "");
        p.lead_name = l.value("displayName", "");
    }

    // Flatten nested: creator
    if (j.contains("creator") && !j["creator"].is_null()) {
        const auto& c = j["creator"];
        p.creator_id = c.value("id", "");
        p.creator_name = c.value("displayName", "");
    }
}

inline void from_json(const json& j, ProjectMilestone& m) {
    auto safe_str = [&](const char* key, const std::string& def = "") -> std::string {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<std::string>();
        return def;
    };
    auto safe_double = [&](const char* key, double def = 0.0) -> double {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<double>();
        return def;
    };
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    j.at("id").get_to(m.id);
    m.created_at = safe_str("createdAt");
    m.updated_at = safe_str("updatedAt");
    j.at("name").get_to(m.name);
    m.status = safe_str("status");
    m.progress = safe_double("progress");
    m.sort_order = safe_double("sortOrder");

    m.description = opt_str("description");
    m.target_date = opt_str("targetDate");

    // Flatten nested: project
    if (j.contains("project") && !j["project"].is_null()) {
        const auto& pr = j["project"];
        m.project_id = pr.value("id", "");
        m.project_name = pr.value("name", "");
    }
}

inline void from_json(const json& j, ProjectUpdate& u) {
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

    j.at("id").get_to(u.id);
    u.created_at = safe_str("createdAt");
    u.updated_at = safe_str("updatedAt");
    u.body = safe_str("body");
    u.url = safe_str("url");
    u.slug_id = safe_str("slugId");

    u.health = opt_str("health");
    u.diff_markdown = opt_str("diffMarkdown");

    // Flatten nested: user
    if (j.contains("user") && !j["user"].is_null()) {
        const auto& usr = j["user"];
        u.user_id = usr.value("id", "");
        u.user_name = usr.value("displayName", "");
    }

    // Flatten nested: project
    if (j.contains("project") && !j["project"].is_null()) {
        const auto& pr = j["project"];
        u.project_id = pr.value("id", "");
        u.project_name = pr.value("name", "");
    }
}
