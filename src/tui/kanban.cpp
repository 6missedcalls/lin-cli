#include "tui/kanban.h"

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "modules/issues/api.h"
#include "modules/issues/model.h"
#include "modules/teams/api.h"
#include "modules/teams/model.h"
#include "tui/theme.h"

using json = nlohmann::json;

namespace tui {

namespace {

std::string truncate(const std::string& s, std::size_t max_len) {
    if (s.size() <= max_len) return s;
    if (max_len < 2) return s.substr(0, max_len);
    return s.substr(0, max_len - 1) + "\xe2\x80\xa6";
}

std::string priority_sym(int pri) {
    switch (pri) {
        case 1: return "\xe2\x97\x86";  // ◆
        case 2: return "\xe2\x96\xb2";  // ▲
        case 3: return "\xe2\x97\x8f";  // ●
        case 4: return "\xe2\x96\xbd";  // ▽
        default: return "\xe2\x97\x8b"; // ○
    }
}

// ---------------------------------------------------------------------------
// KanbanImpl
// ---------------------------------------------------------------------------

class KanbanImpl {
public:
    explicit KanbanImpl(KanbanConfig config,
                        std::function<void(const std::string&)> on_select)
        : config_(std::move(config)),
          on_select_(std::move(on_select)),
          sel_col_(0),
          sel_row_(0) {
        load_data();
    }

    ftxui::Element Render() const {
        if (!load_error_.empty()) {
            return ftxui::vbox({
                ftxui::text("Error loading kanban board:") | ftxui::bold,
                ftxui::text(load_error_) | ftxui::color(ftxui::Color::Red),
                ftxui::text(""),
                ftxui::text("Press q to quit.") | ftxui::dim,
            }) | ftxui::center;
        }

        if (columns_.empty()) {
            return ftxui::text("No workflow states found.") | ftxui::center;
        }

        ftxui::Elements cols;
        cols.reserve(columns_.size());
        for (int ci = 0; ci < static_cast<int>(columns_.size()); ++ci) {
            cols.push_back(render_column(ci));
        }

        auto board = ftxui::hbox(std::move(cols));

        auto help = ftxui::hbox({
            ftxui::text(" h/l") | ftxui::bold,
            ftxui::text(":col  "),
            ftxui::text("j/k") | ftxui::bold,
            ftxui::text(":row  "),
            ftxui::text("Enter") | ftxui::bold,
            ftxui::text(":open  "),
            ftxui::text("q") | ftxui::bold,
            ftxui::text(":quit"),
        }) | ftxui::color(ftxui::Color::GrayDark);

        return ftxui::vbox({board | ftxui::flex, ftxui::separator(), help});
    }

    bool OnEvent(ftxui::Event event) {
        if (event == ftxui::Event::Character('q')) return false;
        if (event == ftxui::Event::Character('h') || event == ftxui::Event::ArrowLeft) {
            if (sel_col_ > 0) { --sel_col_; clamp_row(); }
            return true;
        }
        if (event == ftxui::Event::Character('l') || event == ftxui::Event::ArrowRight) {
            if (sel_col_ < static_cast<int>(columns_.size()) - 1) { ++sel_col_; clamp_row(); }
            return true;
        }
        if (event == ftxui::Event::Character('k') || event == ftxui::Event::ArrowUp) {
            if (sel_row_ > 0) --sel_row_;
            return true;
        }
        if (event == ftxui::Event::Character('j') || event == ftxui::Event::ArrowDown) {
            const auto& issues = col_issues(sel_col_);
            if (sel_row_ < static_cast<int>(issues.size()) - 1) ++sel_row_;
            return true;
        }
        if (event == ftxui::Event::Return) {
            const auto& issues = col_issues(sel_col_);
            if (!issues.empty() && sel_row_ < static_cast<int>(issues.size()))
                on_select_(issues[sel_row_].id);
            return true;
        }
        return false;
    }

private:
    void load_data() {
        if (config_.team_id.empty()) {
            load_error_ = "No team_id provided.";
            return;
        }
        try {
            auto states_conn = teams_api::list_workflow_states(config_.team_id);
            auto states = states_conn.nodes;
            std::sort(states.begin(), states.end(),
                      [](const WorkflowState& a, const WorkflowState& b) {
                          return a.position < b.position;
                      });

            std::vector<WorkflowState> triage;
            for (auto& s : states) {
                if (s.type != "triage") {
                    issues_map_[s.id] = {};
                    columns_.push_back(std::move(s));
                } else {
                    triage.push_back(std::move(s));
                }
            }

            IssueListOptions opts;
            opts.first = 200;
            opts.filter = json({{"team", {{"id", {{"eq", config_.team_id}}}}}});
            auto conn = issues_api::list_issues(opts);

            for (const auto& issue : conn.nodes) {
                if (!issue.state_id.has_value()) continue;
                const std::string& sid = *issue.state_id;

                if (issues_map_.count(sid)) {
                    auto& bucket = issues_map_[sid];
                    if (static_cast<int>(bucket.size()) < config_.max_issues_per_column)
                        bucket.push_back(issue);
                    continue;
                }
                for (auto it = triage.begin(); it != triage.end(); ++it) {
                    if (it->id == sid) {
                        columns_.insert(columns_.begin(), *it);
                        issues_map_[sid] = {issue};
                        triage.erase(it);
                        break;
                    }
                }
            }
            clamp_row();
        } catch (const LinError& e) {
            load_error_ = format_error(e);
        } catch (const std::exception& e) {
            load_error_ = std::string("Error: ") + e.what();
        }
    }

