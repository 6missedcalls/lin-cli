#include "tui/app.h"

#include <functional>
#include <memory>
#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "core/config.h"
#include "core/error.h"
#include "modules/issues/api.h"
#include "modules/teams/api.h"
#include "tui/issue_detail.h"
#include "tui/kanban.h"
#include "tui/search.h"

namespace tui {

namespace {

enum class View {
    KANBAN,
    DETAIL,
    SEARCH,
    HELP,
};

// Resolve which team to operate on.
// Priority: explicit team_key argument > config default > first team from API.
Team resolve_team(const std::string& team_key) {
    if (!team_key.empty()) {
        return teams_api::get_team(team_key);
    }

    const Config config = load_config();
    if (config.defaults.team.has_value() && !config.defaults.team->empty()) {
        return teams_api::get_team(*config.defaults.team);
    }

    const Connection<Team> teams = teams_api::list_teams(1);
    if (teams.nodes.empty()) {
        throw LinError(ErrorKind::NotFound, "No teams found in this workspace");
    }
    return teams.nodes.front();
}

// Build the status bar element shown at the bottom of every view.
ftxui::Element make_status_bar(const std::string& team_name, View current_view) {
    std::string view_name;
    switch (current_view) {
        case View::KANBAN: view_name = "Kanban";  break;
        case View::DETAIL: view_name = "Detail";  break;
        case View::SEARCH: view_name = "Search";  break;
        case View::HELP:   view_name = "Help";    break;
    }

    const std::string left_text  = team_name + " | " + view_name;
    const std::string right_text = "q:quit  /:search  ?:help  r:refresh";

    return ftxui::hbox({
        ftxui::text(" " + left_text) | ftxui::bold,
        ftxui::filler(),
        ftxui::text(right_text + " ") | ftxui::dim,
    }) | ftxui::bgcolor(ftxui::Color::GrayDark);
}

// Build a simple help overlay rendered as a centered modal box.
ftxui::Element make_help_element() {
    return ftxui::vbox({
        ftxui::text(" Keybindings ") | ftxui::bold | ftxui::center,
        ftxui::separator(),
        ftxui::text(""),
        ftxui::hbox({ ftxui::text("  /      "), ftxui::text("Open search overlay") }),
        ftxui::hbox({ ftxui::text("  ?      "), ftxui::text("Toggle this help") }),
        ftxui::hbox({ ftxui::text("  r      "), ftxui::text("Refresh kanban board") }),
        ftxui::hbox({ ftxui::text("  Enter  "), ftxui::text("Open selected issue") }),
        ftxui::hbox({ ftxui::text("  Esc    "), ftxui::text("Close panel / go back") }),
        ftxui::hbox({ ftxui::text("  q      "), ftxui::text("Quit (from kanban view)") }),
        ftxui::hbox({ ftxui::text("  h/l    "), ftxui::text("Move between columns") }),
        ftxui::hbox({ ftxui::text("  j/k    "), ftxui::text("Move between issues") }),
        ftxui::text(""),
        ftxui::text("  Press ? or Esc to close") | ftxui::dim,
        ftxui::text(""),
    }) | ftxui::border | ftxui::center;
}

}  // namespace

int run(const std::string& team_key) {
    // --- Team resolution (blocking, before entering the event loop) ---
    Team team;
    std::string startup_error;

    try {
        team = resolve_team(team_key);
    } catch (const LinError& e) {
        startup_error = format_error(e);
    } catch (const std::exception& e) {
        startup_error = std::string("Failed to load team: ") + e.what();
    }

    if (!startup_error.empty()) {
        // Render a minimal error screen and exit immediately.
        auto screen = ftxui::ScreenInteractive::Fullscreen();
        auto error_component = ftxui::Renderer([&] {
            return ftxui::vbox({
                ftxui::text("lin: startup error") | ftxui::bold | ftxui::color(ftxui::Color::Red),
                ftxui::text(startup_error),
                ftxui::text(""),
                ftxui::text("Press q to quit.") | ftxui::dim,
            }) | ftxui::center;
        });
        auto quittable = ftxui::CatchEvent(error_component, [&](const ftxui::Event& event) {
            if (event == ftxui::Event::Character('q') ||
                event == ftxui::Event::Escape) {
                screen.Exit();
                return true;
            }
            return false;
        });
        screen.Loop(quittable);
        return 1;
    }

    // --- Application state ---
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    View current_view = View::KANBAN;
    std::string selected_issue_id;
    bool show_help = false;

    // Active child components (replaced on view transitions).
    ftxui::Component kanban_component;
    ftxui::Component detail_component;
    ftxui::Component search_component;

    // Forward declarations for mutual lambdas.
    std::function<void()>                         open_search;
    std::function<void(const std::string&)>       open_detail;
    std::function<void()>                         close_detail;
    std::function<void()>                         refresh_kanban;

    // --- View factory helpers ---

    auto make_kanban = [&]() -> ftxui::Component {
        return KanbanBoard(
            KanbanConfig{ team.id, 25 },
            [&](const std::string& issue_id) { open_detail(issue_id); }
        );
    };

    refresh_kanban = [&]() {
        kanban_component = make_kanban();
        current_view     = View::KANBAN;
        show_help        = false;
        screen.PostEvent(ftxui::Event::Custom);
    };

    open_detail = [&](const std::string& issue_id) {
        selected_issue_id = issue_id;
        detail_component  = IssueDetailPanel(
            issue_id,
            [&]() { close_detail(); },           // on_close
            [&]() { refresh_kanban(); }           // on_refresh
        );
        current_view = View::DETAIL;
        show_help    = false;
        screen.PostEvent(ftxui::Event::Custom);
    };

    close_detail = [&]() {
        detail_component = nullptr;
        current_view     = View::KANBAN;
        screen.PostEvent(ftxui::Event::Custom);
    };

    open_search = [&]() {
        search_component = SearchOverlay(
            [&](const std::string& issue_id) {
                search_component = nullptr;
                open_detail(issue_id);
            },
            [&]() {
                search_component = nullptr;
                current_view     = View::KANBAN;
                screen.PostEvent(ftxui::Event::Custom);
            }
        );
        current_view = View::SEARCH;
        show_help    = false;
        screen.PostEvent(ftxui::Event::Custom);
    };

    // Build the initial kanban board.
    kanban_component = make_kanban();

    // --- Root component ---
    // The renderer delegates rendering and events to the currently active child.
    auto root = ftxui::Renderer([&]() -> ftxui::Element {
        ftxui::Element content;

        switch (current_view) {
            case View::KANBAN: {
                content = kanban_component->Render();
                break;
            }
            case View::DETAIL: {
                content = detail_component
                    ? detail_component->Render()
                    : ftxui::text("Loading…") | ftxui::center;
                break;
            }
            case View::SEARCH: {
                // Render kanban underneath, search overlay on top.
                ftxui::Element base   = kanban_component->Render();
                ftxui::Element overlay = search_component
                    ? search_component->Render()
                    : ftxui::text("") | ftxui::center;
                content = ftxui::dbox({ base, overlay });
                break;
            }
            case View::HELP: {
                // Render kanban underneath, help overlay on top.
                ftxui::Element base    = kanban_component->Render();
                ftxui::Element overlay = make_help_element();
                content = ftxui::dbox({ base, overlay });
                break;
            }
        }

        return ftxui::vbox({
            content | ftxui::flex,
            make_status_bar(team.name, current_view),
        });
    });

    // --- Event routing ---
    auto root_with_events = ftxui::CatchEvent(root, [&](const ftxui::Event& event) -> bool {
        // Delegate events to the active child first so it can consume them.
        switch (current_view) {
            case View::KANBAN:
            case View::HELP:
                if (kanban_component && kanban_component->OnEvent(event)) {
                    return true;
                }
                break;
            case View::DETAIL:
                if (detail_component && detail_component->OnEvent(event)) {
                    return true;
                }
                break;
            case View::SEARCH:
                if (search_component && search_component->OnEvent(event)) {
                    return true;
                }
                break;
        }

        // Global keybindings (only when child did not consume the event).
        if (current_view == View::KANBAN || current_view == View::HELP) {
            if (event == ftxui::Event::Character('q')) {
                screen.Exit();
                return true;
            }
            if (event == ftxui::Event::Character('/')) {
                open_search();
                return true;
            }
            if (event == ftxui::Event::Character('?')) {
                if (current_view == View::HELP) {
                    current_view = View::KANBAN;
                } else {
                    current_view = View::HELP;
                }
                return true;
            }
            if (event == ftxui::Event::Character('r') && current_view == View::KANBAN) {
                refresh_kanban();
                return true;
            }
        }

        // Allow Escape to dismiss help overlay.
        if (current_view == View::HELP && event == ftxui::Event::Escape) {
            current_view = View::KANBAN;
            return true;
        }

        return false;
    });

    screen.Loop(root_with_events);
    return 0;
}

}  // namespace tui
