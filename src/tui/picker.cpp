#include "tui/picker.h"

#include <algorithm>

namespace tui {

std::vector<PickerItem> build_priority_picker_items() {
    return {
        {"No priority", "0"},
        {"Urgent",      "1"},
        {"High",        "2"},
        {"Normal",      "3"},
        {"Low",         "4"},
    };
}

std::vector<PickerItem> build_priority_picker_items(const std::vector<PriorityValue>& values) {
    std::vector<PickerItem> items;
    items.reserve(values.size());
    for (const auto& pv : values) {
        items.push_back({pv.label, std::to_string(pv.priority)});
    }
    return items;
}

std::vector<PickerItem> build_state_picker_items(const std::vector<WorkflowState>& states) {
    std::vector<PickerItem> items;
    items.reserve(states.size());
    for (const auto& s : states) {
        items.push_back({s.name, s.id});
    }
    return items;
}

std::vector<PickerItem> build_assign_picker_items(const std::vector<TeamMember>& members) {
    std::vector<PickerItem> items;
    items.reserve(members.size() + 1);
    items.push_back({"Unassign", ""});
    for (const auto& m : members) {
        items.push_back({m.display_name, m.id});
    }
    return items;
}

IssueUpdateInput make_priority_update(int priority) {
    IssueUpdateInput input;
    input.priority = priority;
    return input;
}

IssueUpdateInput make_state_update(const std::string& state_id) {
    IssueUpdateInput input;
    input.state_id = state_id;
    return input;
}

IssueUpdateInput make_assign_update(const std::string& user_id) {
    IssueUpdateInput input;
    input.assignee_id = user_id;
    return input;
}

int clamp_picker_selection(int index, std::size_t item_count) {
    if (item_count == 0) return 0;
    if (index < 0) return 0;
    int max_idx = static_cast<int>(item_count) - 1;
    return std::min(index, max_idx);
}

}  // namespace tui
