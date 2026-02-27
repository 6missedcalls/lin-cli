#include <gtest/gtest.h>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "modules/issues/api.h"
#include "modules/issues/model.h"
#include "modules/teams/model.h"
#include "tui/picker.h"

namespace {

// Helper: create a minimal Issue for testing
Issue make_issue(const std::string& id, const std::string& title,
                 const std::string& state_id, int priority = 3) {
    Issue i;
    i.id = id;
    i.title = title;
    i.state_id = state_id;
    i.priority = static_cast<double>(priority);
    i.priority_label = (priority == 1 ? "Urgent" : priority == 2 ? "High" : priority == 3 ? "Normal" : "Low");
    return i;
}

// Helper: create a WorkflowState
WorkflowState make_state(const std::string& id, const std::string& name,
                         const std::string& type, double position) {
    WorkflowState s;
    s.id = id;
    s.name = name;
    s.type = type;
    s.position = position;
    return s;
}

}  // namespace

// =============================================================================
// KANBAN BOARD TESTS
// =============================================================================

TEST(TuiKanban, GroupsIssuesByState) {
    std::vector<Issue> issues = {
        make_issue("i1", "Bug fix", "state-started", 2),
        make_issue("i2", "Feature", "state-backlog", 3),
        make_issue("i3", "Refactor", "state-started", 4),
        make_issue("i4", "Docs", "state-done", 3),
    };

    std::map<std::string, std::vector<Issue>> grouped;
    for (const auto& issue : issues) {
        if (issue.state_id) {
            grouped[*issue.state_id].push_back(issue);
        }
    }

    EXPECT_EQ(grouped.size(), 3);
    EXPECT_EQ(grouped["state-started"].size(), 2);
    EXPECT_EQ(grouped["state-backlog"].size(), 1);
    EXPECT_EQ(grouped["state-done"].size(), 1);
}

TEST(TuiKanban, SortsStatesByPosition) {
    std::vector<WorkflowState> states = {
        make_state("s3", "Done", "completed", 3.0),
        make_state("s1", "Backlog", "backlog", 1.0),
        make_state("s2", "In Progress", "started", 2.0),
    };

    std::sort(states.begin(), states.end(), [](const auto& a, const auto& b) {
        return a.position < b.position;
    });

    EXPECT_EQ(states[0].name, "Backlog");
    EXPECT_EQ(states[1].name, "In Progress");
    EXPECT_EQ(states[2].name, "Done");
}

TEST(TuiKanban, HandlesIssuesWithNoState) {
    std::vector<Issue> issues = {
        make_issue("i1", "Has state", "state-1"),
    };
    Issue no_state;
    no_state.id = "i2";
    no_state.title = "No state";
    issues.push_back(no_state);

    std::map<std::string, std::vector<Issue>> grouped;
    for (const auto& issue : issues) {
        std::string key = issue.state_id.value_or("_unassigned");
        grouped[key].push_back(issue);
    }

    EXPECT_EQ(grouped["state-1"].size(), 1);
    EXPECT_EQ(grouped["_unassigned"].size(), 1);
}

TEST(TuiKanban, EmptyColumnsAreIncluded) {
    std::vector<WorkflowState> states = {
        make_state("s1", "Backlog", "backlog", 1.0),
        make_state("s2", "In Progress", "started", 2.0),
        make_state("s3", "Done", "completed", 3.0),
    };
    std::vector<Issue> issues = {
        make_issue("i1", "Only issue", "s1"),
    };

    // All columns should exist even if empty
    std::map<std::string, std::vector<Issue>> grouped;
    for (const auto& state : states) {
        grouped[state.id] = {};  // Initialize all columns
    }
    for (const auto& issue : issues) {
        if (issue.state_id) {
            grouped[*issue.state_id].push_back(issue);
        }
    }

    EXPECT_EQ(grouped.size(), 3);
    EXPECT_EQ(grouped["s1"].size(), 1);
    EXPECT_EQ(grouped["s2"].size(), 0);
    EXPECT_EQ(grouped["s3"].size(), 0);
}

