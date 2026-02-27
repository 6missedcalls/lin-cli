#include "tui/issue_detail.h"

#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

#include "modules/comments/api.h"
#include "modules/comments/model.h"
#include "modules/issues/api.h"
#include "modules/issues/model.h"
#include "modules/teams/api.h"
#include "tui/picker.h"
#include "tui/theme.h"

using namespace ftxui;

namespace tui {

namespace {

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
std::string format_timestamp(const std::string& ts) {
    if (ts.size() < 10) return ts;
    std::string result = ts.substr(0, 10);
    if (ts.size() >= 16 && ts[10] == 'T') {
        result += ' ';
        result += ts.substr(11, 5);
    }
    return result;
}

std::string join(const std::vector<std::string>& parts, const std::string& sep) {
    std::string result;
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) result += sep;
        result += parts[i];
    }
    return result;
}

Element meta_row(const std::string& label, Element value_elem) {
    return hbox({
        text(label) | color(tui::theme::dim_color()) | size(WIDTH, EQUAL, 14),
        value_elem,
    });
}

Element meta_row_text(const std::string& label, const std::string& value) {
    return meta_row(label, text(value));
}

Element render_comment(const Comment& c) {
    const std::string author = c.user_name.value_or("Unknown");
    const std::string date = format_timestamp(c.created_at);
    Element header = hbox({
        text(author) | bold,
        text("  "),
        text(date) | color(tui::theme::dim_color()),
    });
    return vbox({
        header,
        separator(),
        paragraphAlignLeft(c.body),
    }) | border | color(Color::Default);
}

// ---------------------------------------------------------------------------
// Overlay mode
// ---------------------------------------------------------------------------
enum class Overlay { NONE, PRIORITY, STATE, ASSIGN };

// ---------------------------------------------------------------------------
// DetailImpl
// ---------------------------------------------------------------------------
class DetailImpl : public ComponentBase {
public:
    DetailImpl(
        const std::string& issue_id,
        std::function<void()> on_close,
        std::function<void()> on_refresh
    )
        : issue_id_(issue_id),
          on_close_(std::move(on_close)),
          on_refresh_(std::move(on_refresh)),
          scroll_y_(0),
          load_error_(false),
          dirty_(false),
          overlay_(Overlay::NONE),
          picker_sel_(0)
    {
        fetch_data();
    }

    void fetch_data() {
        try {
            issue_ = issues_api::get_issue(issue_id_);
        } catch (const std::exception& e) {
            load_error_ = true;
            error_message_ = std::string("Failed to load issue: ") + e.what();
            return;
        }
        try {
            auto conn = comments_api::list_comments(issue_id_, 20);
            comments_ = std::move(conn.nodes);
        } catch (const std::exception& e) {
            comment_load_warning_ = std::string("Could not load comments: ") + e.what();
        }
    }

    Element Render() final {
        if (load_error_) return render_error_view();

        Element detail = render_detail_view();

        if (overlay_ != Overlay::NONE) {
            Element picker = render_picker_overlay();
            return dbox({detail, picker});
        }
        return detail;
    }

    bool OnEvent(Event event) final {
        // When a picker overlay is open, it handles events exclusively
        if (overlay_ != Overlay::NONE) {
            return handle_picker_event(event);
        }
        return handle_detail_event(event);
    }

private:
    // -----------------------------------------------------------------------
    // Detail-mode event handling
    // -----------------------------------------------------------------------
    bool handle_detail_event(Event event) {
        if (event == Event::ArrowDown || event == Event::Character('j')) {
            scroll_y_ += 1;
            return true;
        }
        if (event == Event::ArrowUp || event == Event::Character('k')) {
            if (scroll_y_ > 0) scroll_y_ -= 1;
            return true;
        }
        if (event == Event::PageDown) { scroll_y_ += 10; return true; }
        if (event == Event::PageUp) {
            scroll_y_ = (scroll_y_ >= 10) ? scroll_y_ - 10 : 0;
            return true;
        }
        if (event == Event::Escape || event == Event::Character('q')) {
            if (dirty_ && on_refresh_) {
                on_refresh_();
            } else if (on_close_) {
                on_close_();
            }
            return true;
        }
        if (event == Event::Character('p')) {
            open_priority_picker();
            return true;
        }
        if (event == Event::Character('s')) {
            open_state_picker();
            return true;
        }
        if (event == Event::Character('a')) {
            open_assign_picker();
            return true;
        }
        return false;
    }

    // -----------------------------------------------------------------------
    // Picker-mode event handling
    // -----------------------------------------------------------------------
    bool handle_picker_event(Event event) {
        if (event == Event::Escape) {
            overlay_ = Overlay::NONE;
            return true;
        }
        if (event == Event::ArrowDown || event == Event::Character('j')) {
            picker_sel_ = clamp_picker_selection(picker_sel_ + 1, picker_items_.size());
            return true;
        }
        if (event == Event::ArrowUp || event == Event::Character('k')) {
            picker_sel_ = clamp_picker_selection(picker_sel_ - 1, picker_items_.size());
            return true;
        }
        if (event == Event::Return) {
            apply_picker_selection();
            return true;
        }
        return true;  // swallow all other keys while picker is open
    }

