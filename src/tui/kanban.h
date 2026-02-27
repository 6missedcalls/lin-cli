#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>

namespace tui {

struct KanbanConfig {
    std::string team_id;
    int max_issues_per_column = 25;
};

// Creates a kanban board component.
// on_select is called when the user presses Enter on an issue.
// Returns an FTXUI Component.
ftxui::Component KanbanBoard(
    KanbanConfig config,
    std::function<void(const std::string& issue_id)> on_select
);

}  // namespace tui
