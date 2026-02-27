#include "modules/notifications/api.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string NOTIFICATIONS_LIST_QUERY = R"gql(
query NotificationsList($first: Int, $after: String, $filter: NotificationFilter) {
    notifications(first: $first, after: $after, filter: $filter) {
        nodes {
            id type createdAt updatedAt readAt snoozedUntilAt archivedAt
            url
            actor { id name }
            ... on IssueNotification {
                title
                issue { id identifier title }
            }
            ... on ProjectNotification {
                title
                project { id name }
            }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string NOTIFICATION_GET_QUERY = R"gql(
query NotificationGet($id: String!) {
    notification(id: $id) {
        id type createdAt updatedAt readAt snoozedUntilAt archivedAt
        url
        actor { id name }
        ... on IssueNotification {
            title
            issue { id identifier title }
        }
        ... on ProjectNotification {
            title
            project { id name }
        }
    }
}
)gql";

static const std::string NOTIFICATION_UPDATE_MUTATION = R"gql(
mutation NotificationUpdate($id: String!, $input: NotificationUpdateInput!) {
    notificationUpdate(id: $id, input: $input) { success }
}
)gql";

static const std::string NOTIFICATION_MARK_READ_ALL_MUTATION = R"gql(
mutation NotificationMarkReadAll {
    notificationMarkReadAll { success }
}
)gql";

static const std::string NOTIFICATION_ARCHIVE_MUTATION = R"gql(
mutation NotificationArchive($id: String!) {
    notificationArchive(id: $id) { success }
}
)gql";

// ---------------------------------------------------------------------------
// Shared helpers
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

// Returns the current UTC time formatted as ISO 8601: "2026-02-26T12:34:56Z"
static std::string current_iso8601_utc() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm utc_tm{};

#if defined(_WIN32)
    gmtime_s(&utc_tm, &t);
#else
    gmtime_r(&t, &utc_tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&utc_tm, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}

// ---------------------------------------------------------------------------
// API implementations
// ---------------------------------------------------------------------------

namespace notifications_api {

Connection<Notification> list_notifications(
    int first,
    const std::optional<std::string>& after,
    bool unread_only
) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }

    if (unread_only) {
        // Filter for notifications where readAt is null (unread)
        json filter = json::object();
        json read_at_filter = json::object();
        read_at_filter["null"] = true;
        filter["readAt"] = read_at_filter;
        variables["filter"] = filter;
    }

    auto data = execute_graphql(NOTIFICATIONS_LIST_QUERY, variables);

    Connection<Notification> result;
    from_json(data.at("notifications"), result);
    return result;
}

Notification get_notification(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(NOTIFICATION_GET_QUERY, variables);

    Notification notification;
    from_json(data.at("notification"), notification);
    return notification;
}

int get_unread_count() {
    // Fetch unread notifications and count the returned nodes.
    // Use a generous page size to get an accurate count for most users.
    json variables = json::object();
    variables["first"] = 250;

    json filter = json::object();
    json read_at_filter = json::object();
    read_at_filter["null"] = true;
    filter["readAt"] = read_at_filter;
    variables["filter"] = filter;

    auto data = execute_graphql(NOTIFICATIONS_LIST_QUERY, variables);

    const auto& conn = data.at("notifications");
    if (conn.contains("nodes") && conn["nodes"].is_array()) {
        return static_cast<int>(conn["nodes"].size());
    }
    return 0;
}

void mark_read(const std::string& id) {
    json input = json::object();
    input["readAt"] = current_iso8601_utc();

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = input;

    auto data = execute_graphql(NOTIFICATION_UPDATE_MUTATION, variables);

    bool success = data.at("notificationUpdate").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to mark notification read: " + id);
    }
}

void mark_all_read() {
    auto data = execute_graphql(NOTIFICATION_MARK_READ_ALL_MUTATION, json::object());

    bool success = data.at("notificationMarkReadAll").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to mark all notifications as read");
    }
}

void archive_notification(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(NOTIFICATION_ARCHIVE_MUTATION, variables);

    bool success = data.at("notificationArchive").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to archive notification: " + id);
    }
}

void snooze_notification(const std::string& id, const std::string& snoozed_until_at) {
    json input = json::object();
    input["snoozedUntilAt"] = snoozed_until_at;

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = input;

    auto data = execute_graphql(NOTIFICATION_UPDATE_MUTATION, variables);

    bool success = data.at("notificationUpdate").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to snooze notification: " + id);
    }
}

}  // namespace notifications_api
