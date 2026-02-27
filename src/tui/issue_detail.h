#pragma once

#include <functional>
#include <string>

#include <ftxui/component/component.hpp>

namespace tui {

// Creates an issue detail panel component.
// Fetches the full issue and its comments internally on construction.
// on_close is called when the user presses Escape or q to go back.
// on_refresh is called when the issue data changes (e.g., after a state change).
ftxui::Component IssueDetailPanel(
    const std::string& issue_id,
    std::function<void()> on_close,
    std::function<void()> on_refresh = nullptr
);

}  // namespace tui
