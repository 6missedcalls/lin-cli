#include "modules/labels/api.h"

#include <string>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string LABELS_LIST_QUERY = R"gql(
query LabelsList($first: Int, $after: String, $filter: IssueLabelFilter) {
    issueLabels(first: $first, after: $after, filter: $filter) {
        nodes {
            id name description color isGroup createdAt
            parent { id name }
            team { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string LABEL_GET_QUERY = R"gql(
query LabelGet($id: String!) {
    issueLabel(id: $id) {
        id name description color isGroup createdAt
        parent { id name }
        team { id name }
    }
}
)gql";

static const std::string LABEL_CREATE_MUTATION = R"gql(
mutation IssueLabelCreate($input: IssueLabelCreateInput!) {
    issueLabelCreate(input: $input) {
        issueLabel {
            id name description color isGroup createdAt
            parent { id name }
            team { id name }
        }
    }
}
)gql";

static const std::string LABEL_UPDATE_MUTATION = R"gql(
mutation IssueLabelUpdate($id: String!, $input: IssueLabelUpdateInput!) {
    issueLabelUpdate(id: $id, input: $input) {
        issueLabel {
            id name description color isGroup createdAt
            parent { id name }
            team { id name }
        }
    }
}
)gql";

static const std::string LABEL_DELETE_MUTATION = R"gql(
mutation IssueLabelDelete($id: String!) {
    issueLabelDelete(id: $id) { success }
}
)gql";

// ---------------------------------------------------------------------------
// Shared helpers
// ---------------------------------------------------------------------------

static const std::string GRAPHQL_ENDPOINT = "https://api.linear.app/graphql";

static json execute_graphql(const std::string& query, const json& variables) {
    HttpClient client;
    auto api_key = get_api_key();
    auto body = build_request_body({query, variables});

    auto response = with_retry([&]() {
        auto resp = client.post(
            GRAPHQL_ENDPOINT,
            body,
            {{"Content-Type", "application/json"}, {"Authorization", api_key}}
        );
        check_http_status(resp.status_code, resp.body);
        return resp;
    });

    return parse_response(response.body);
}

// ---------------------------------------------------------------------------
// API implementations
// ---------------------------------------------------------------------------

namespace labels_api {

Connection<IssueLabel> list_labels(
    int first,
    const std::optional<std::string>& after,
    const std::optional<std::string>& team_id
) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }

    if (team_id.has_value()) {
        json filter = json::object();
        json team_filter = json::object();
        team_filter["id"] = json::object({{"eq", team_id.value()}});
        filter["team"] = team_filter;
        variables["filter"] = filter;
    }

    auto data = execute_graphql(LABELS_LIST_QUERY, variables);

    Connection<IssueLabel> result;
    from_json(data.at("issueLabels"), result);
    return result;
}

IssueLabel get_label(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(LABEL_GET_QUERY, variables);

    IssueLabel label;
    from_json(data.at("issueLabel"), label);
    return label;
}

IssueLabel create_label(
    const std::string& name,
    const std::string& color,
    const std::optional<std::string>& team_id,
    const std::optional<std::string>& description,
    const std::optional<std::string>& parent_id
) {
    json label_input = json::object();
    label_input["name"] = name;
    label_input["color"] = color;

    if (team_id.has_value()) {
        label_input["teamId"] = team_id.value();
    }
    if (description.has_value()) {
        label_input["description"] = description.value();
    }
    if (parent_id.has_value()) {
        label_input["parentId"] = parent_id.value();
    }

    json variables = json::object();
    variables["input"] = label_input;

    auto data = execute_graphql(LABEL_CREATE_MUTATION, variables);

    IssueLabel label;
    from_json(data.at("issueLabelCreate").at("issueLabel"), label);
    return label;
}

IssueLabel update_label(
    const std::string& id,
    const std::optional<std::string>& name,
    const std::optional<std::string>& color,
    const std::optional<std::string>& description
) {
    json label_input = json::object();

    if (name.has_value()) {
        label_input["name"] = name.value();
    }
    if (color.has_value()) {
        label_input["color"] = color.value();
    }
    if (description.has_value()) {
        label_input["description"] = description.value();
    }

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = label_input;

    auto data = execute_graphql(LABEL_UPDATE_MUTATION, variables);

    IssueLabel label;
    from_json(data.at("issueLabelUpdate").at("issueLabel"), label);
    return label;
}

void delete_label(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(LABEL_DELETE_MUTATION, variables);

    bool success = data.at("issueLabelDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete label " + id);
    }
}

}  // namespace labels_api
