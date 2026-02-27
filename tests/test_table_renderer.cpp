#include <gtest/gtest.h>
#include <sstream>
#include "core/output.h"
#include "core/color.h"

class TableRendererTest : public ::testing::Test {
protected:
    void SetUp() override {
        color::set_enabled(false);  // Disable colors for predictable output
    }
};

TEST_F(TableRendererTest, EmptyTable) {
    TableRenderer table({{"ID", 4, 10, false}, {"NAME", 4, 20, false}});
    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.row_count(), 0);
}

TEST_F(TableRendererTest, SingleRow) {
    TableRenderer table({{"ID", 4, 10, false}, {"NAME", 4, 20, false}});
    table.add_row({"1", "Alice"});

    EXPECT_FALSE(table.empty());
    EXPECT_EQ(table.row_count(), 1);

    std::ostringstream out;
    table.render(out);
    std::string output = out.str();

    EXPECT_NE(output.find("ID"), std::string::npos);
    EXPECT_NE(output.find("NAME"), std::string::npos);
    EXPECT_NE(output.find("Alice"), std::string::npos);
}

TEST_F(TableRendererTest, MultipleRows) {
    TableRenderer table({{"ID", 4, 10, false}, {"NAME", 4, 20, false}});
    table.add_row({"1", "Alice"});
    table.add_row({"2", "Bob"});
    table.add_row({"3", "Charlie"});

    EXPECT_EQ(table.row_count(), 3);

    std::ostringstream out;
    table.render(out);
    std::string output = out.str();

    EXPECT_NE(output.find("Alice"), std::string::npos);
    EXPECT_NE(output.find("Bob"), std::string::npos);
    EXPECT_NE(output.find("Charlie"), std::string::npos);
}

TEST_F(TableRendererTest, RenderProducesHeader) {
    TableRenderer table({{"IDENTIFIER", 6, 15, false}, {"TITLE", 5, 30, false}});
    table.add_row({"ENG-1", "Fix bug"});

    std::ostringstream out;
    table.render(out);
    std::string output = out.str();

    EXPECT_NE(output.find("IDENTIFIER"), std::string::npos);
    EXPECT_NE(output.find("TITLE"), std::string::npos);
}
