#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/labels/model.h"

namespace labels_api {

// List labels with optional team filter and pagination
Connection<IssueLabel> list_labels(
    int first = 50,
    const std::optional<std::string>& after = std::nullopt,
    const std::optional<std::string>& team_id = std::nullopt
);

// Get single label by ID
IssueLabel get_label(const std::string& id);

// Create a new label
IssueLabel create_label(
    const std::string& name,
    const std::string& color,
    const std::optional<std::string>& team_id = std::nullopt,
    const std::optional<std::string>& description = std::nullopt,
    const std::optional<std::string>& parent_id = std::nullopt
);

// Update an existing label
IssueLabel update_label(
    const std::string& id,
    const std::optional<std::string>& name = std::nullopt,
    const std::optional<std::string>& color = std::nullopt,
    const std::optional<std::string>& description = std::nullopt
);

// Delete a label
void delete_label(const std::string& id);

// Resolve a label name or ID to a label ID.
// Returns the input unchanged if it looks like a UUID; otherwise
// searches labels by name (case-insensitive).
std::string resolve_label_id(const std::string& input);

}  // namespace labels_api
