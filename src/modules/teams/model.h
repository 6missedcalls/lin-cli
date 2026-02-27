#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Team {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::string name;
    std::string key;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::optional<std::string> timezone;
    std::string display_name;
    bool cycles_enabled = false;
    bool triage_enabled = false;
    bool private_team = false;
    int issue_count = 0;
    double cycle_duration = 0;
    double cycle_cooldown_time = 0;
    double cycle_start_day = 0;
    std::string issue_estimation_type;
};

struct WorkflowState {
    std::string id;
    std::string created_at;
    std::string name;
    std::string color;
    std::optional<std::string> description;
    double position = 0.0;
    std::string type;  // triage, backlog, unstarted, started, completed, canceled
    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
};

// --- from_json implementations (inline) ---

inline void from_json(const json& j, Team& t) {
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
    auto safe_int = [&](const char* key, int def = 0) -> int {
        if (j.contains(key) && !j[key].is_null()) return j[key].get<int>();
        return def;
    };
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    j.at("id").get_to(t.id);
    t.name = safe_str("name");
    t.key = safe_str("key");
    t.created_at = safe_str("createdAt");
    t.updated_at = safe_str("updatedAt");
    t.display_name = safe_str("displayName");
    t.issue_estimation_type = safe_str("issueEstimationType");

    t.description = opt_str("description");
    t.icon = opt_str("icon");
    t.color = opt_str("color");
    t.timezone = opt_str("timezone");

    t.cycles_enabled = safe_bool("cyclesEnabled");
    t.triage_enabled = safe_bool("triageEnabled");
    t.private_team = safe_bool("private");

    t.issue_count = safe_int("issueCount");
    t.cycle_duration = safe_double("cycleDuration");
    t.cycle_cooldown_time = safe_double("cycleCooldownTime");
    t.cycle_start_day = safe_double("cycleStartDay");
}

inline void from_json(const json& j, WorkflowState& s) {
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

    j.at("id").get_to(s.id);
    s.name = safe_str("name");
    s.color = safe_str("color");
    s.created_at = safe_str("createdAt");
    s.type = safe_str("type");
    s.position = safe_double("position");

    s.description = opt_str("description");

    if (j.contains("team") && !j["team"].is_null()) {
        const auto& team = j["team"];
        s.team_id = team.value("id", "");
        s.team_name = team.value("name", "");
    }
}