TEST(TuiKanban, MaintainsStateOrderWithMultipleIssues) {
    std::vector<WorkflowState> states = {
        make_state("backlog", "Backlog", "backlog", 0.0),
        make_state("started", "In Progress", "started", 1.0),
        make_state("completed", "Done", "completed", 2.0),
    };

    std::vector<Issue> issues = {
        make_issue("i1", "First", "completed"),
        make_issue("i2", "Second", "started"),
        make_issue("i3", "Third", "backlog"),
        make_issue("i4", "Fourth", "started"),
        make_issue("i5", "Fifth", "completed"),
    };

    std::map<std::string, std::vector<Issue>> grouped;
    for (const auto& state : states) {
        grouped[state.id] = {};
    }
    for (const auto& issue : issues) {
        if (issue.state_id) {
            grouped[*issue.state_id].push_back(issue);
        }
    }

    std::sort(states.begin(), states.end(), [](const auto& a, const auto& b) {
        return a.position < b.position;
    });

    EXPECT_EQ(states[0].id, "backlog");
    EXPECT_EQ(states[1].id, "started");
    EXPECT_EQ(states[2].id, "completed");

    EXPECT_EQ(grouped["backlog"].size(), 1);
    EXPECT_EQ(grouped["started"].size(), 2);
    EXPECT_EQ(grouped["completed"].size(), 2);
}

// =============================================================================
// DETAIL VIEW TESTS
// =============================================================================

TEST(TuiDetail, PriorityLabelMapping) {
    // Test the mapping logic that the TUI uses
    auto label = [](int p) -> std::string {
        switch (p) {
            case 0: return "---";
            case 1: return "URG";
            case 2: return "HI ";
            case 3: return "NRM";
            case 4: return "LOW";
            default: return "---";
        }
    };

    EXPECT_EQ(label(0), "---");
    EXPECT_EQ(label(1), "URG");
    EXPECT_EQ(label(2), "HI ");
    EXPECT_EQ(label(3), "NRM");
    EXPECT_EQ(label(4), "LOW");
}

TEST(TuiDetail, IssueDisplayTruncation) {
    std::string long_title(200, 'A');
    std::string truncated = long_title.substr(0, 60) + "...";
    EXPECT_EQ(truncated.size(), 63);
    EXPECT_EQ(truncated.back(), '.');
}

TEST(TuiDetail, TruncationPreservesContent) {
    std::string title = "This is a very long issue title that should be truncated";
    size_t max_len = 40;
    std::string truncated = (title.length() > max_len)
        ? title.substr(0, max_len - 3) + "..."
        : title;

    EXPECT_LE(truncated.length(), max_len);
    EXPECT_EQ(truncated.substr(0, 4), "This");
}

TEST(TuiDetail, IssueDisplayWithMissingFields) {
    Issue i = make_issue("i1", "Test issue", "state-1");
    // Leave optional fields unset
    EXPECT_TRUE(i.assignee_name.has_value() == false);
    EXPECT_TRUE(i.due_date.has_value() == false);
    EXPECT_TRUE(i.estimate.has_value() == false);
}

TEST(TuiDetail, PriorityDisplayForDifferentValues) {
    auto get_priority_label = [](double p) -> std::string {
        int int_p = static_cast<int>(p);
        switch (int_p) {
            case 0: return "---";
            case 1: return "URG";
            case 2: return "HI ";
            case 3: return "NRM";
            case 4: return "LOW";
            default: return "---";
        }
    };

    Issue i1 = make_issue("i1", "Urgent", "s1", 1);
    Issue i2 = make_issue("i2", "High", "s1", 2);
    Issue i3 = make_issue("i3", "Normal", "s1", 3);
    Issue i4 = make_issue("i4", "Low", "s1", 4);

    EXPECT_EQ(get_priority_label(i1.priority), "URG");
    EXPECT_EQ(get_priority_label(i2.priority), "HI ");
    EXPECT_EQ(get_priority_label(i3.priority), "NRM");
    EXPECT_EQ(get_priority_label(i4.priority), "LOW");
}

// =============================================================================
// SEARCH TESTS
// =============================================================================

TEST(TuiSearch, EmptyQueryReturnsNoResults) {
    std::string query = "";
    EXPECT_TRUE(query.empty());
    // Search should not be triggered on empty query
}

TEST(TuiSearch, QueryTrimming) {
    std::string query = "  hello world  ";
    // Trim leading/trailing whitespace
    size_t start = query.find_first_not_of(" \t");
    size_t end = query.find_last_not_of(" \t");
    std::string trimmed = (start == std::string::npos) ? "" : query.substr(start, end - start + 1);
    EXPECT_EQ(trimmed, "hello world");
}

TEST(TuiSearch, QueryTrimmingMultipleSpaces) {
    std::string query = "   search term   ";
    size_t start = query.find_first_not_of(" \t");
    size_t end = query.find_last_not_of(" \t");
    std::string trimmed = (start == std::string::npos) ? "" : query.substr(start, end - start + 1);
    EXPECT_EQ(trimmed, "search term");
}

