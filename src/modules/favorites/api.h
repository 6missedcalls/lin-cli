#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/favorites/model.h"

struct FavoriteCreateInput {
    // Exactly one of these should be set
    std::optional<std::string> issue_id;
    std::optional<std::string> project_id;
    std::optional<std::string> cycle_id;
    std::optional<std::string> custom_view_id;
    std::optional<std::string> document_id;
    std::optional<std::string> label_id;
};

namespace favorites_api {

// List all favorites for the current user
Connection<Favorite> list_favorites(int first = 50, std::optional<std::string> after = std::nullopt);

// Create a favorite — exactly one ID field in input should be set
Favorite create_favorite(const FavoriteCreateInput& input);

// Delete a favorite by ID
void delete_favorite(const std::string& id);

}  // namespace favorites_api
