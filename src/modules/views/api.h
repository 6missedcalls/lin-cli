#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/views/model.h"

namespace views_api {

// List custom views, optionally filtering to shared views only
Connection<CustomView> list_views(
    int first = 50,
    const std::optional<std::string>& after = std::nullopt,
    const std::optional<bool>& shared = std::nullopt
);

// Get a single custom view by ID
CustomView get_view(const std::string& id);

// Create a new custom view
CustomView create_view(
    const std::string& name,
    const std::optional<std::string>& description = std::nullopt,
    bool shared = false,
    const std::optional<json>& filter_json = std::nullopt
);

// Delete a custom view by ID
void delete_view(const std::string& id);

// Resolve a view name or UUID to a view ID
std::string resolve_view_id(const std::string& input);

}  // namespace views_api
