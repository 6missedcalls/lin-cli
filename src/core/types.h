#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct PageInfo {
    bool has_next_page = false;
    bool has_previous_page = false;
    std::optional<std::string> start_cursor;
    std::optional<std::string> end_cursor;
};

template <typename T>
struct Connection {
    std::vector<T> nodes;
    PageInfo page_info;
};

inline void from_json(const json& j, PageInfo& p) {
    p.has_next_page = j.value("hasNextPage", false);
    p.has_previous_page = j.value("hasPreviousPage", false);
    if (j.contains("startCursor") && !j["startCursor"].is_null()) {
        p.start_cursor = j["startCursor"].get<std::string>();
    }
    if (j.contains("endCursor") && !j["endCursor"].is_null()) {
        p.end_cursor = j["endCursor"].get<std::string>();
    }
}

template <typename T>
void from_json(const json& j, Connection<T>& c) {
    if (j.contains("nodes") && j["nodes"].is_array()) {
        for (const auto& node : j["nodes"]) {
            T item;
            from_json(node, item);
            c.nodes.push_back(std::move(item));
        }
    }
    if (j.contains("pageInfo")) {
        from_json(j["pageInfo"], c.page_info);
    }
}
