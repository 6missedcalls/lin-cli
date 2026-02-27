#pragma once

#include <string>

namespace tui {

// Launches the TUI application.
// team_key: optional team key or ID to start with.
//   If empty, uses the config default team, or falls back to the first team
//   returned by the API.
// Returns 0 on normal exit, non-zero on startup error.
int run(const std::string& team_key = "");

}  // namespace tui
