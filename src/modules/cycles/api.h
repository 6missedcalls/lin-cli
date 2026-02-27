#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/cycles/model.h"

struct CycleListOptions {
    int first = 50;
    std::optional<std::string> after;
    nlohmann::json filter = nullptr;  // CycleFilter JSON or null
};

struct CycleCreateInput {
    std::string team_id;
    std::string starts_at;
    std::string ends_at;
    std::optional<std::string> name;
    std::optional<std::string> description;
};

struct CycleUpdateInput {
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::optional<std::string> starts_at;
    std::optional<std::string> ends_at;
};

namespace cycles_api {

// List cycles with filtering and pagination
Connection<Cycle> list_cycles(const CycleListOptions& opts);

// Get single cycle by ID
Cycle get_cycle(const std::string& id);

// CRUD
Cycle create_cycle(const CycleCreateInput& input);
Cycle update_cycle(const std::string& id, const CycleUpdateInput& input);
void archive_cycle(const std::string& id);

}  // namespace cycles_api
