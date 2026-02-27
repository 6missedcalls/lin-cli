#include "core/filter.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <unordered_map>

namespace {

std::string to_lower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

const std::unordered_map<std::string, int> priority_map = {
    {"none", 0},
    {"urgent", 1},
    {"high", 2},
    {"normal", 3},
    {"medium", 3},
    {"low", 4},
};

const std::vector<std::string> valid_state_types = {
    "triage", "backlog", "unstarted", "started", "completed", "canceled",
};

json wrap_in_and(const std::vector<json>& clauses) {
    if (clauses.empty()) {
        return json(nullptr);
    }
    if (clauses.size() == 1) {
        return clauses[0];
    }
    return json{{"and", clauses}};
}

}  // namespace

std::optional<int> priority_name_to_number(const std::string& name) {
    auto it = priority_map.find(to_lower(name));
    if (it != priority_map.end()) {
        return it->second;
    }
    // Also accept raw numeric strings 0-4
    try {
        int val = std::stoi(name);
        if (val >= 0 && val <= 4) {
            return val;
        }
    } catch (const std::exception&) {
        // Not a number, fall through
    }
    return std::nullopt;
}

bool is_valid_state_type(const std::string& type) {
    std::string lower = to_lower(type);
    return std::find(valid_state_types.begin(), valid_state_types.end(), lower)
           != valid_state_types.end();
}

json build_issue_filter(
    const std::optional<std::string>& team,
    const std::optional<std::string>& assignee,
    const std::optional<std::string>& state,
    const std::optional<std::string>& state_type,
    const std::optional<std::string>& priority,
    const std::optional<std::string>& label,
    const std::optional<std::string>& project,
    const std::optional<std::string>& cycle,
    const std::optional<std::string>& creator
) {
    std::vector<json> clauses;

    if (team.has_value()) {
        clauses.push_back(json{
            {"team", {{"key", {{"eq", team.value()}}}}}
        });
    }

    if (assignee.has_value()) {
        if (assignee.value() == "@me") {
            clauses.push_back(json{
                {"assignee", {{"isMe", {{"eq", true}}}}}
            });
        } else {
            clauses.push_back(json{
                {"assignee", {{"displayName", {{"eqIgnoreCase", assignee.value()}}}}}
            });
        }
    }

    if (state.has_value()) {
        clauses.push_back(json{
            {"state", {{"name", {{"eqIgnoreCase", state.value()}}}}}
        });
    }

    if (state_type.has_value()) {
        clauses.push_back(json{
            {"state", {{"type", {{"eq", state_type.value()}}}}}
        });
    }

    if (priority.has_value()) {
        auto pnum = priority_name_to_number(priority.value());
        if (pnum.has_value()) {
            clauses.push_back(json{
                {"priority", {{"eq", pnum.value()}}}
            });
        }
    }

    if (label.has_value()) {
        clauses.push_back(json{
            {"labels", {{"name", {{"eqIgnoreCase", label.value()}}}}}
        });
    }

    if (project.has_value()) {
        clauses.push_back(json{
            {"project", {{"name", {{"eqIgnoreCase", project.value()}}}}}
        });
    }

    if (cycle.has_value()) {
        try {
            int cycle_number = std::stoi(cycle.value());
            clauses.push_back(json{
                {"cycle", {{"number", {{"eq", cycle_number}}}}}
            });
        } catch (const std::exception&) {
            // Invalid cycle number — skip this filter
        }
    }

    if (creator.has_value()) {
        clauses.push_back(json{
            {"creator", {{"displayName", {{"eqIgnoreCase", creator.value()}}}}}
        });
    }

    return wrap_in_and(clauses);
}

json build_project_filter(
    const std::optional<std::string>& status,
    const std::optional<std::string>& lead,
    const std::optional<std::string>& health
) {
    std::vector<json> clauses;

    if (status.has_value()) {
        clauses.push_back(json{
            {"status", {{"name", {{"eqIgnoreCase", status.value()}}}}}
        });
    }

    if (lead.has_value()) {
        clauses.push_back(json{
            {"lead", {{"displayName", {{"eqIgnoreCase", lead.value()}}}}}
        });
    }

    if (health.has_value()) {
        clauses.push_back(json{
            {"health", {{"eq", health.value()}}}
        });
    }

    return wrap_in_and(clauses);
}

json build_cycle_filter(
    const std::optional<std::string>& team,
    bool active_only
) {
    std::vector<json> clauses;

    if (team.has_value()) {
        clauses.push_back(json{
            {"team", {{"key", {{"eq", team.value()}}}}}
        });
    }

    if (active_only) {
        clauses.push_back(json{
            {"isActive", {{"eq", true}}}
        });
    }

    return wrap_in_and(clauses);
}
