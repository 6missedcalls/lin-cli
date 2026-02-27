#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "core/types.h"

struct PaginationOptions {
    int first = 50;
    std::optional<std::string> after;
    bool fetch_all = false;
    int limit = 0;  // 0 = no limit (use first per page)
};

template <typename T>
class Paginator {
public:
    using FetchFn = std::function<Connection<T>(const PaginationOptions&)>;

    Paginator(FetchFn fetch, PaginationOptions opts)
        : fetch_fn_(std::move(fetch)), opts_(std::move(opts)) {}

    std::optional<Connection<T>> next() {
        if (!has_more_) {
            return std::nullopt;
        }
        auto conn = fetch_fn_(opts_);
        if (conn.page_info.has_next_page && conn.page_info.end_cursor.has_value()) {
            opts_ = PaginationOptions{
                opts_.first,
                conn.page_info.end_cursor,
                opts_.fetch_all,
                opts_.limit
            };
        } else {
            has_more_ = false;
        }
        return conn;
    }

    std::vector<T> fetch_all() {
        std::vector<T> results;
        while (has_more_) {
            auto conn = next();
            if (!conn.has_value() || conn->nodes.empty()) {
                break;
            }
            for (auto& node : conn->nodes) {
                results.push_back(std::move(node));
            }
            if (opts_.limit > 0 && static_cast<int>(results.size()) >= opts_.limit) {
                results.resize(static_cast<size_t>(opts_.limit));
                break;
            }
            if (!opts_.fetch_all) {
                break;  // Only fetch first page unless --all
            }
        }
        return results;
    }

    bool has_next() const { return has_more_; }

private:
    FetchFn fetch_fn_;
    PaginationOptions opts_;
    bool has_more_ = true;
};
