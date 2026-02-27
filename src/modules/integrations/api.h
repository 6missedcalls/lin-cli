#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/integrations/model.h"

namespace integrations_api {

// List all integrations with pagination
Connection<Integration> list_integrations(
    int first,
    const std::optional<std::string>& after
);

// Get a single integration by ID
Integration get_integration(const std::string& id);

}  // namespace integrations_api