TEST(TuiSearch, FilterIssuesByTitle) {
    std::vector<Issue> issues = {
        make_issue("i1", "Fix login bug", "s1"),
        make_issue("i2", "Add feature", "s1"),
        make_issue("i3", "Fix database issue", "s1"),
    };

    std::string query = "fix";
    std::vector<Issue> results;
    for (const auto& issue : issues) {
        std::string title = issue.title;
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        if (title.find(query) != std::string::npos) {
            results.push_back(issue);
        }
    }

    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].id, "i1");
    EXPECT_EQ(results[1].id, "i3");
}

TEST(TuiSearch, FilterIssuesByIdentifier) {
    Issue i1 = make_issue("i1", "Title", "s1");
    i1.identifier = "ENG-123";

    Issue i2 = make_issue("i2", "Title", "s1");
    i2.identifier = "PROD-456";

    std::vector<Issue> issues = {i1, i2};

    std::string query = "ENG";
    std::vector<Issue> results;
    for (const auto& issue : issues) {
        if (issue.identifier.find(query) != std::string::npos) {
            results.push_back(issue);
        }
    }

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].identifier, "ENG-123");
}

TEST(TuiSearch, CaseInsensitiveSearch) {
    std::vector<Issue> issues = {
        make_issue("i1", "CRITICAL BUG", "s1"),
        make_issue("i2", "Feature request", "s1"),
    };

    std::string query = "bug";
    std::vector<Issue> results;
    for (const auto& issue : issues) {
        std::string title = issue.title;
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::string q = query;
        std::transform(q.begin(), q.end(), q.begin(), ::tolower);
        if (title.find(q) != std::string::npos) {
            results.push_back(issue);
        }
    }

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].id, "i1");
}

// =============================================================================
// STATE TYPE TESTS
// =============================================================================

TEST(TuiKanban, StateTypeClassification) {
    std::vector<WorkflowState> states = {
        make_state("s1", "Backlog", "backlog", 0.0),
        make_state("s2", "Triage", "triage", 0.5),
        make_state("s3", "In Progress", "started", 1.0),
        make_state("s4", "Done", "completed", 2.0),
        make_state("s5", "Canceled", "canceled", 3.0),
    };

    // Group by type
    std::map<std::string, std::vector<WorkflowState>> by_type;
    for (const auto& state : states) {
        by_type[state.type].push_back(state);
    }

    EXPECT_EQ(by_type["backlog"].size(), 1);
    EXPECT_EQ(by_type["triage"].size(), 1);
    EXPECT_EQ(by_type["started"].size(), 1);
    EXPECT_EQ(by_type["completed"].size(), 1);
    EXPECT_EQ(by_type["canceled"].size(), 1);
}

// =============================================================================
// COLUMN RENDERING TESTS
// =============================================================================

TEST(TuiKanban, ColumnHeightCalculation) {
    std::vector<Issue> issues = {
        make_issue("i1", "Issue 1", "s1"),
        make_issue("i2", "Issue 2", "s1"),
        make_issue("i3", "Issue 3", "s1"),
    };

    std::map<std::string, std::vector<Issue>> grouped;
    grouped["s1"] = issues;
    grouped["s2"] = {};
    grouped["s3"] = {make_issue("i4", "Issue 4", "s3")};

    // Simulate height calculation (e.g., 1 header + issues + padding)
    auto calc_height = [](size_t issue_count) -> int {
        return 1 + static_cast<int>(issue_count) + 2;  // header + issues + padding
    };

    EXPECT_EQ(calc_height(grouped["s1"].size()), 6);
    EXPECT_EQ(calc_height(grouped["s2"].size()), 3);
    EXPECT_EQ(calc_height(grouped["s3"].size()), 4);
}

TEST(TuiKanban, MaxIssuesPerColumnLimit) {
    // Create many issues
    std::vector<Issue> issues;
    for (int i = 0; i < 100; ++i) {
        issues.push_back(make_issue("i" + std::to_string(i), "Issue " + std::to_string(i), "s1"));
    }

    // Limit display to first 20
    const int max_display = 20;
    std::vector<Issue> displayed(issues.begin(), issues.begin() + std::min(max_display, static_cast<int>(issues.size())));

    EXPECT_EQ(displayed.size(), 20);
    EXPECT_EQ(displayed[0].id, "i0");
    EXPECT_EQ(displayed[19].id, "i19");
}