    const std::vector<Issue>& col_issues(int ci) const {
        static const std::vector<Issue> empty;
        if (ci < 0 || ci >= static_cast<int>(columns_.size())) return empty;
        auto it = issues_map_.find(columns_[ci].id);
        return (it != issues_map_.end()) ? it->second : empty;
    }

    void clamp_row() {
        const auto& issues = col_issues(sel_col_);
        int max_r = static_cast<int>(issues.size()) - 1;
        if (max_r < 0) sel_row_ = 0;
        else if (sel_row_ > max_r) sel_row_ = max_r;
    }

    // -----------------------------------------------------------------------
    // Rendering
    // -----------------------------------------------------------------------

    ftxui::Element render_column(int ci) const {
        const WorkflowState& state = columns_[ci];
        bool is_active = (ci == sel_col_);
        const auto& issues = col_issues(ci);

        // Header
        auto header = ftxui::hbox({
            ftxui::text(" " + state.name) | ftxui::bold | ftxui::color(theme::state_color(state.type)),
            ftxui::text(" (" + std::to_string(issues.size()) + ") ") | ftxui::dim,
        });
        if (is_active) header = header | ftxui::underlined;

        // Card list
        ftxui::Elements card_elems;
        if (issues.empty()) {
            card_elems.push_back(ftxui::text("  (empty)") | ftxui::dim);
        } else {
            for (int ri = 0; ri < static_cast<int>(issues.size()); ++ri) {
                bool selected = is_active && (ri == sel_row_);
                card_elems.push_back(render_card(issues[ri], selected));
            }
        }

        auto card_list = ftxui::vbox(std::move(card_elems)) | ftxui::yframe;

        auto col = ftxui::vbox({
            header,
            ftxui::separator(),
            card_list | ftxui::flex,
        }) | ftxui::flex;

        return ftxui::hbox({col, ftxui::separatorLight()});
    }

    ftxui::Element render_card(const Issue& issue, bool selected) const {
        int pri = static_cast<int>(issue.priority);

        // Line 1: ◆ ENG-42  Fix the login timeout
        auto line1 = ftxui::hbox({
            ftxui::text(" " + priority_sym(pri) + " ") | ftxui::color(theme::priority_color(pri)),
            ftxui::text(issue.identifier) | ftxui::bold,
            ftxui::text("  " + truncate(issue.title, 24)),
        });

        // Line 2:    @alice · Bug · Due 2026-03-15
        std::string meta = "   ";
        if (issue.assignee_name.has_value() && !issue.assignee_name->empty()) {
            meta += "@" + truncate(*issue.assignee_name, 10);
        } else {
            meta += "unassigned";
        }
        if (!issue.label_names.empty()) {
            meta += " \xc2\xb7 " + truncate(issue.label_names[0], 10);
            if (issue.label_names.size() > 1)
                meta += " +" + std::to_string(issue.label_names.size() - 1);
        }

        auto line2 = ftxui::text(meta) | ftxui::dim;

        auto card = ftxui::vbox({line1, line2, ftxui::text("")});

        if (selected) {
            card = card | ftxui::focus | ftxui::inverted;
        }

        return card;
    }

    KanbanConfig config_;
    std::function<void(const std::string&)> on_select_;
    std::vector<WorkflowState> columns_;
    std::map<std::string, std::vector<Issue>> issues_map_;
    int sel_col_;
    int sel_row_;
    std::string load_error_;
};

}  // anonymous namespace

ftxui::Component KanbanBoard(
    KanbanConfig config,
    std::function<void(const std::string& issue_id)> on_select
) {
    auto impl = std::make_shared<KanbanImpl>(std::move(config), std::move(on_select));
    auto renderer = ftxui::Renderer([impl]() { return impl->Render(); });
    return ftxui::CatchEvent(renderer, [impl](ftxui::Event event) {
        return impl->OnEvent(event);
    });
}

}  // namespace tui
