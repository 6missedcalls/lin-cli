#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/webhooks/model.h"

namespace webhooks_api {

// List all webhooks (paginated)
Connection<Webhook> list_webhooks(
    int first = 50,
    const std::optional<std::string>& after = std::nullopt
);

// Get a single webhook by ID
Webhook get_webhook(const std::string& id);

// Create a new webhook
Webhook create_webhook(
    const std::string& url,
    const std::optional<std::string>& label = std::nullopt,
    const std::optional<std::string>& team_id = std::nullopt,
    const std::optional<bool>& enabled = std::nullopt
);

// Update an existing webhook
Webhook update_webhook(
    const std::string& id,
    const std::optional<std::string>& url = std::nullopt,
    const std::optional<std::string>& label = std::nullopt,
    const std::optional<bool>& enabled = std::nullopt
);

// Delete a webhook
void delete_webhook(const std::string& id);

}  // namespace webhooks_api
