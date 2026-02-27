#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/projects/model.h"

struct ProjectListOptions {
    int first = 50;
    std::optional<std::string> after;
    nlohmann::json filter = nullptr;
};

struct ProjectCreateInput {
    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::optional<std::string> lead_id;
    std::optional<std::string> status_id;
    std::optional<int> priority;
    std::optional<std::string> start_date;
    std::optional<std::string> target_date;
    std::vector<std::string> member_ids;
    std::vector<std::string> team_ids;
};

struct ProjectUpdateInput {
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::optional<std::string> icon;
    std::optional<std::string> color;
    std::optional<std::string> lead_id;
    std::optional<std::string> status_id;
    std::optional<int> priority;
    std::optional<std::string> start_date;
    std::optional<std::string> target_date;
    std::optional<std::string> health;
};

struct ProjectMilestoneCreateInput {
    std::string project_id;
    std::string name;
    std::optional<std::string> description;
    std::optional<std::string> target_date;
    std::optional<double> sort_order;
};

struct ProjectMilestoneUpdateInput {
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::optional<std::string> target_date;
    std::optional<double> sort_order;
};

struct ProjectUpdateCreateInput {
    std::string project_id;
    std::string body;
    std::optional<std::string> health;
};

namespace projects_api {

// Projects
Connection<Project> list_projects(const ProjectListOptions& opts);
Project get_project(const std::string& id);
Connection<Project> search_projects(const std::string& term, int limit = 20);
Project create_project(const ProjectCreateInput& input);
Project update_project(const std::string& id, const ProjectUpdateInput& input);
void delete_project(const std::string& id);

// Milestones
Connection<ProjectMilestone> list_milestones(const std::string& project_id);
ProjectMilestone create_milestone(const ProjectMilestoneCreateInput& input);
ProjectMilestone update_milestone(const std::string& id, const ProjectMilestoneUpdateInput& input);
void delete_milestone(const std::string& id);

// Updates
Connection<ProjectUpdate> list_updates(const std::string& project_id);
ProjectUpdate create_update(const ProjectUpdateCreateInput& input);

}  // namespace projects_api