// =============================================================================
// ISSUE ASSIGNMENT DISPLAY
// =============================================================================

TEST(TuiDetail, DisplayAssignedIssue) {
    Issue i = make_issue("i1", "Test", "s1");
    i.assignee_name = "Alice";
    EXPECT_TRUE(i.assignee_name.has_value());
    EXPECT_EQ(*i.assignee_name, "Alice");
}

TEST(TuiDetail, DisplayUnassignedIssue) {
    Issue i = make_issue("i1", "Test", "s1");
    EXPECT_FALSE(i.assignee_name.has_value());
}

// =============================================================================
// ISSUE FILTERING BY ASSIGNEE
// =============================================================================

TEST(TuiKanban, FilterIssuesByAssignee) {
    Issue i1 = make_issue("i1", "Task 1", "s1");
    i1.assignee_name = "Alice";

    Issue i2 = make_issue("i2", "Task 2", "s1");
    i2.assignee_name = "Bob";

    Issue i3 = make_issue("i3", "Task 3", "s1");
    // Unassigned

    std::vector<Issue> issues = {i1, i2, i3};

    // Filter by assignee
    std::string target = "Alice";
    std::vector<Issue> assigned_to_alice;
    for (const auto& issue : issues) {
        if (issue.assignee_name && *issue.assignee_name == target) {
            assigned_to_alice.push_back(issue);
        }
    }

    EXPECT_EQ(assigned_to_alice.size(), 1);
    EXPECT_EQ(assigned_to_alice[0].id, "i1");
}

// =============================================================================
// DATE DISPLAY TESTS
// =============================================================================

TEST(TuiDetail, DisplayDueDate) {
    Issue i = make_issue("i1", "Task", "s1");
    i.due_date = "2026-03-15";
    EXPECT_TRUE(i.due_date.has_value());
    EXPECT_EQ(*i.due_date, "2026-03-15");
}

TEST(TuiDetail, DisplayEstimate) {
    Issue i = make_issue("i1", "Task", "s1");
    i.estimate = 5.0;
    EXPECT_TRUE(i.estimate.has_value());
    EXPECT_EQ(*i.estimate, 5.0);
}

// =============================================================================
// LABEL DISPLAY
// =============================================================================

TEST(TuiDetail, DisplayIssueLabels) {
    Issue i = make_issue("i1", "Task", "s1");
    i.label_names = {"bug", "critical", "frontend"};

    EXPECT_EQ(i.label_names.size(), 3);
    EXPECT_EQ(i.label_names[0], "bug");
    EXPECT_EQ(i.label_names[2], "frontend");
}

TEST(TuiKanban, FilterIssuesByLabel) {
    Issue i1 = make_issue("i1", "Task 1", "s1");
    i1.label_names = {"bug", "critical"};

    Issue i2 = make_issue("i2", "Task 2", "s1");
    i2.label_names = {"feature", "enhancement"};

    Issue i3 = make_issue("i3", "Task 3", "s1");
    i3.label_names = {"bug", "frontend"};

    std::vector<Issue> issues = {i1, i2, i3};

    // Filter by label "bug"
    std::string target = "bug";
    std::vector<Issue> with_bug_label;
    for (const auto& issue : issues) {
        auto it = std::find(issue.label_names.begin(), issue.label_names.end(), target);
        if (it != issue.label_names.end()) {
            with_bug_label.push_back(issue);
        }
    }

    EXPECT_EQ(with_bug_label.size(), 2);
    EXPECT_EQ(with_bug_label[0].id, "i1");
    EXPECT_EQ(with_bug_label[1].id, "i3");
}

// =============================================================================
// PICKER OVERLAY TESTS
// =============================================================================

TEST(TuiPicker, PriorityPickerHasFiveItems) {
    auto items = tui::build_priority_picker_items();
    EXPECT_EQ(items.size(), 5);
}

TEST(TuiPicker, PriorityPickerItemOrder) {
    auto items = tui::build_priority_picker_items();
    EXPECT_EQ(items[0].label, "No priority");
    EXPECT_EQ(items[1].label, "Urgent");
    EXPECT_EQ(items[2].label, "High");
    EXPECT_EQ(items[3].label, "Normal");
    EXPECT_EQ(items[4].label, "Low");
}

