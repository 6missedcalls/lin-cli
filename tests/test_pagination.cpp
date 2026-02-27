#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "core/types.h"
#include "core/paginator.h"

using json = nlohmann::json;

TEST(PageInfo, ParsesFullPageInfo) {
    auto j = json::parse(R"({
        "hasNextPage": true,
        "hasPreviousPage": false,
        "startCursor": "cursor_start",
        "endCursor": "cursor_end"
    })");

    PageInfo pi;
    from_json(j, pi);

    EXPECT_TRUE(pi.has_next_page);
    EXPECT_FALSE(pi.has_previous_page);
    EXPECT_EQ(pi.start_cursor, "cursor_start");
    EXPECT_EQ(pi.end_cursor, "cursor_end");
}

TEST(PageInfo, ParsesMinimalPageInfo) {
    auto j = json::parse(R"({
        "hasNextPage": false
    })");

    PageInfo pi;
    from_json(j, pi);

    EXPECT_FALSE(pi.has_next_page);
    EXPECT_EQ(pi.start_cursor, std::nullopt);
    EXPECT_EQ(pi.end_cursor, std::nullopt);
}

TEST(PaginationOptions, Defaults) {
    PaginationOptions opts;
    EXPECT_EQ(opts.first, 50);
    EXPECT_EQ(opts.after, std::nullopt);
    EXPECT_FALSE(opts.fetch_all);
    EXPECT_EQ(opts.limit, 0);
}

// Simple struct for testing Connection parsing
struct TestItem {
    std::string id;
    std::string name;
};

inline void from_json(const json& j, TestItem& t) {
    t.id = j.value("id", "");
    t.name = j.value("name", "");
}

TEST(Connection, ParsesWithNodes) {
    auto j = json::parse(R"({
        "nodes": [
            {"id": "1", "name": "Alpha"},
            {"id": "2", "name": "Beta"}
        ],
        "pageInfo": {
            "hasNextPage": true,
            "endCursor": "cursor_2"
        }
    })");

    Connection<TestItem> conn;
    from_json(j, conn);

    ASSERT_EQ(conn.nodes.size(), 2);
    EXPECT_EQ(conn.nodes[0].id, "1");
    EXPECT_EQ(conn.nodes[0].name, "Alpha");
    EXPECT_EQ(conn.nodes[1].name, "Beta");
    EXPECT_TRUE(conn.page_info.has_next_page);
    EXPECT_EQ(conn.page_info.end_cursor, "cursor_2");
}

TEST(Connection, ParsesEmptyNodes) {
    auto j = json::parse(R"({
        "nodes": [],
        "pageInfo": {
            "hasNextPage": false
        }
    })");

    Connection<TestItem> conn;
    from_json(j, conn);

    EXPECT_TRUE(conn.nodes.empty());
    EXPECT_FALSE(conn.page_info.has_next_page);
}

TEST(Paginator, SinglePageFetch) {
    auto fetch = [](const PaginationOptions& opts) -> Connection<TestItem> {
        Connection<TestItem> conn;
        conn.nodes = {{"1", "Alpha"}, {"2", "Beta"}};
        conn.page_info.has_next_page = false;
        return conn;
    };

    Paginator<TestItem> paginator(fetch, {});
    auto results = paginator.fetch_all();

    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].name, "Alpha");
    EXPECT_FALSE(paginator.has_next());
}

TEST(Paginator, MultiPageFetchAll) {
    int call_count = 0;
    auto fetch = [&call_count](const PaginationOptions& opts) -> Connection<TestItem> {
        Connection<TestItem> conn;
        call_count++;
        if (call_count == 1) {
            conn.nodes = {{"1", "Alpha"}};
            conn.page_info.has_next_page = true;
            conn.page_info.end_cursor = "cursor_1";
        } else {
            conn.nodes = {{"2", "Beta"}};
            conn.page_info.has_next_page = false;
        }
        return conn;
    };

    PaginationOptions opts;
    opts.fetch_all = true;
    Paginator<TestItem> paginator(fetch, opts);
    auto results = paginator.fetch_all();

    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(call_count, 2);
}

TEST(Paginator, RespectsLimit) {
    int call_count = 0;
    auto fetch = [&call_count](const PaginationOptions& opts) -> Connection<TestItem> {
        Connection<TestItem> conn;
        call_count++;
        conn.nodes = {{"1", "A"}, {"2", "B"}, {"3", "C"}};
        conn.page_info.has_next_page = true;
        conn.page_info.end_cursor = "cursor";
        return conn;
    };

    PaginationOptions opts;
    opts.fetch_all = true;
    opts.limit = 2;
    Paginator<TestItem> paginator(fetch, opts);
    auto results = paginator.fetch_all();

    ASSERT_EQ(results.size(), 2);
}
