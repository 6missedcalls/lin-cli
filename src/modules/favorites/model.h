#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "core/types.h"

using json = nlohmann::json;

struct Favorite {
    std::string id;
    std::string created_at;
    std::string type;
    std::optional<std::string> folder_name;
    double sort_order = 0.0;

    // Flattened nested IDs
    std::optional<std::string> issue_id;
    std::optional<std::string> project_id;
    std::optional<std::string> cycle_id;
    std::optional<std::string> custom_view_id;
    std::optional<std::string> document_id;
    std::optional<std::string> label_id;

    // Display fields
    std::optional<std::string> url;
    std::optional<std::string> title;
};

// --- from_json implementation (inline) ---

inline void from_json(const json& j, Favorite& f) {
    auto opt_str = [&](const char* key) -> std::optional<std::string> {
        if (j.contains(key) && !j[key].is_null()) {
            return j[key].get<std::string>();
        }
        return std::nullopt;
    };

    j.at("id").get_to(f.id);
    f.created_at = j.value("createdAt", "");
    f.type = j.value("type", "");

    if (j.contains("sortOrder") && !j["sortOrder"].is_null()) {
        f.sort_order = j["sortOrder"].get<double>();
    }

    f.folder_name = opt_str("folderName");
    f.url = opt_str("url");
    f.title = opt_str("title");

    // Flatten nested: issue { id }
    if (j.contains("issue") && !j["issue"].is_null()) {
        f.issue_id = j["issue"].value("id", "");
    }

    // Flatten nested: project { id }
    if (j.contains("project") && !j["project"].is_null()) {
        f.project_id = j["project"].value("id", "");
    }

    // Flatten nested: cycle { id }
    if (j.contains("cycle") && !j["cycle"].is_null()) {
        f.cycle_id = j["cycle"].value("id", "");
    }

    // Flatten nested: customView { id }
    if (j.contains("customView") && !j["customView"].is_null()) {
        f.custom_view_id = j["customView"].value("id", "");
    }

    // Flatten nested: document { id }
    if (j.contains("document") && !j["document"].is_null()) {
        f.document_id = j["document"].value("id", "");
    }

    // Flatten nested: label { id }
    if (j.contains("label") && !j["label"].is_null()) {
        f.label_id = j["label"].value("id", "");
    }
}
