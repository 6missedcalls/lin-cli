#pragma once

#include <string>
#include <ftxui/screen/color.hpp>

namespace tui {
namespace theme {

// Map priority levels to FTXUI colors
inline ftxui::Color priority_color(int priority) {
    switch (priority) {
        case 1: return ftxui::Color::Red;        // Urgent
        case 2: return ftxui::Color::RGB(255, 165, 0); // High - orange
        case 3: return ftxui::Color::Default;     // Normal
        case 4: return ftxui::Color::GrayDark;    // Low
        default: return ftxui::Color::GrayDark;   // No priority
    }
}

// Map workflow state types to FTXUI colors
inline ftxui::Color state_color(const std::string& state_type) {
    if (state_type == "started") return ftxui::Color::Yellow;
    if (state_type == "completed") return ftxui::Color::Green;
    if (state_type == "canceled") return ftxui::Color::GrayDark;
    if (state_type == "triage") return ftxui::Color::Red;
    if (state_type == "backlog") return ftxui::Color::GrayLight;
    return ftxui::Color::Default;  // unstarted
}

// Map project health to FTXUI colors
inline ftxui::Color health_color(const std::string& health) {
    if (health == "onTrack") return ftxui::Color::Green;
    if (health == "atRisk") return ftxui::Color::Yellow;
    if (health == "offTrack") return ftxui::Color::Red;
    return ftxui::Color::Default;
}

// Priority label
inline std::string priority_label(int priority) {
    switch (priority) {
        case 0: return "---";
        case 1: return "URG";
        case 2: return "HI ";
        case 3: return "NRM";
        case 4: return "LOW";
        default: return "---";
    }
}

// Kanban card border style by state type
inline ftxui::Color card_border_color(const std::string& state_type) {
    return state_color(state_type);
}

// Column header style by state type
inline ftxui::Color column_header_color(const std::string& state_type) {
    return state_color(state_type);
}

// Selected item highlight
inline ftxui::Color selection_color() {
    return ftxui::Color::Cyan;
}

// Dim color for secondary info
inline ftxui::Color dim_color() {
    return ftxui::Color::GrayDark;
}

// Accent color for actions/links
inline ftxui::Color accent_color() {
    return ftxui::Color::Cyan;
}

}  // namespace theme
}  // namespace tui
