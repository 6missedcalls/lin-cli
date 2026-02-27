#pragma once

#include <optional>
#include <string>

#include "core/types.h"
#include "modules/documents/model.h"

struct DocumentCreateInput {
    std::string title;
    std::optional<std::string> content;
    std::optional<std::string> project_id;
};

struct DocumentUpdateInput {
    std::optional<std::string> title;
    std::optional<std::string> content;
};

namespace documents_api {

// List documents with optional pagination
Connection<Document> list_documents(
    int first = 50,
    const std::optional<std::string>& after = std::nullopt,
    const nlohmann::json& filter = nullptr
);

// Get a single document by ID
Document get_document(const std::string& id);

// Full-text search across documents
Connection<Document> search_documents(
    const std::string& term,
    int limit = 20
);

// Create a new document
Document create_document(const DocumentCreateInput& input);

// Update an existing document
Document update_document(const std::string& id, const DocumentUpdateInput& input);

// Delete a document
void delete_document(const std::string& id);

}  // namespace documents_api
