#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers that mirror what commands.cpp does when parsing search results
// ---------------------------------------------------------------------------

namespace {

// Extract issue nodes from a searchIssues response payload
std::vector<json> extract_issue_nodes(const json& data) {
    std::vector<json> result;
    if (!data.contains("searchIssues")) return result;
    const auto& si = data["searchIssues"];
    if (!si.contains("nodes") || !si["nodes"].is_array()) return result;
    for (const auto& node : si["nodes"]) {
        result.push_back(node);
    }
    return result;
}

// Extract project nodes from a projectSearch response payload
std::vector<json> extract_project_nodes(const json& data) {
    std::vector<json> result;
    if (!data.contains("projectSearch")) return result;
    const auto& ps = data["projectSearch"];
    if (!ps.contains("nodes") || !ps["nodes"].is_array()) return result;
    for (const auto& node : ps["nodes"]) {
        result.push_back(node);
    }
    return result;
}

// Extract document nodes from a searchDocuments response payload
std::vector<json> extract_document_nodes(const json& data) {
    std::vector<json> result;
    if (!data.contains("searchDocuments")) return result;
    const auto& sd = data["searchDocuments"];
    if (!sd.contains("nodes") || !sd["nodes"].is_array()) return result;
    for (const auto& node : sd["nodes"]) {
        result.push_back(node);
    }
    return result;
}

// Build a grouped JSON result from a cross-type search response (mirrors render_all_json)
json build_grouped_result(const json& data) {
    json result = json::object();
    if (data.contains("searchIssues")) {
        result["issues"] = data["searchIssues"].value("nodes", json::array());
    }
    if (data.contains("projectSearch")) {
        result["projects"] = data["projectSearch"].value("nodes", json::array());
    }
    if (data.contains("searchDocuments")) {
        result["documents"] = data["searchDocuments"].value("nodes", json::array());
    }
    return result;
}

}  // namespace

// ---------------------------------------------------------------------------
// Tests: ParsesSearchResponse
// ---------------------------------------------------------------------------

TEST(SearchResponse, ParsesIssueSearchResponse) {
    auto data = json::parse(R"({
        "searchIssues": {
            "nodes": [
                {
                    "id": "issue-1",
                    "identifier": "ENG-42",
                    "title": "Fix authentication bug",
                    "priority": 1,
                    "priorityLabel": "Urgent",
                    "url": "https://linear.app/team/issue/ENG-42",
                    "branchName": "eng-42-fix-auth",
                    "createdAt": "2026-02-01T10:00:00Z",
                    "updatedAt": "2026-02-10T12:00:00Z",
                    "state": { "id": "state-1", "name": "In Progress", "type": "started" },
                    "assignee": { "id": "user-1", "displayName": "Jane Doe" },
                    "team": { "id": "team-1", "name": "Engineering", "key": "ENG" }
                },
                {
                    "id": "issue-2",
                    "identifier": "ENG-99",
                    "title": "Update login flow",
                    "priority": 2,
                    "priorityLabel": "High",
                    "url": "https://linear.app/team/issue/ENG-99",
                    "branchName": "eng-99-login",
                    "createdAt": "2026-01-15T08:00:00Z",
                    "updatedAt": "2026-01-20T09:00:00Z",
                    "state": { "id": "state-2", "name": "Todo", "type": "unstarted" },
                    "assignee": null,
                    "team": { "id": "team-1", "name": "Engineering", "key": "ENG" }
                }
            ],
            "pageInfo": { "hasNextPage": false, "endCursor": null }
        }
    })");

    auto nodes = extract_issue_nodes(data);

    ASSERT_EQ(nodes.size(), 2);

    // First issue
    EXPECT_EQ(nodes[0]["id"].get<std::string>(), "issue-1");
    EXPECT_EQ(nodes[0]["identifier"].get<std::string>(), "ENG-42");
    EXPECT_EQ(nodes[0]["title"].get<std::string>(), "Fix authentication bug");
    EXPECT_EQ(nodes[0]["priority"].get<double>(), 1.0);
    EXPECT_EQ(nodes[0]["priorityLabel"].get<std::string>(), "Urgent");
    EXPECT_EQ(nodes[0]["state"]["name"].get<std::string>(), "In Progress");
    EXPECT_EQ(nodes[0]["state"]["type"].get<std::string>(), "started");
    EXPECT_EQ(nodes[0]["assignee"]["displayName"].get<std::string>(), "Jane Doe");
    EXPECT_EQ(nodes[0]["team"]["key"].get<std::string>(), "ENG");

    // Second issue — null assignee
    EXPECT_EQ(nodes[1]["identifier"].get<std::string>(), "ENG-99");
    EXPECT_TRUE(nodes[1]["assignee"].is_null());
    EXPECT_EQ(nodes[1]["state"]["type"].get<std::string>(), "unstarted");
}

