#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/comments/model.h"

namespace comments_api {

// List comments for a given issue (by issue ID or identifier)
Connection<Comment> list_comments(
    const std::string& issue_id,
    int first = 50,
    const std::optional<std::string>& after = std::nullopt
);

// Get a single comment by its ID
Comment get_comment(const std::string& id);

// Create a comment on an issue; optionally reply to a parent comment
Comment create_comment(
    const std::string& issue_id,
    const std::string& body,
    const std::optional<std::string>& parent_id = std::nullopt
);

// Update the body of an existing comment
Comment update_comment(const std::string& id, const std::string& body);

// Delete a comment by ID
void delete_comment(const std::string& id);

}  // namespace comments_api
