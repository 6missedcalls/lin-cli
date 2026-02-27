#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "modules/organization/model.h"

using json = nlohmann::json;

TEST(OrganizationModel, ParsesOrganization) {
    auto j = json::parse(R"({
        "id": "org-001",
        "name": "Acme Corp",
        "urlKey": "acme",
        "logoUrl": "https://example.com/logo.png",
        "userCount": 42,
        "createdIssueCount": 1234,
        "gitBranchFormat": "{branchType}/{issueIdentifier}-{issueTitle}",
        "gitLinkbackMessagesEnabled": true,
        "samlEnabled": false,
        "scimEnabled": false,
        "trialEndsAt": "2026-03-01T00:00:00Z",
        "subscription": { "type": "plus" },
        "createdAt": "2023-01-15T10:00:00Z"
    })");

    Organization org;
    from_json(j, org);

    EXPECT_EQ(org.id, "org-001");
    EXPECT_EQ(org.name, "Acme Corp");
    EXPECT_EQ(org.url_key, "acme");
    EXPECT_EQ(org.logo_url, "https://example.com/logo.png");
    EXPECT_EQ(org.user_count, 42);
    EXPECT_EQ(org.created_issue_count, 1234);
    EXPECT_EQ(org.git_branch_format, "{branchType}/{issueIdentifier}-{issueTitle}");
    EXPECT_EQ(org.git_linkback_messages_enabled, true);
    EXPECT_EQ(org.saml_enabled, false);
    EXPECT_EQ(org.scim_enabled, false);
    EXPECT_EQ(org.trial_ends_at, "2026-03-01T00:00:00Z");
    EXPECT_EQ(org.subscription_type, "plus");
    EXPECT_EQ(org.created_at, "2023-01-15T10:00:00Z");
}

TEST(OrganizationModel, ParsesRateLimitStatus) {
    auto j = json::parse(R"({
        "requestsRemaining": 1450,
        "requestsLimit": 1500,
        "resetAt": 1740960000.0
    })");

    RateLimitStatus status;
    from_json(j, status);

    EXPECT_EQ(status.requests_remaining, 1450);
    EXPECT_EQ(status.requests_limit, 1500);
    EXPECT_DOUBLE_EQ(status.reset_at, 1740960000.0);
}

TEST(OrganizationModel, HandlesNullFields) {
    auto j = json::parse(R"({
        "id": "org-002",
        "name": "Minimal Org",
        "urlKey": "minimal",
        "logoUrl": null,
        "userCount": 5,
        "createdIssueCount": 10,
        "gitBranchFormat": null,
        "gitLinkbackMessagesEnabled": false,
        "samlEnabled": false,
        "scimEnabled": false,
        "trialEndsAt": null,
        "subscription": null,
        "createdAt": "2024-06-01T00:00:00Z"
    })");

    Organization org;
    from_json(j, org);

    EXPECT_EQ(org.id, "org-002");
    EXPECT_EQ(org.name, "Minimal Org");
    EXPECT_EQ(org.logo_url, std::nullopt);
    EXPECT_EQ(org.git_branch_format, std::nullopt);
    EXPECT_EQ(org.trial_ends_at, std::nullopt);
    EXPECT_EQ(org.subscription_type, std::nullopt);
    EXPECT_EQ(org.user_count, 5);
    EXPECT_EQ(org.created_issue_count, 10);
    EXPECT_EQ(org.git_linkback_messages_enabled, false);
    EXPECT_EQ(org.saml_enabled, false);
    EXPECT_EQ(org.scim_enabled, false);
}

TEST(OrganizationModel, ParsesOrganizationWithSamlEnabled) {
    auto j = json::parse(R"({
        "id": "org-003",
        "name": "Enterprise Org",
        "urlKey": "enterprise",
        "logoUrl": null,
        "userCount": 500,
        "createdIssueCount": 99999,
        "gitBranchFormat": null,
        "gitLinkbackMessagesEnabled": true,
        "samlEnabled": true,
        "scimEnabled": true,
        "trialEndsAt": null,
        "subscription": { "type": "enterprise" },
        "createdAt": "2022-01-01T00:00:00Z"
    })");

    Organization org;
    from_json(j, org);

    EXPECT_EQ(org.id, "org-003");
    EXPECT_EQ(org.saml_enabled, true);
    EXPECT_EQ(org.scim_enabled, true);
    EXPECT_EQ(org.subscription_type, "enterprise");
    EXPECT_EQ(org.user_count, 500);
}

TEST(RateLimitModel, HandlesZeroValues) {
    auto j = json::parse(R"({
        "requestsRemaining": 0,
        "requestsLimit": 0,
        "resetAt": 0.0
    })");

    RateLimitStatus status;
    from_json(j, status);

    EXPECT_EQ(status.requests_remaining, 0);
    EXPECT_EQ(status.requests_limit, 0);
    EXPECT_DOUBLE_EQ(status.reset_at, 0.0);
}
