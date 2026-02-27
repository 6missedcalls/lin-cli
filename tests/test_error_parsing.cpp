#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "core/error.h"

using json = nlohmann::json;

TEST(LinError, ConstructsWithKindAndMessage) {
    LinError err(ErrorKind::Auth, "Invalid API key");
    EXPECT_EQ(err.kind(), ErrorKind::Auth);
    EXPECT_STREQ(err.what(), "Invalid API key");
    EXPECT_EQ(err.retry_after(), std::nullopt);
}

TEST(LinError, RetryAfter) {
    LinError err(ErrorKind::RateLimit, "Too many requests");
    err.set_retry_after(5);
    EXPECT_EQ(err.retry_after(), 5);
}

TEST(GraphQLErrors, NoErrorsDoesNotThrow) {
    auto response = json::parse(R"({
        "data": {"viewer": {"id": "123"}}
    })");
    EXPECT_NO_THROW(check_graphql_errors(response));
}

TEST(GraphQLErrors, EmptyErrorsArrayDoesNotThrow) {
    auto response = json::parse(R"({
        "data": {"viewer": {"id": "123"}},
        "errors": []
    })");
    EXPECT_NO_THROW(check_graphql_errors(response));
}

TEST(GraphQLErrors, SingleErrorThrows) {
    auto response = json::parse(R"({
        "errors": [{"message": "Not found"}]
    })");

    try {
        check_graphql_errors(response);
        FAIL() << "Expected LinError";
    } catch (const LinError& e) {
        EXPECT_EQ(e.kind(), ErrorKind::GraphQL);
        EXPECT_TRUE(std::string(e.what()).find("Not found") != std::string::npos);
    }
}

TEST(GraphQLErrors, MultipleErrorsJoined) {
    auto response = json::parse(R"({
        "errors": [
            {"message": "Error one"},
            {"message": "Error two"}
        ]
    })");

    try {
        check_graphql_errors(response);
        FAIL() << "Expected LinError";
    } catch (const LinError& e) {
        auto msg = std::string(e.what());
        EXPECT_TRUE(msg.find("Error one") != std::string::npos);
        EXPECT_TRUE(msg.find("Error two") != std::string::npos);
    }
}

TEST(HttpStatus, SuccessDoesNotThrow) {
    EXPECT_NO_THROW(check_http_status(200, "{}"));
}

TEST(HttpStatus, AuthErrorThrows) {
    try {
        check_http_status(401, "{}");
        FAIL() << "Expected LinError";
    } catch (const LinError& e) {
        EXPECT_EQ(e.kind(), ErrorKind::Auth);
    }
}

TEST(HttpStatus, NotFoundThrows) {
    try {
        check_http_status(404, "{}");
        FAIL() << "Expected LinError";
    } catch (const LinError& e) {
        EXPECT_EQ(e.kind(), ErrorKind::NotFound);
    }
}

TEST(HttpStatus, RateLimitThrows) {
    try {
        check_http_status(429, "{}");
        FAIL() << "Expected LinError";
    } catch (const LinError& e) {
        EXPECT_EQ(e.kind(), ErrorKind::RateLimit);
    }
}

TEST(FormatError, AuthError) {
    LinError err(ErrorKind::Auth, "Invalid key");
    auto msg = format_error(err);
    EXPECT_FALSE(msg.empty());
}

TEST(FormatError, RateLimitError) {
    LinError err(ErrorKind::RateLimit, "Too many requests");
    err.set_retry_after(30);
    auto msg = format_error(err);
    EXPECT_FALSE(msg.empty());
}
