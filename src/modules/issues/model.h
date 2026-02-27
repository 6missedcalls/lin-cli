#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Issue {
    std::string id;
    std::string created_at;
    std::string updated_at;
    std::optional<std::string> archived_at;

    double number = 0;
    std::string title;
    double priority = 0;                          // 0=None, 1=Urgent, 2=High, 3=Normal, 4=Low
    std::string priority_label;
    std::optional<double> estimate;
    std::string identifier;                       // e.g. "ENG-123"
    std::string url;
    std::string branch_name;

    std::optional<std::string> description;
    std::optional<std::string> due_date;
    std::optional<std::string> started_at;
    std::optional<std::string> completed_at;
    std::optional<std::string> canceled_at;
    bool trashed = false;

    std::optional<std::string> team_id;
    std::optional<std::string> team_name;
    std::optional<std::string> team_key;

    std::optional<std::string> assignee_id;
    std::optional<std::string> assignee_name;

    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;

    std::optional<std::string> state_id;
    std::optional<std::string> state_name;
    std::optional<std::string> state_type;

    std::optional<std::string> project_id;
    std::optional<std::string> project_name;

    std::optional<std::string> cycle_id;
    std::optional<double> cycle_number;

    std::optional<std::string> parent_id;
    std::optional<std::string> parent_identifier;

    std::vector<std::string> label_ids;
    std::vector<std::string> label_names;
    std::vector<std::string> previous_identifiers;
};

struct PriorityValue {
    int priority = 0;
    std::string label;
};

inline void from_json(const json& j, PriorityValue& pv) {
    pv.priority = j.at("priority").get<int>();
    pv.label = j.at("label").get<std::string>();
}

struct IssueRelation {
    std::string id;
    std::string created_at;
    std::string type;  // blocks, duplicate, related, similar

    std::optional<std::string> issue_id;
    std::optional<std::string> issue_identifier;
    std::optional<std::string> related_issue_id;
    std::optional<std::string> related_issue_identifier;
};

struct Attachment {
    std::string id;
    std::string created_at;
    std::optional<std::string> title;
    std::optional<std::string> subtitle;
    std::optional<std::string> url;
    std::optional<std::string> source_type;
    std::optional<std::string> creator_id;
    std::optional<std::string> creator_name;
    std::optional<std::string> issue_id;
};

// --- from_json implementations (inline) ---

inline void from_json(const json& j, Issue& i) {
    // Null-safe accessors: j.value() doesn't handle null, only missing keys
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

    j.at("id").get_to(i.id);
    j.at("title").get_to(i.title);
    j.at("identifier").get_to(i.identifier);
    i.number = safe_double("number");
    i.priority = safe_double("priority");
    i.priority_label = safe_str("priorityLabel");
    i.url = safe_str("url");
    i.branch_name = safe_str("branchName");
    i.created_at = safe_str("createdAt");
    i.updated_at = safe_str("updatedAt");
    i.trashed = safe_bool("trashed");

    // Optional strings
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    i.archived_at = opt_str("archivedAt");
    i.description = opt_str("description");
    i.due_date = opt_str("dueDate");
    i.started_at = opt_str("startedAt");
    i.completed_at = opt_str("completedAt");
    i.canceled_at = opt_str("canceledAt");

    // Optional double
    if (j.contains("estimate") && !j["estimate"].is_null()) {
        i.estimate = j["estimate"].get<double>();
    }

    // Flatten nested: assignee
    if (j.contains("assignee") && !j["assignee"].is_null()) {
        const auto& a = j["assignee"];
        i.assignee_id = a.value("id", "");
        i.assignee_name = a.value("displayName", "");
    }

    // Flatten nested: team
    if (j.contains("team") && !j["team"].is_null()) {
        const auto& t = j["team"];
        i.team_id = t.value("id", "");
        i.team_name = t.value("name", "");
        i.team_key = t.value("key", "");
    }

    // Flatten nested: state
    if (j.contains("state") && !j["state"].is_null()) {
        const auto& s = j["state"];
        i.state_id = s.value("id", "");
        i.state_name = s.value("name", "");
        i.state_type = s.value("type", "");
    }

    // Flatten nested: creator
    if (j.contains("creator") && !j["creator"].is_null()) {
        const auto& c = j["creator"];
        i.creator_id = c.value("id", "");
        i.creator_name = c.value("displayName", "");
    }

    // Flatten nested: project
    if (j.contains("project") && !j["project"].is_null()) {
        const auto& p = j["project"];
        i.project_id = p.value("id", "");
        i.project_name = p.value("name", "");
    }

    // Flatten nested: cycle
    if (j.contains("cycle") && !j["cycle"].is_null()) {
        const auto& c = j["cycle"];
        i.cycle_id = c.value("id", "");
        if (c.contains("number") && !c["number"].is_null()) {
            i.cycle_number = c["number"].get<double>();
        }
    }

    // Flatten nested: parent
    if (j.contains("parent") && !j["parent"].is_null()) {
        const auto& p = j["parent"];
        i.parent_id = p.value("id", "");
        i.parent_identifier = p.value("identifier", "");
    }

    // Labels array
    if (j.contains("labels") && !j["labels"].is_null()) {
        const auto& labels = j["labels"];
        if (labels.contains("nodes") && labels["nodes"].is_array()) {
            for (const auto& lbl : labels["nodes"]) {
                i.label_ids.push_back(lbl.value("id", ""));
                i.label_names.push_back(lbl.value("name", ""));
            }
        }
    }
}

inline void from_json(const json& j, IssueRelation& r) {
    j.at("id").get_to(r.id);
    r.created_at = j.value("createdAt", "");
    r.type = j.value("type", "");

    if (j.contains("issue") && !j["issue"].is_null()) {
        r.issue_id = j["issue"].value("id", "");
        r.issue_identifier = j["issue"].value("identifier", "");
    }
    if (j.contains("relatedIssue") && !j["relatedIssue"].is_null()) {
        r.related_issue_id = j["relatedIssue"].value("id", "");
        r.related_issue_identifier = j["relatedIssue"].value("identifier", "");
    }
}

inline void from_json(const json& j, Attachment& a) {
    j.at("id").get_to(a.id);
    a.created_at = j.value("createdAt", "");

    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    a.title = opt_str("title");
    a.subtitle = opt_str("subtitle");
    a.url = opt_str("url");
    a.source_type = opt_str("sourceType");

    if (j.contains("creator") && !j["creator"].is_null()) {
        a.creator_id = j["creator"].value("id", "");
        a.creator_name = j["creator"].value("displayName", "");
    }
    if (j.contains("issue") && !j["issue"].is_null()) {
        a.issue_id = j["issue"].value("id", "");
    }
}
