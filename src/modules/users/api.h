#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/users/model.h"

namespace users_api {

// List all users in the workspace
Connection<User> list_users(
    int first = 50,
    const std::optional<std::string>& after = std::nullopt,
    bool include_disabled = false
);

// Get a single user by ID
User get_user(const std::string& id);

// Get the currently authenticated viewer (is_me = true)
User get_viewer();

// Resolve a name, displayName, email, or UUID to a user ID
std::string resolve_user_id(const std::string& input);

}  // namespace users_api
