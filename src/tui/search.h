#pragma once

#include <functional>
#include <string>

#include <ftxui/component/component.hpp>

namespace tui {

// Creates a search overlay component.
// on_select is called with an issue ID when the user selects a result.
// on_close is called when the user presses Escape.
ftxui::Component SearchOverlay(
    std::function<void(const std::string& issue_id)> on_select,
    std::function<void()> on_close
);

}  // namespace tui