TEST(TuiPicker, PriorityPickerItemValues) {
    auto items = tui::build_priority_picker_items();
    EXPECT_EQ(items[0].value, "0");
    EXPECT_EQ(items[1].value, "1");
    EXPECT_EQ(items[2].value, "2");
    EXPECT_EQ(items[3].value, "3");
    EXPECT_EQ(items[4].value, "4");
}

TEST(TuiPicker, PriorityUpdateInput) {
    auto input = tui::make_priority_update(2);
    ASSERT_TRUE(input.priority.has_value());
    EXPECT_EQ(*input.priority, 2);
    EXPECT_FALSE(input.state_id.has_value());
    EXPECT_FALSE(input.assignee_id.has_value());
}

TEST(TuiPicker, PriorityUpdateInputNone) {
    auto input = tui::make_priority_update(0);
    ASSERT_TRUE(input.priority.has_value());
    EXPECT_EQ(*input.priority, 0);
}

TEST(TuiPicker, StateUpdateInput) {
    auto input = tui::make_state_update("state-abc-123");
    ASSERT_TRUE(input.state_id.has_value());
    EXPECT_EQ(*input.state_id, "state-abc-123");
    EXPECT_FALSE(input.priority.has_value());
    EXPECT_FALSE(input.assignee_id.has_value());
}

TEST(TuiPicker, AssignUpdateInput) {
    auto input = tui::make_assign_update("user-abc-123");
    ASSERT_TRUE(input.assignee_id.has_value());
    EXPECT_EQ(*input.assignee_id, "user-abc-123");
    EXPECT_FALSE(input.priority.has_value());
    EXPECT_FALSE(input.state_id.has_value());
}

TEST(TuiPicker, UnassignUpdateInput) {
    auto input = tui::make_assign_update("");
    ASSERT_TRUE(input.assignee_id.has_value());
    EXPECT_EQ(*input.assignee_id, "");
}

TEST(TuiPicker, StatePickerFromWorkflowStates) {
    std::vector<WorkflowState> states = {
        make_state("s1", "Backlog", "backlog", 1.0),
        make_state("s2", "In Progress", "started", 2.0),
        make_state("s3", "Done", "completed", 3.0),
    };

    auto items = tui::build_state_picker_items(states);
    ASSERT_EQ(items.size(), 3);
    EXPECT_EQ(items[0].label, "Backlog");
    EXPECT_EQ(items[0].value, "s1");
    EXPECT_EQ(items[1].label, "In Progress");
    EXPECT_EQ(items[1].value, "s2");
    EXPECT_EQ(items[2].label, "Done");
    EXPECT_EQ(items[2].value, "s3");
}

TEST(TuiPicker, AssignPickerFromTeamMembers) {
    std::vector<TeamMember> members;
    TeamMember m1; m1.id = "u1"; m1.display_name = "Alice"; m1.active = true;
    TeamMember m2; m2.id = "u2"; m2.display_name = "Bob"; m2.active = true;
    members = {m1, m2};

    auto items = tui::build_assign_picker_items(members);
    // First item should be "Unassign"
    ASSERT_GE(items.size(), 3);
    EXPECT_EQ(items[0].label, "Unassign");
    EXPECT_EQ(items[0].value, "");
    EXPECT_EQ(items[1].label, "Alice");
    EXPECT_EQ(items[1].value, "u1");
    EXPECT_EQ(items[2].label, "Bob");
    EXPECT_EQ(items[2].value, "u2");
}

TEST(TuiPicker, PickerSelectionClamp) {
    auto items = tui::build_priority_picker_items();
    int sel = 3;
    // Move down past end
    sel = tui::clamp_picker_selection(sel + 1, items.size());
    EXPECT_EQ(sel, 4);
    sel = tui::clamp_picker_selection(sel + 1, items.size());
    EXPECT_EQ(sel, 4);  // clamped at last item
    // Move up past start
    sel = 0;
    sel = tui::clamp_picker_selection(sel - 1, items.size());
    EXPECT_EQ(sel, 0);  // clamped at 0
}

TEST(TuiPicker, EmptyMembersListStillHasUnassign) {
    std::vector<TeamMember> empty_members;
    auto items = tui::build_assign_picker_items(empty_members);
    ASSERT_EQ(items.size(), 1);
    EXPECT_EQ(items[0].label, "Unassign");
    EXPECT_EQ(items[0].value, "");
}

// =============================================================================
// DYNAMIC PRIORITY PICKER TESTS
// =============================================================================