TEST(SearchResponse, ParsesProjectSearchResponse) {
    auto data = json::parse(R"({
        "projectSearch": {
            "nodes": [
                {
                    "id": "proj-1",
                    "name": "Q1 Launch",
                    "slugId": "q1-launch",
                    "url": "https://linear.app/team/project/q1-launch",
                    "priority": 1,
                    "priorityLabel": "Urgent",
                    "progress": 0.65,
                    "health": "onTrack",
                    "status": { "id": "status-1", "name": "In Progress", "type": "started" },
                    "lead": { "id": "user-2", "displayName": "Alice" },
                    "createdAt": "2026-01-01T00:00:00Z",
                    "updatedAt": "2026-02-15T14:00:00Z"
                }
            ],
            "pageInfo": { "hasNextPage": false, "endCursor": null }
        }
    })");

    auto nodes = extract_project_nodes(data);

    ASSERT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]["id"].get<std::string>(), "proj-1");
    EXPECT_EQ(nodes[0]["name"].get<std::string>(), "Q1 Launch");
    EXPECT_NEAR(nodes[0]["progress"].get<double>(), 0.65, 0.001);
    EXPECT_EQ(nodes[0]["health"].get<std::string>(), "onTrack");
    EXPECT_EQ(nodes[0]["status"]["name"].get<std::string>(), "In Progress");
    EXPECT_EQ(nodes[0]["lead"]["displayName"].get<std::string>(), "Alice");
}

TEST(SearchResponse, ParsesDocumentSearchResponse) {
    auto data = json::parse(R"({
        "searchDocuments": {
            "nodes": [
                {
                    "id": "doc-1",
                    "title": "Authentication Design Doc",
                    "slugId": "auth-design",
                    "url": "https://linear.app/team/document/auth-design",
                    "createdAt": "2026-01-10T09:00:00Z",
                    "updatedAt": "2026-02-20T11:00:00Z",
                    "creator": { "id": "user-3", "displayName": "Bob" },
                    "project": { "id": "proj-1", "name": "Q1 Launch" }
                }
            ],
            "pageInfo": { "hasNextPage": false, "endCursor": null }
        }
    })");

    auto nodes = extract_document_nodes(data);

    ASSERT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]["id"].get<std::string>(), "doc-1");
    EXPECT_EQ(nodes[0]["title"].get<std::string>(), "Authentication Design Doc");
    EXPECT_EQ(nodes[0]["creator"]["displayName"].get<std::string>(), "Bob");
    EXPECT_EQ(nodes[0]["project"]["name"].get<std::string>(), "Q1 Launch");
}