    // -----------------------------------------------------------------------
    // Open pickers
    // -----------------------------------------------------------------------
    void open_priority_picker() {
        try {
            auto values = issues_api::list_priority_values();
            picker_items_ = build_priority_picker_items(values);
        } catch (const std::exception&) {
            picker_items_ = build_priority_picker_items();
        }
        picker_title_ = "Set Priority";
        // Pre-select current priority
        picker_sel_ = 0;
        int current_pri = static_cast<int>(issue_.priority);
        for (int i = 0; i < static_cast<int>(picker_items_.size()); ++i) {
            if (picker_items_[i].value == std::to_string(current_pri)) {
                picker_sel_ = i;
                break;
            }
        }
        overlay_ = Overlay::PRIORITY;
    }

    void open_state_picker() {
        std::string team_id = issue_.team_id.value_or("");
        if (team_id.empty()) {
            status_message_ = "Cannot load states: no team_id";
            return;
        }
        try {
            auto conn = teams_api::list_workflow_states(team_id);
            auto states = conn.nodes;
            std::sort(states.begin(), states.end(),
                      [](const WorkflowState& a, const WorkflowState& b) {
                          return a.position < b.position;
                      });
            picker_items_ = build_state_picker_items(states);
        } catch (const std::exception& e) {
            status_message_ = std::string("Failed to load states: ") + e.what();
            return;
        }
        picker_title_ = "Set State";
        // Pre-select current state
        picker_sel_ = 0;
        for (int i = 0; i < static_cast<int>(picker_items_.size()); ++i) {
            if (picker_items_[i].value == issue_.state_id.value_or("")) {
                picker_sel_ = i;
                break;
            }
        }
        overlay_ = Overlay::STATE;
    }

    void open_assign_picker() {
        std::string team_id = issue_.team_id.value_or("");
        if (team_id.empty()) {
            status_message_ = "Cannot load members: no team_id";
            return;
        }
        try {
            auto members = teams_api::list_members(team_id);
            picker_items_ = build_assign_picker_items(members);
        } catch (const std::exception& e) {
            status_message_ = std::string("Failed to load members: ") + e.what();
            return;
        }
        picker_title_ = "Assign To";
        // Pre-select current assignee (index 0 = Unassign)
        picker_sel_ = 0;
        for (int i = 0; i < static_cast<int>(picker_items_.size()); ++i) {
            if (picker_items_[i].value == issue_.assignee_id.value_or("")) {
                picker_sel_ = i;
                break;
            }
        }
        overlay_ = Overlay::ASSIGN;
    }

    // -----------------------------------------------------------------------
    // Apply the current picker selection via API call
    // -----------------------------------------------------------------------
    void apply_picker_selection() {
        if (picker_sel_ < 0 || picker_sel_ >= static_cast<int>(picker_items_.size())) {
            overlay_ = Overlay::NONE;
            return;
        }

        const auto& selected = picker_items_[picker_sel_];
        try {
            switch (overlay_) {
                case Overlay::PRIORITY: {
                    int pri = std::stoi(selected.value);
                    auto input = make_priority_update(pri);
                    issue_ = issues_api::update_issue(issue_id_, input);
                    break;
                }
                case Overlay::STATE: {
                    auto input = make_state_update(selected.value);
                    issue_ = issues_api::update_issue(issue_id_, input);
                    break;
                }
                case Overlay::ASSIGN: {
                    auto input = make_assign_update(selected.value);
                    issue_ = issues_api::update_issue(issue_id_, input);
                    break;
                }
                case Overlay::NONE:
                    break;
            }
            status_message_ = "Updated " + issue_.identifier;
            dirty_ = true;
        } catch (const std::exception& e) {
            status_message_ = std::string("Update failed: ") + e.what();
        }
        overlay_ = Overlay::NONE;
    }

    // -----------------------------------------------------------------------
    // Render: picker overlay
    // -----------------------------------------------------------------------
    Element render_picker_overlay() const {
        Elements rows;
        rows.push_back(text(" " + picker_title_ + " ") | bold | center);
        rows.push_back(separator());

        for (int i = 0; i < static_cast<int>(picker_items_.size()); ++i) {
            const auto& item = picker_items_[i];
            auto row = text("  " + item.label);
            if (i == picker_sel_) {
                row = text("> " + item.label) | bold | inverted;
            }
            rows.push_back(row);
        }

        rows.push_back(separator());
        rows.push_back(text(" j/k:move  Enter:select  Esc:cancel ") | dim);

        return vbox(std::move(rows))
            | border
            | size(WIDTH, LESS_THAN, 40)
            | center
            | clear_under;
    }

    // -----------------------------------------------------------------------
    // Render: detail view
    // -----------------------------------------------------------------------
    Element render_detail_view() const {
        Elements top_parts = {
            render_header_bar(),
            render_scrollable_body() | flex,
        };

        if (!status_message_.empty()) {
            top_parts.push_back(separator());
            top_parts.push_back(
                text(" " + status_message_) | color(Color::Yellow)
            );
        }

        return vbox(std::move(top_parts)) | border;
    }

