#include <gtest/gtest.h>
#include "core/filter.h"

TEST(FilterBuilder, EmptyFilterReturnsNull) {
    auto filter = build_issue_filter(
        std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        std::nullopt
    );
    EXPECT_TRUE(filter.is_null());
}

TEST(FilterBuilder, TeamFilter) {
    auto filter = build_issue_filter(
        "ENG", std::nullopt, std::nullopt, std::nullopt,
        std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        std::nullopt
    );
    EXPECT_FALSE(filter.is_null());
    // Should contain team key eq filter
    EXPECT_TRUE(filter.dump().find("ENG") != std::string::npos);
}

TEST(FilterBuilder, PriorityFilter) {
    auto filter = build_issue_filter(
        std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        "urgent", std::nullopt, std::nullopt, std::nullopt,
        std::nullopt
    );
    EXPECT_FALSE(filter.is_null());
}

TEST(FilterBuilder, CombinedFilters) {
    auto filter = build_issue_filter(
        "ENG", "Jane", std::nullopt, std::nullopt,
        "high", std::nullopt, std::nullopt, std::nullopt,
        std::nullopt
    );
    EXPECT_FALSE(filter.is_null());
    auto s = filter.dump();
    EXPECT_TRUE(s.find("ENG") != std::string::npos);
    EXPECT_TRUE(s.find("Jane") != std::string::npos);
}

TEST(FilterBuilder, PriorityNameToNumber) {
    EXPECT_EQ(priority_name_to_number("none"), 0);
    EXPECT_EQ(priority_name_to_number("urgent"), 1);
    EXPECT_EQ(priority_name_to_number("high"), 2);
    EXPECT_EQ(priority_name_to_number("normal"), 3);
    EXPECT_EQ(priority_name_to_number("low"), 4);
    EXPECT_EQ(priority_name_to_number("URGENT"), 1);  // case insensitive
    EXPECT_EQ(priority_name_to_number("invalid"), std::nullopt);
}

TEST(FilterBuilder, ValidStateTypes) {
    EXPECT_TRUE(is_valid_state_type("triage"));
    EXPECT_TRUE(is_valid_state_type("backlog"));
    EXPECT_TRUE(is_valid_state_type("unstarted"));
    EXPECT_TRUE(is_valid_state_type("started"));
    EXPECT_TRUE(is_valid_state_type("completed"));
    EXPECT_TRUE(is_valid_state_type("canceled"));
    EXPECT_FALSE(is_valid_state_type("invalid"));
    EXPECT_FALSE(is_valid_state_type(""));
}

TEST(FilterBuilder, ProjectFilter) {
    auto filter = build_project_filter("started", std::nullopt, std::nullopt);
    EXPECT_FALSE(filter.is_null());
}

TEST(FilterBuilder, CycleFilter) {
    auto filter = build_cycle_filter("ENG", true);
    EXPECT_FALSE(filter.is_null());
}
