#include "tui/search.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

#include "modules/issues/api.h"
#include "modules/issues/model.h"
#include "tui/theme.h"

namespace tui {

namespace {

// Truncate a string to max_len, appending "..." if truncated
std::string truncate(const std::string& s, size_t max_len) {
    if (s.size() <= max_len) return s;
    if (max_len <= 3) return s.substr(0, max_len);
    return s.substr(0, max_len - 3) + "...";
}

// Pad a string to exactly width characters (truncating if needed)
std::string pad(const std::string& s, size_t width) {
    const auto truncated = truncate(s, width);
    if (truncated.size() >= width) return truncated;
    return truncated + std::string(width - truncated.size(), ' ');
}

struct SearchState {
    std::string query;
    std::string last_searched_query;
    std::vector<Issue> results;
    int selected = 0;
    bool has_error = false;
    std::string error_msg;
    bool search_pending = false;

    void run_search() {
        if (query.empty()) {
            results.clear();
            has_error = false;
            error_msg.clear();
            last_searched_query = query;
            selected = 0;
            return;
        }
        if (query == last_searched_query) return;

        try {
            const auto conn = issues_api::search_issues(query, std::nullopt, false, 20);
            results = conn.nodes;
            has_error = false;
            error_msg.clear();
        } catch (const std::exception& e) {
            results.clear();
            has_error = true;
            error_msg = e.what();
        }

        last_searched_query = query;
        selected = 0;
    }

    void clamp_selected() {
        if (results.empty()) {
            selected = 0;
            return;
        }
        const int max_idx = static_cast<int>(results.size()) - 1;
        selected = std::clamp(selected, 0, max_idx);
    }
};

ftxui::Element render_result_row(const Issue& issue, bool is_selected) {
    const int pri = static_cast<int>(issue.priority);
    const std::string pri_str = "[" + tui::theme::priority_label(pri) + "]";
    const auto pri_col = tui::theme::priority_color(pri);

    const std::string identifier = pad(issue.identifier, 10);

    const std::string title = pad(issue.title, 42);

    const std::string state_str = [&]() -> std::string {
        if (issue.state_name.has_value()) return pad(*issue.state_name, 14);
        return pad("", 14);
    }();
    const std::string state_type = issue.state_type.value_or("");
    const auto state_col = tui::theme::state_color(state_type);

    const std::string assignee_str = [&]() -> std::string {
        if (issue.assignee_name.has_value() && !issue.assignee_name->empty()) {
            return "@" + truncate(*issue.assignee_name, 14);
        }
        return "";
    }();

    auto row = ftxui::hbox({
        ftxui::text(pri_str) | ftxui::color(pri_col),
        ftxui::text(" "),
        ftxui::text(identifier) | ftxui::color(ftxui::Color::Cyan),
        ftxui::text("  "),
        ftxui::text(title),
        ftxui::text("  "),
        ftxui::text(state_str) | ftxui::color(state_col),
        ftxui::text("  "),
        ftxui::text(assignee_str) | ftxui::color(tui::theme::dim_color()),
    });

    if (is_selected) {
        return row | ftxui::inverted;
    }
    return row;
}

ftxui::Element render_results_area(const SearchState& state) {
    if (state.has_error) {
        return ftxui::vbox({
            ftxui::text("Error: " + state.error_msg)
                | ftxui::color(ftxui::Color::Red)
                | ftxui::bold,
        });
    }

    if (!state.last_searched_query.empty() && state.results.empty()) {
        return ftxui::vbox({
            ftxui::text("No results for \"" + state.last_searched_query + "\"")
                | ftxui::color(tui::theme::dim_color()),
        });
    }

    if (state.results.empty() && state.query.empty()) {
        return ftxui::vbox({
            ftxui::text("Type a query and press Enter to search")
                | ftxui::color(tui::theme::dim_color()),
        });
    }

    ftxui::Elements rows;
    rows.reserve(state.results.size());
    for (int i = 0; i < static_cast<int>(state.results.size()); ++i) {
        rows.push_back(render_result_row(state.results[i], i == state.selected));
    }
    return ftxui::vbox(std::move(rows));
}

}  // namespace

ftxui::Component SearchOverlay(
    std::function<void(const std::string& issue_id)> on_select,
    std::function<void()> on_close
) {
    auto state = std::make_shared<SearchState>();

    auto input_component = ftxui::Input(&state->query, "Search issues...");

    auto component = ftxui::Make<ftxui::ComponentBase>();

    class SearchOverlayComponent : public ftxui::ComponentBase {
    public:
        SearchOverlayComponent(
            std::shared_ptr<SearchState> state,
            ftxui::Component input,
            std::function<void(const std::string&)> on_select,
            std::function<void()> on_close
        )
            : state_(std::move(state))
            , input_(std::move(input))
            , on_select_(std::move(on_select))
            , on_close_(std::move(on_close))
        {
            Add(input_);
        }

        ftxui::Element Render() override {
            const auto input_el = ftxui::hbox({
                ftxui::text("/ ") | ftxui::color(tui::theme::selection_color()),
                input_->Render() | ftxui::flex,
            }) | ftxui::border;

            const auto results_el = render_results_area(*state_)
                | ftxui::yframe
                | ftxui::flex;

            const int result_count = static_cast<int>(state_->results.size());
            std::string status_text;
            if (!state_->last_searched_query.empty() && !state_->has_error) {
                status_text = std::to_string(result_count)
                    + " result" + (result_count == 1 ? "" : "s")
                    + "  |  j/k: navigate  Enter: select  Esc: close";
            } else {
                status_text = "Enter: search  Esc: close";
            }
            const auto status_el = ftxui::text(status_text)
                | ftxui::color(tui::theme::dim_color());

            const auto overlay_content = ftxui::vbox({
                input_el,
                results_el | ftxui::flex,
                ftxui::separator(),
                status_el,
            });

            const auto overlay_box = overlay_content
                | ftxui::border
                | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 100)
                | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 40)
                | ftxui::clear_under
                | ftxui::center;

            return overlay_box;
        }

        bool OnEvent(ftxui::Event event) override {
            // Escape always closes
            if (event == ftxui::Event::Escape) {
                if (on_close_) on_close_();
                return true;
            }

            // Enter: if input is focused and we have a query → search
            // If results are present and something is selected → select it
            if (event == ftxui::Event::Return) {
                if (!state_->results.empty()) {
                    const int idx = state_->selected;
                    if (idx >= 0 && idx < static_cast<int>(state_->results.size())) {
                        if (on_select_) on_select_(state_->results[idx].id);
                        return true;
                    }
                }
                // No results yet: trigger search
                state_->run_search();
                return true;
            }

            // j / k navigation for results list
            if (event == ftxui::Event::Character('j') || event == ftxui::Event::ArrowDown) {
                if (!state_->results.empty()) {
                    state_->selected = std::min(
                        state_->selected + 1,
                        static_cast<int>(state_->results.size()) - 1
                    );
                    return true;
                }
            }

            if (event == ftxui::Event::Character('k') || event == ftxui::Event::ArrowUp) {
                if (!state_->results.empty()) {
                    state_->selected = std::max(state_->selected - 1, 0);
                    return true;
                }
            }

            // Delegate remaining events (typing) to the input field
            if (input_->OnEvent(event)) return true;

            return false;
        }

    private:
        std::shared_ptr<SearchState> state_;
        ftxui::Component input_;
        std::function<void(const std::string&)> on_select_;
        std::function<void()> on_close_;
    };

    return std::make_shared<SearchOverlayComponent>(
        state,
        input_component,
        std::move(on_select),
        std::move(on_close)
    );
}

}  // namespace tui
