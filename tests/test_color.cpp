#include <gtest/gtest.h>
#include "core/color.h"

TEST(Color, DisabledReturnsPlainText) {
    color::set_enabled(false);
    EXPECT_EQ(color::red("hello"), "hello");
    EXPECT_EQ(color::green("world"), "world");
    EXPECT_EQ(color::bold("text"), "text");
    EXPECT_EQ(color::dim("text"), "text");
    EXPECT_EQ(color::reset(), "");
}

TEST(Color, EnabledWrapsWithAnsi) {
    color::set_enabled(true);
    auto result = color::red("hello");
    EXPECT_NE(result, "hello");
    EXPECT_TRUE(result.find("\033[") != std::string::npos);
    EXPECT_TRUE(result.find("hello") != std::string::npos);
    EXPECT_TRUE(result.find("\033[0m") != std::string::npos);
    color::set_enabled(false);  // Reset
}

TEST(Color, FromHexDisabled) {
    color::set_enabled(false);
    EXPECT_EQ(color::from_hex("#FF0000", "text"), "text");
}

TEST(Color, FromHexEnabled) {
    color::set_enabled(true);
    auto result = color::from_hex("#FF0000", "text");
    EXPECT_NE(result, "text");
    EXPECT_TRUE(result.find("text") != std::string::npos);
    color::set_enabled(false);
}

TEST(Color, PriorityColors) {
    color::set_enabled(true);
    auto urgent = color::priority(1, "Urgent");
    auto low = color::priority(4, "Low");
    // Both should be wrapped in ANSI codes
    EXPECT_NE(urgent, "Urgent");
    EXPECT_NE(low, "Low");
    // Normal priority should pass through or have minimal wrapping
    color::set_enabled(false);
}

TEST(Color, StateTypeColors) {
    color::set_enabled(true);
    auto started = color::state_type("started", "In Progress");
    auto completed = color::state_type("completed", "Done");
    EXPECT_NE(started, "In Progress");
    EXPECT_NE(completed, "Done");
    color::set_enabled(false);
}
