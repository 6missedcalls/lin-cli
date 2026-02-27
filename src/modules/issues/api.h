#pragma once

#include <optional>
#include <string>
#include <vector>

#include "core/types.h"
#include "modules/issues/model.h"

struct IssueListOptions {
    int first = 50;
    std::optional<std::string> after;
    nlohmann::json filter = nullptr;  // IssueFilter JSON or null
    std::optional<std::string> order_by;
};

struct IssueCreateInput {
    std::string title;
    std::string team_id;
    std::optional<std::string> description;
    std::optional<std::string> assignee_id;
    std::optional<int> priority;
    std::optional<std::string> state_id;
    std::optional<std::string> project_id;
    std::optional<std::string> cycle_id;
    std::optional<std::string> parent_id;
    std::optional<double> estimate;
    std::optional<std::string> due_date;
    std::vector<std::string> label_ids;
};

struct IssueUpdateInput {
    std::optional<std::string> title;
    std::optional<std::string> description;
    std::optional<std::string> assignee_id;
    std::optional<int> priority;
    std::optional<std::string> state_id;
    std::optional<std::string> project_id;
    std::optional<std::string> cycle_id;
    std::optional<std::string> parent_id;
    std::optional<double> estimate;
    std::optional<std::string> due_date;
};

namespace issues_api {

// List issues with filtering and pagination
Connection<Issue> list_issues(const IssueListOptions& opts);

// Get single issue by ID or identifier
Issue get_issue(const std::string& id_or_identifier);

// Search issues
Connection<Issue> search_issues(
    const std::string& term,
    const std::optional<std::string>& team_id = std::nullopt,
    bool include_comments = false,
    int limit = 20
);

// CRUD
Issue create_issue(const IssueCreateInput& input);
Issue update_issue(const std::string& id, const IssueUpdateInput& input);
void delete_issue(const std::string& id, bool permanently = false);
void archive_issue(const std::string& id);
void unarchive_issue(const std::string& id);

// Labels
void add_label(const std::string& issue_id, const std::string& label_id);
void remove_label(const std::string& issue_id, const std::string& label_id);

// Subscribe
void subscribe(const std::string& issue_id);
void unsubscribe(const std::string& issue_id);

// Relations
IssueRelation create_relation(const std::string& issue_id, const std::string& related_id, const std::string& type);
void delete_relation(const std::string& relation_id);

// Bulk
int bulk_update(const std::vector<std::string>& ids, const IssueUpdateInput& input);

// Get viewer (current user)
struct ViewerInfo {
    std::string id;
    std::string name;
    std::string email;
    std::string display_name;
};
ViewerInfo get_viewer();

}  // namespace issues_api