    Element render_header_bar() const {
        const int priority = static_cast<int>(issue_.priority);
        Element identifier_elem =
            text(issue_.identifier) | bold | color(tui::theme::priority_color(priority));
        Element title_elem = text("  " + issue_.title) | bold;

        return hbox({
            identifier_elem,
            title_elem,
            filler(),
            text("[q] back  [j/k] scroll  [a] assign  [s] state  [p] priority")
                | color(tui::theme::dim_color()),
        }) | size(HEIGHT, EQUAL, 1);
    }

    Element render_scrollable_body() const {
        Elements sections;

        sections.push_back(render_metadata());
        sections.push_back(separator());

        if (issue_.description.has_value() && !issue_.description->empty()) {
            sections.push_back(vbox({
                text("Description") | bold | underlined,
                text(""),
                paragraphAlignLeft(*issue_.description),
            }));
            sections.push_back(separator());
        }

        if (comment_load_warning_.has_value()) {
            sections.push_back(
                text("Warning: " + *comment_load_warning_) | color(Color::Yellow)
            );
            sections.push_back(separator());
        }

        if (!comments_.empty()) {
            sections.push_back(render_comments_section());
            sections.push_back(separator());
        }

        sections.push_back(render_footer());

        Element body = vbox(std::move(sections)) | focusPositionRelative(0, 0);

        Elements with_offset;
        if (scroll_y_ > 0) {
            with_offset.push_back(text("") | size(HEIGHT, EQUAL, scroll_y_));
        }
        with_offset.push_back(body | flex);

        return vbox(std::move(with_offset)) | yframe | reflect(scroll_box_);
    }

    Element render_metadata() const {
        Elements rows;

        const std::string state_name = issue_.state_name.value_or("\xe2\x80\x94");
        const std::string state_type = issue_.state_type.value_or("");
        rows.push_back(meta_row("State:", text(state_name) | color(tui::theme::state_color(state_type))));

        const int priority = static_cast<int>(issue_.priority);
        rows.push_back(meta_row("Priority:", text(issue_.priority_label) | color(tui::theme::priority_color(priority))));

        rows.push_back(meta_row_text("Assignee:", issue_.assignee_name.value_or("Unassigned")));
        rows.push_back(meta_row_text("Creator:", issue_.creator_name.value_or("\xe2\x80\x94")));
        rows.push_back(meta_row_text("Team:", issue_.team_name.value_or("\xe2\x80\x94")));

        if (issue_.project_name.has_value())
            rows.push_back(meta_row_text("Project:", *issue_.project_name));
        if (issue_.due_date.has_value())
            rows.push_back(meta_row_text("Due Date:", *issue_.due_date));
        if (issue_.estimate.has_value()) {
            std::ostringstream oss;
            oss << *issue_.estimate;
            rows.push_back(meta_row_text("Estimate:", oss.str()));
        }
        if (!issue_.label_names.empty())
            rows.push_back(meta_row_text("Labels:", join(issue_.label_names, ", ")));

        rows.push_back(meta_row_text("Created:", format_timestamp(issue_.created_at)));
        rows.push_back(meta_row_text("Updated:", format_timestamp(issue_.updated_at)));

        return vbox(std::move(rows));
    }

    Element render_comments_section() const {
        std::ostringstream header_text;
        header_text << "Comments (" << comments_.size() << ")";
        Elements comment_elems;
        comment_elems.push_back(text(header_text.str()) | bold | underlined);
        comment_elems.push_back(text(""));
        for (const auto& c : comments_) {
            comment_elems.push_back(render_comment(c));
            comment_elems.push_back(text(""));
        }
        return vbox(std::move(comment_elems));
    }

    Element render_footer() const {
        return hbox({
            text("URL: ") | color(tui::theme::dim_color()),
            text(issue_.url) | color(tui::theme::accent_color()),
        });
    }

    Element render_error_view() const {
        return vbox({
            text("Error") | bold | color(Color::Red),
            separator(),
            paragraphAlignLeft(error_message_),
            separator(),
            text("[q/Esc] back") | color(tui::theme::dim_color()),
        }) | border;
    }

    // -----------------------------------------------------------------------
    // Data members
    // -----------------------------------------------------------------------
    std::string issue_id_;
    std::function<void()> on_close_;
    std::function<void()> on_refresh_;

    Issue issue_;
    std::vector<Comment> comments_;

    int scroll_y_;
    bool load_error_;
    bool dirty_;
    std::string error_message_;
    std::optional<std::string> comment_load_warning_;
    std::string status_message_;

    // Picker overlay state
    Overlay overlay_;
    std::vector<PickerItem> picker_items_;
    int picker_sel_;
    std::string picker_title_;

    mutable Box scroll_box_;
};

}  // namespace

ftxui::Component IssueDetailPanel(
    const std::string& issue_id,
    std::function<void()> on_close,
    std::function<void()> on_refresh
) {
    return std::make_shared<DetailImpl>(issue_id, std::move(on_close), std::move(on_refresh));
}

}  // namespace tui