TEST(SearchResponse, ParsesCrossTypeSearchResponse) {
    auto data = json::parse(R"({
        "searchIssues": {
            "nodes": [
                {
                    "id": "issue-3",
                    "identifier": "API-5",
                    "title": "Auth token expiry",
                    "priority": 0,
                    "priorityLabel": "No priority",
                    "url": "https://linear.app/api/issue/API-5",
                    "branchName": "api-5-auth-token",
                    "createdAt": "2026-02-10T08:00:00Z",
                    "updatedAt": "2026-02-11T10:00:00Z",
                    "state": { "id": "state-3", "name": "Backlog", "type": "backlog" },
                    "assignee": null,
                    "team": { "id": "team-2", "name": "API Team", "key": "API" }
                }
            ],
            "pageInfo": { "hasNextPage": false, "endCursor": null }
        },
        "searchDocuments": {
            "nodes": [
                {
                    "id": "doc-2",
                    "title": "API Auth Spec",
                    "slugId": "api-auth-spec",
                    "url": "https://linear.app/api/document/api-auth-spec",
                    "createdAt": "2026-01-20T12:00:00Z",
                    "updatedAt": "2026-02-18T08:00:00Z",
                    "creator": { "id": "user-4", "displayName": "Carol" },
                    "project": null
                }
            ],
            "pageInfo": { "hasNextPage": false, "endCursor": null }
        }
    })");

    auto issue_nodes = extract_issue_nodes(data);
    auto doc_nodes   = extract_document_nodes(data);

    ASSERT_EQ(issue_nodes.size(), 1);
    EXPECT_EQ(issue_nodes[0]["identifier"].get<std::string>(), "API-5");
    EXPECT_EQ(issue_nodes[0]["team"]["key"].get<std::string>(), "API");

    ASSERT_EQ(doc_nodes.size(), 1);
    EXPECT_EQ(doc_nodes[0]["title"].get<std::string>(), "API Auth Spec");
    EXPECT_TRUE(doc_nodes[0]["project"].is_null());
}

TEST(SearchResponse, BuildsGroupedJsonResult) {
    auto data = json::parse(R"({
        "searchIssues": {
            "nodes": [
                { "id": "i1", "identifier": "T-1", "title": "Issue one" }
            ]
        },
        "projectSearch": {
            "nodes": [
                { "id": "p1", "name": "Project Alpha" }
            ]
        },
        "searchDocuments": {
            "nodes": [
                { "id": "d1", "title": "Doc Gamma" }
            ]
        }
    })");

    auto grouped = build_grouped_result(data);

    ASSERT_TRUE(grouped.contains("issues"));
    ASSERT_TRUE(grouped.contains("projects"));
    ASSERT_TRUE(grouped.contains("documents"));

    ASSERT_EQ(grouped["issues"].size(), 1);
    EXPECT_EQ(grouped["issues"][0]["id"].get<std::string>(), "i1");

    ASSERT_EQ(grouped["projects"].size(), 1);
    EXPECT_EQ(grouped["projects"][0]["name"].get<std::string>(), "Project Alpha");

    ASSERT_EQ(grouped["documents"].size(), 1);
    EXPECT_EQ(grouped["documents"][0]["title"].get<std::string>(), "Doc Gamma");
}

TEST(SearchResponse, HandlesEmptyResults) {
    auto data = json::parse(R"({
        "searchIssues": {
            "nodes": [],
            "pageInfo": { "hasNextPage": false, "endCursor": null }
        },
        "searchDocuments": {
            "nodes": [],
            "pageInfo": { "hasNextPage": false, "endCursor": null }
        }
    })");

    auto issue_nodes = extract_issue_nodes(data);
    auto doc_nodes   = extract_document_nodes(data);

    EXPECT_TRUE(issue_nodes.empty());
    EXPECT_TRUE(doc_nodes.empty());
}

TEST(SearchResponse, HandlesPageInfoPagination) {
    auto data = json::parse(R"({
        "searchIssues": {
            "nodes": [
                {
                    "id": "issue-a",
                    "identifier": "ENG-100",
                    "title": "Paginated result",
                    "priority": 3,
                    "priorityLabel": "Normal",
                    "url": "https://linear.app/team/issue/ENG-100",
                    "branchName": "eng-100-paginated",
                    "createdAt": "2026-02-01T00:00:00Z",
                    "updatedAt": "2026-02-01T00:00:00Z",
                    "state": null,
                    "assignee": null,
                    "team": null
                }
            ],
            "pageInfo": {
                "hasNextPage": true,
                "endCursor": "cursor-abc123"
            }
        }
    })");

    const auto& si = data["searchIssues"];
    EXPECT_TRUE(si["pageInfo"]["hasNextPage"].get<bool>());
    EXPECT_EQ(si["pageInfo"]["endCursor"].get<std::string>(), "cursor-abc123");

    auto nodes = extract_issue_nodes(data);
    ASSERT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]["identifier"].get<std::string>(), "ENG-100");
}