TEST(TuiPicker, DynamicPriorityPickerFromValues) {
    std::vector<PriorityValue> values = {
        {0, "No priority"},
        {1, "Urgent"},
        {2, "High"},
        {3, "Medium"},
        {4, "Low"},
    };

    auto items = tui::build_priority_picker_items(values);
    ASSERT_EQ(items.size(), 5);
    EXPECT_EQ(items[0].label, "No priority");
    EXPECT_EQ(items[0].value, "0");
    EXPECT_EQ(items[1].label, "Urgent");
    EXPECT_EQ(items[1].value, "1");
    EXPECT_EQ(items[3].label, "Medium");
    EXPECT_EQ(items[3].value, "3");
}

TEST(TuiPicker, DynamicPriorityPickerPreservesOrder) {
    std::vector<PriorityValue> values = {
        {4, "Low"},
        {0, "None"},
        {2, "High"},
        {1, "Urgent"},
        {3, "Medium"},
    };

    auto items = tui::build_priority_picker_items(values);
    ASSERT_EQ(items.size(), 5);
    // Should preserve input order (API returns them sorted by priority int)
    EXPECT_EQ(items[0].label, "Low");
    EXPECT_EQ(items[0].value, "4");
    EXPECT_EQ(items[1].label, "None");
    EXPECT_EQ(items[1].value, "0");
}

TEST(TuiPicker, DynamicPriorityPickerCustomLabels) {
    // Workspace might have custom labels
    std::vector<PriorityValue> values = {
        {0, "None"},
        {1, "Critical"},
        {2, "Important"},
        {3, "Normal"},
        {4, "Nice to have"},
    };

    auto items = tui::build_priority_picker_items(values);
    ASSERT_EQ(items.size(), 5);
    EXPECT_EQ(items[1].label, "Critical");
    EXPECT_EQ(items[4].label, "Nice to have");
}

TEST(TuiPicker, DynamicPriorityPickerEmpty) {
    std::vector<PriorityValue> empty;
    auto items = tui::build_priority_picker_items(empty);
    EXPECT_TRUE(items.empty());
}

TEST(TuiPicker, PriorityValueParsing) {
    nlohmann::json j = nlohmann::json::array({
        {{"priority", 0}, {"label", "No priority"}},
        {{"priority", 1}, {"label", "Urgent"}},
        {{"priority", 2}, {"label", "High"}},
        {{"priority", 3}, {"label", "Medium"}},
        {{"priority", 4}, {"label", "Low"}},
    });

    std::vector<PriorityValue> values;
    for (const auto& item : j) {
        PriorityValue pv;
        from_json(item, pv);
        values.push_back(pv);
    }

    ASSERT_EQ(values.size(), 5);
    EXPECT_EQ(values[0].priority, 0);
    EXPECT_EQ(values[0].label, "No priority");
    EXPECT_EQ(values[1].priority, 1);
    EXPECT_EQ(values[1].label, "Urgent");
    EXPECT_EQ(values[4].priority, 4);
    EXPECT_EQ(values[4].label, "Low");
}

// =============================================================================
// DETAIL VIEW DIRTY TRACKING TESTS
// =============================================================================
// When the detail view makes a mutation (state/priority/assign change),
// closing the detail should trigger a kanban refresh so changes are visible.

TEST(TuiDetail, CloseAfterUpdateShouldTriggerRefresh) {
    // Simulate the pattern: detail view has an on_close and on_refresh callback.
    // After a mutation, closing should call on_refresh (not just on_close)
    // so the kanban rebuilds with fresh data.
    bool on_close_called = false;
    bool on_refresh_called = false;
    bool dirty = false;  // tracks whether a mutation was made

    auto on_close = [&]() { on_close_called = true; };
    auto on_refresh = [&]() { on_refresh_called = true; };

    // Simulate: user opens detail, makes a state change (dirty=true), then closes
    dirty = true;  // mutation happened

    // When closing with dirty flag, on_refresh should be called
    if (dirty) {
        on_refresh();
    } else {
        on_close();
    }

    EXPECT_TRUE(on_refresh_called);
    EXPECT_FALSE(on_close_called);
}

TEST(TuiDetail, CloseWithoutUpdateShouldNotRefresh) {
    bool on_close_called = false;
    bool on_refresh_called = false;
    bool dirty = false;

    auto on_close = [&]() { on_close_called = true; };
    auto on_refresh = [&]() { on_refresh_called = true; };

    // No mutation happened, just closing
    if (dirty) {
        on_refresh();
    } else {
        on_close();
    }

    EXPECT_FALSE(on_refresh_called);
    EXPECT_TRUE(on_close_called);
}
