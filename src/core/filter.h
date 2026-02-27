#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Build an IssueFilter JSON object from CLI flags
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
);

// Build a ProjectFilter JSON object from CLI flags
json build_project_filter(
    const std::optional<std::string>& status,
    const std::optional<std::string>& lead,
    const std::optional<std::string>& health
);

// Build a CycleFilter JSON object from CLI flags
json build_cycle_filter(
    const std::optional<std::string>& team,
    bool active_only
);

// Convert priority name to number: none=0, urgent=1, high=2, normal=3, low=4
std::optional<int> priority_name_to_number(const std::string& name);

// Convert state type string for filter: triage, backlog, unstarted, started, completed, canceled
bool is_valid_state_type(const std::string& type);
