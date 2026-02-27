#include "core/graphql.h"

#include "core/error.h"

std::string build_request_body(const GraphQLRequest& request) {
    json body = {
        {"query", request.query},
        {"variables", request.variables}
    };
    return body.dump();
}

json parse_response(const std::string& response_body) {
    json response;
    try {
        response = json::parse(response_body);
    } catch (const json::parse_error& e) {
        throw LinError(ErrorKind::Internal,
            "Failed to parse GraphQL response. The server returned invalid JSON.");
    }

    check_graphql_errors(response);

    if (!response.contains("data")) {
        throw LinError(ErrorKind::Internal, "Missing data in response");
    }

    return response["data"];
}
