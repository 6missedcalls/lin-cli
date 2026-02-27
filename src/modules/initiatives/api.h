#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/initiatives/model.h"

struct InitiativeListOptions {
    int first = 50;
    std::optional<std::string> after;
    std::optional<std::string> status_filter;
};

namespace initiatives_api {

// List all initiatives with optional pagination and status filter.
// Maps to the `initiatives` GraphQL query.
Connection<Initiative> list_initiatives(const InitiativeListOptions& opts);

// Fetch a single initiative by ID.
// Maps to the `initiative(id:)` GraphQL query.
Initiative get_initiative(const std::string& id);

}  // namespace initiatives_api
