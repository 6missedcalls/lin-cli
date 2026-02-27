#pragma once

#include <string>
#include <vector>

#include "modules/issues/api.h"
#include "modules/teams/api.h"
#include "modules/teams/model.h"

namespace tui {

struct PickerItem {
    std::string label;
    std::string value;
};

// Build the static list of priority choices (hardcoded fallback).
std::vector<PickerItem> build_priority_picker_items();

// Build priority choices from dynamic API values.
std::vector<PickerItem> build_priority_picker_items(const std::vector<PriorityValue>& values);

// Build picker items from workflow states (already sorted by position).
std::vector<PickerItem> build_state_picker_items(const std::vector<WorkflowState>& states);

// Build picker items from team members. First item is always "Unassign".
std::vector<PickerItem> build_assign_picker_items(const std::vector<TeamMember>& members);

// Construct an IssueUpdateInput that sets only the priority field.
IssueUpdateInput make_priority_update(int priority);

// Construct an IssueUpdateInput that sets only the state_id field.
IssueUpdateInput make_state_update(const std::string& state_id);

// Construct an IssueUpdateInput that sets only the assignee_id field.
// Pass empty string to unassign.
IssueUpdateInput make_assign_update(const std::string& user_id);

// Clamp a picker selection index within [0, item_count - 1].
int clamp_picker_selection(int index, std::size_t item_count);

}  // namespace tui
