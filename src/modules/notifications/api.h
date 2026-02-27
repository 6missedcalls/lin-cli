#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/notifications/model.h"

namespace notifications_api {

// List notifications with optional unread filter and pagination.
// When unread_only is true, applies a filter for readAt null.
Connection<Notification> list_notifications(
    int first = 50,
    const std::optional<std::string>& after = std::nullopt,
    bool unread_only = false
);

// Fetch a single notification by ID.
Notification get_notification(const std::string& id);

// Return count of unread notifications.
// Uses the notifications query with readAt null filter and counts returned nodes.
int get_unread_count();

// Mark a single notification as read by setting readAt to the current UTC timestamp.
void mark_read(const std::string& id);

// Mark all notifications as read via notificationMarkReadAll mutation.
void mark_all_read();

// Archive a single notification.
void archive_notification(const std::string& id);

// Snooze a notification until the given ISO 8601 datetime string.
void snooze_notification(const std::string& id, const std::string& snoozed_until_at);

}  // namespace notifications_api
