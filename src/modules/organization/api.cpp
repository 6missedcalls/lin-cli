#include "modules/organization/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query strings
// ---------------------------------------------------------------------------

static const std::string ORGANIZATION_QUERY = R"gql(
query Organization {
    organization {
        id name urlKey logoUrl userCount createdIssueCount
        gitBranchFormat gitLinkbackMessagesEnabled
        samlEnabled scimEnabled trialEndsAt
        subscription { type }
        createdAt
    }
}
)gql";

static const std::string RATE_LIMIT_QUERY = R"gql(
query RateLimitStatus {
    rateLimitStatus {
        requestsRemaining requestsLimit resetAt
    }
}
)gql";

// ---------------------------------------------------------------------------
// Shared helper
// ---------------------------------------------------------------------------

static const std::string GRAPHQL_ENDPOINT = "https://api.linear.app/graphql";

static json execute_graphql(const std::string& query, const json& variables) {
    HttpClient client;
    auto api_key = get_api_key();
    auto body = build_request_body({query, variables});

    auto response = with_retry([&]() {
        auto resp = client.post(
            GRAPHQL_ENDPOINT,
            body,
            {{"Content-Type", "application/json"}, {"Authorization", api_key}}
        );
        check_http_status(resp.status_code, resp.body);
        return resp;
    });

    return parse_response(response.body);
}

// ---------------------------------------------------------------------------
// API implementations
// ---------------------------------------------------------------------------

namespace organization_api {

Organization get_organization() {
    auto data = execute_graphql(ORGANIZATION_QUERY, json::object());

    Organization org;
    from_json(data.at("organization"), org);
    return org;
}

RateLimitStatus get_rate_limit() {
    auto data = execute_graphql(RATE_LIMIT_QUERY, json::object());

    RateLimitStatus status;
    from_json(data.at("rateLimitStatus"), status);
    return status;
}

}  // namespace organization_api
