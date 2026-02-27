#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace search_api {

// Perform a semantic cross-type search using Linear's semanticSearch endpoint.
// Returns the raw JSON data node so commands.cpp can format grouped results.
// The response contains semanticSearch.archivePayload nodes with:
//   identifier, title, __typename
json search_all(const std::string& query, int limit = 20);

// Search issues by term, optionally filtered to a team.
// Returns raw JSON data node (searchIssues with nodes and pageInfo).
json search_issues(
    const std::string& term,
    const std::optional<std::string>& team_key = std::nullopt,
    int limit = 20
);

// Search projects by term.
// Returns raw JSON data node (projectSearch with nodes and pageInfo).
json search_projects(const std::string& term, int limit = 20);

// Search documents by term.
// Returns raw JSON data node (documentSearch with nodes and pageInfo).
json search_documents(const std::string& term, int limit = 20);

}  // namespace search_api
