#include "modules/documents/api.h"

#include <string>
#include <utility>

#include "core/auth.h"
#include "core/error.h"
#include "core/graphql.h"
#include "core/http_client.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// GraphQL query / mutation strings
// ---------------------------------------------------------------------------

static const std::string DOCUMENTS_LIST_QUERY = R"gql(
query DocumentsList($first: Int, $after: String, $filter: DocumentFilter) {
    documents(first: $first, after: $after, filter: $filter) {
        nodes {
            id title slugId url icon color
            createdAt updatedAt trashed
            content
            creator { id displayName }
            project { id name }
            initiative { id }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string DOCUMENT_GET_QUERY = R"gql(
query DocumentGet($id: String!) {
    document(id: $id) {
        id title slugId url icon color
        createdAt updatedAt trashed
        content
        creator { id displayName }
        project { id name }
        initiative { id }
    }
}
)gql";

static const std::string SEARCH_DOCUMENTS_QUERY = R"gql(
query SearchDocuments($term: String!, $first: Int) {
    searchDocuments(term: $term, first: $first) {
        nodes {
            id title slugId url icon color
            createdAt updatedAt trashed
            creator { id displayName }
            project { id name }
        }
        pageInfo { hasNextPage endCursor }
    }
}
)gql";

static const std::string DOCUMENT_CREATE_MUTATION = R"gql(
mutation DocumentCreate($input: DocumentCreateInput!) {
    documentCreate(input: $input) {
        document {
            id title slugId url icon color
            createdAt updatedAt trashed
            content
            creator { id displayName }
            project { id name }
            initiative { id }
        }
    }
}
)gql";

static const std::string DOCUMENT_UPDATE_MUTATION = R"gql(
mutation DocumentUpdate($id: String!, $input: DocumentUpdateInput!) {
    documentUpdate(id: $id, input: $input) {
        document {
            id title slugId url icon color
            createdAt updatedAt trashed
            content
            creator { id displayName }
            project { id name }
            initiative { id }
        }
    }
}
)gql";

static const std::string DOCUMENT_DELETE_MUTATION = R"gql(
mutation DocumentDelete($id: String!) {
    documentDelete(id: $id) { success }
}
)gql";

// ---------------------------------------------------------------------------
// Shared helper
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

namespace documents_api {

Connection<Document> list_documents(
    int first,
    const std::optional<std::string>& after,
    const json& filter
) {
    json variables = json::object();
    variables["first"] = first;

    if (after.has_value()) {
        variables["after"] = after.value();
    }
    if (!filter.is_null()) {
        variables["filter"] = filter;
    }

    auto data = execute_graphql(DOCUMENTS_LIST_QUERY, variables);

    Connection<Document> result;
    from_json(data.at("documents"), result);
    return result;
}

Document get_document(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(DOCUMENT_GET_QUERY, variables);

    Document doc;
    from_json(data.at("document"), doc);
    return doc;
}

Connection<Document> search_documents(const std::string& term, int limit) {
    json variables = json::object();
    variables["term"] = term;
    variables["first"] = limit;

    auto data = execute_graphql(SEARCH_DOCUMENTS_QUERY, variables);

    Connection<Document> result;
    from_json(data.at("searchDocuments"), result);
    return result;
}

Document create_document(const DocumentCreateInput& input) {
    json doc_input = json::object();
    doc_input["title"] = input.title;

    if (input.content.has_value()) {
        doc_input["content"] = input.content.value();
    }
    if (input.project_id.has_value()) {
        doc_input["projectId"] = input.project_id.value();
    }

    json variables = json::object();
    variables["input"] = doc_input;

    auto data = execute_graphql(DOCUMENT_CREATE_MUTATION, variables);

    Document doc;
    from_json(data.at("documentCreate").at("document"), doc);
    return doc;
}

Document update_document(const std::string& id, const DocumentUpdateInput& input) {
    json doc_input = json::object();

    if (input.title.has_value()) {
        doc_input["title"] = input.title.value();
    }
    if (input.content.has_value()) {
        doc_input["content"] = input.content.value();
    }

    json variables = json::object();
    variables["id"] = id;
    variables["input"] = doc_input;

    auto data = execute_graphql(DOCUMENT_UPDATE_MUTATION, variables);

    Document doc;
    from_json(data.at("documentUpdate").at("document"), doc);
    return doc;
}

void delete_document(const std::string& id) {
    json variables = json::object();
    variables["id"] = id;

    auto data = execute_graphql(DOCUMENT_DELETE_MUTATION, variables);

    bool success = data.at("documentDelete").at("success").get<bool>();
    if (!success) {
        throw LinError(ErrorKind::Internal, "Failed to delete document " + id);
    }
}

}  // namespace documents_api
