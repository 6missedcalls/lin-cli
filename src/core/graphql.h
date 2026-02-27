#pragma once

#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct GraphQLRequest {
    std::string query;
    json variables = json::object();
};

// Build a JSON string body for GraphQL POST: {"query": "...", "variables": {...}}
std::string build_request_body(const GraphQLRequest& request);

// Parse a GraphQL response body. Returns the "data" object.
// Throws LinError(GraphQL, ...) if response contains errors array.
// Throws LinError(Internal, ...) if response is malformed.
json parse_response(const std::string& response_body);
