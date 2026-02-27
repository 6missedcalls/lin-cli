#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/issues/model.h"

using json = nlohmann::json;

TEST(IssueModel, ParsesMinimalIssue) {
    auto j = json::parse(R"({
        "id": "abc-123",
        "title": "Fix bug",
        "identifier": "ENG-1",
        "number": 1,
        "priority": 2,
        "priorityLabel": "High",
        "url": "https://linear.app/team/issue/ENG-1",
        "branchName": "eng-1-fix-bug"
    })");

    Issue issue;
    from_json(j, issue);

    EXPECT_EQ(issue.id, "abc-123");
    EXPECT_EQ(issue.title, "Fix bug");
    EXPECT_EQ(issue.identifier, "ENG-1");
    EXPECT_EQ(issue.number, 1.0);
    EXPECT_EQ(issue.priority, 2.0);
    EXPECT_EQ(issue.priority_label, "High");
    EXPECT_EQ(issue.assignee_name, std::nullopt);
    EXPECT_EQ(issue.state_name, std::nullopt);
    EXPECT_EQ(issue.description, std::nullopt);
}

TEST(IssueModel, ParsesFullIssue) {
    auto j = json::parse(R"({
        "id": "abc-123",
        "title": "Fix bug",
        "identifier": "ENG-1",
        "number": 1,
        "priority": 2,
        "priorityLabel": "High",
        "url": "https://linear.app/team/issue/ENG-1",
        "branchName": "eng-1-fix-bug",
        "createdAt": "2026-01-01T00:00:00Z",
        "updatedAt": "2026-01-02T00:00:00Z",
        "description": "Detailed description here",
        "dueDate": "2026-03-15",
        "estimate": 5.0,
        "trashed": false,
        "assignee": { "id": "user-1", "displayName": "Jane Doe" },
        "state": { "id": "state-1", "name": "In Progress", "type": "started" },
        "team": { "id": "team-1", "name": "Engineering", "key": "ENG" },
        "creator": { "id": "user-2", "displayName": "John Smith" },
        "project": { "id": "proj-1", "name": "Q1 Launch" },
        "cycle": { "id": "cycle-1", "number": 5 },
        "parent": { "id": "parent-1", "identifier": "ENG-0" },
        "labels": { "nodes": [
            {"id": "l1", "name": "Bug", "color": "#FF0000"},
            {"id": "l2", "name": "P0", "color": "#FF6600"}
        ]}
    })");

    Issue issue;
    from_json(j, issue);

    EXPECT_EQ(issue.assignee_name, "Jane Doe");
    EXPECT_EQ(issue.state_name, "In Progress");
    EXPECT_EQ(issue.state_type, "started");
    EXPECT_EQ(issue.team_key, "ENG");
    EXPECT_EQ(issue.creator_name, "John Smith");
    EXPECT_EQ(issue.project_name, "Q1 Launch");
    EXPECT_EQ(issue.cycle_number, 5.0);
    EXPECT_EQ(issue.parent_identifier, "ENG-0");
    EXPECT_EQ(issue.description, "Detailed description here");
    EXPECT_EQ(issue.due_date, "2026-03-15");
    EXPECT_EQ(issue.estimate, 5.0);
    ASSERT_EQ(issue.label_names.size(), 2);
    EXPECT_EQ(issue.label_names[0], "Bug");
    EXPECT_EQ(issue.label_names[1], "P0");
}

TEST(IssueModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "abc-123",
        "title": "Fix bug",
        "identifier": "ENG-1",
        "number": 1,
        "priority": 0,
        "priorityLabel": "No priority",
        "url": "https://linear.app/...",
        "branchName": "eng-1-fix-bug",
        "assignee": null,
        "state": null,
        "team": null,
        "description": null,
        "dueDate": null,
        "labels": null
    })");

    Issue issue;
    from_json(j, issue);

    EXPECT_EQ(issue.assignee_name, std::nullopt);
    EXPECT_EQ(issue.state_name, std::nullopt);
    EXPECT_EQ(issue.team_name, std::nullopt);
    EXPECT_EQ(issue.description, std::nullopt);
    EXPECT_EQ(issue.due_date, std::nullopt);
    EXPECT_TRUE(issue.label_names.empty());
}

TEST(IssueModel, HandlesEmptyLabels) {
    auto j = json::parse(R"({
        "id": "abc-123",
        "title": "Fix bug",
        "identifier": "ENG-1",
        "number": 1,
        "priority": 0,
        "priorityLabel": "",
        "url": "",
        "branchName": "",
        "labels": { "nodes": [] }
    })");

    Issue issue;
    from_json(j, issue);

    EXPECT_TRUE(issue.label_names.empty());
    EXPECT_TRUE(issue.label_ids.empty());
}

TEST(IssueRelationModel, ParsesRelation) {
    auto j = json::parse(R"({
        "id": "rel-1",
        "createdAt": "2026-01-01T00:00:00Z",
        "type": "blocks",
        "issue": { "id": "issue-1", "identifier": "ENG-1" },
        "relatedIssue": { "id": "issue-2", "identifier": "ENG-2" }
    })");

    IssueRelation rel;
    from_json(j, rel);

    EXPECT_EQ(rel.id, "rel-1");
    EXPECT_EQ(rel.type, "blocks");
    EXPECT_EQ(rel.issue_identifier, "ENG-1");
    EXPECT_EQ(rel.related_issue_identifier, "ENG-2");
}

TEST(AttachmentModel, ParsesAttachment) {
    auto j = json::parse(R"({
        "id": "att-1",
        "createdAt": "2026-01-01T00:00:00Z",
        "title": "Screenshot",
        "url": "https://example.com/img.png",
        "sourceType": "url",
        "creator": { "id": "user-1", "displayName": "Jane" }
    })");

    Attachment att;
    from_json(j, att);

    EXPECT_EQ(att.id, "att-1");
    EXPECT_EQ(att.title, "Screenshot");
    EXPECT_EQ(att.url, "https://example.com/img.png");
    EXPECT_EQ(att.creator_name, "Jane");
}
