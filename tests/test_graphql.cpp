#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "core/graphql.h"
#include "core/error.h"

using json = nlohmann::json;

TEST(GraphQL, BuildRequestBody) {
    GraphQLRequest req;
    req.query = "query { viewer { id } }";
    req.variables = json::object();

    auto body = build_request_body(req);
    auto parsed = json::parse(body);

    EXPECT_EQ(parsed["query"], "query { viewer { id } }");
    EXPECT_TRUE(parsed.contains("variables"));
}

TEST(GraphQL, BuildRequestBodyWithVariables) {
    GraphQLRequest req;
    req.query = "query($id: String!) { issue(id: $id) { title } }";
    req.variables = {{"id", "abc-123"}};

    auto body = build_request_body(req);
    auto parsed = json::parse(body);

    EXPECT_EQ(parsed["variables"]["id"], "abc-123");
}

TEST(GraphQL, ParseResponseSuccess) {
    auto response = R"({"data": {"viewer": {"id": "user-1", "name": "Test"}}})";
    auto data = parse_response(response);

    EXPECT_TRUE(data.contains("viewer"));
    EXPECT_EQ(data["viewer"]["id"], "user-1");
}

TEST(GraphQL, ParseResponseWithErrors) {
    auto response = R"({"errors": [{"message": "Not found"}]})";
    EXPECT_THROW(parse_response(response), LinError);
}

TEST(GraphQL, ParseResponseMalformed) {
    EXPECT_THROW(parse_response("not json at all"), LinError);
}

TEST(GraphQL, ParseResponseMissingData) {
    auto response = R"({"something": "else"})";
    EXPECT_THROW(parse_response(response), LinError);
}
