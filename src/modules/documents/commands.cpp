#include "modules/documents/commands.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include "core/error.h"
#include "core/output.h"
#include "core/paginator.h"
#include "modules/documents/api.h"
#include "modules/documents/model.h"

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

std::string read_file_content(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw LinError(ErrorKind::Validation, "Cannot open file: " + path);
    }
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

void render_document_table(const std::vector<Document>& docs) {
    if (get_output_format() == OutputFormat::Csv) {
        output_csv_header({"TITLE", "CREATOR", "PROJECT", "UPDATED"});
        for (const auto& doc : docs) {
            output_csv_row({
                doc.title,
                doc.creator_name.value_or(""),
                doc.project_name.value_or(""),
                doc.updated_at
            });
        }
        return;
    }

    TableRenderer table({
        {"TITLE",   10, 60, false},
        {"CREATOR",  4, 24, false},
        {"PROJECT",  4, 24, false},
        {"UPDATED",  8, 24, false}
    });

    for (const auto& doc : docs) {
        table.add_row({
            doc.title,
            doc.creator_name.value_or(""),
            doc.project_name.value_or(""),
            doc.updated_at
        });
    }

    if (table.empty()) {
        print_warning("No documents found.");
        return;
    }

    table.render(std::cout);
}

void render_document_json(const std::vector<Document>& docs) {
    json arr = json::array();
    for (const auto& doc : docs) {
        json j;
        j["id"] = doc.id;
        j["title"] = doc.title;
        j["slugId"] = doc.slug_id;
        j["url"] = doc.url;
        j["icon"] = doc.icon.has_value() ? json(doc.icon.value()) : json(nullptr);
        j["color"] = doc.color.has_value() ? json(doc.color.value()) : json(nullptr);
        j["creator"] = doc.creator_name.value_or("");
        j["creatorId"] = doc.creator_id.value_or("");
        j["project"] = doc.project_name.value_or("");
        j["projectId"] = doc.project_id.value_or("");
        j["initiativeId"] = doc.initiative_id.has_value() ? json(doc.initiative_id.value()) : json(nullptr);
        j["createdAt"] = doc.created_at;
        j["updatedAt"] = doc.updated_at;
        j["trashed"] = doc.trashed;
        arr.push_back(j);
    }
    output_json(arr);
}

void render_document_detail(const Document& doc) {
    if (get_output_format() == OutputFormat::Json) {
        json j;
        j["id"] = doc.id;
        j["title"] = doc.title;
        j["slugId"] = doc.slug_id;
        j["url"] = doc.url;
        j["icon"] = doc.icon.has_value() ? json(doc.icon.value()) : json(nullptr);
        j["color"] = doc.color.has_value() ? json(doc.color.value()) : json(nullptr);
        j["creator"] = doc.creator_name.value_or("");
        j["creatorId"] = doc.creator_id.value_or("");
        j["project"] = doc.project_name.value_or("");
        j["projectId"] = doc.project_id.value_or("");
        j["initiativeId"] = doc.initiative_id.has_value() ? json(doc.initiative_id.value()) : json(nullptr);
        j["content"] = doc.content.has_value() ? json(doc.content.value()) : json(nullptr);
        j["createdAt"] = doc.created_at;
        j["updatedAt"] = doc.updated_at;
        j["trashed"] = doc.trashed;
        output_json(j);
        return;
    }

    DetailRenderer detail;
    detail.add_section(doc.title);

    if (doc.creator_name.has_value()) {
        detail.add_field("Creator", doc.creator_name.value());
    }
    if (doc.project_name.has_value()) {
        detail.add_field("Project", doc.project_name.value());
    }
    if (doc.initiative_id.has_value()) {
        detail.add_field("Initiative", doc.initiative_id.value());
    }
    if (doc.icon.has_value()) {
        detail.add_field("Icon", doc.icon.value());
    }

    detail.add_field("Created", doc.created_at);
    detail.add_field("Updated", doc.updated_at);
    detail.add_field("URL", doc.url);

    if (doc.content.has_value() && !doc.content.value().empty()) {
        detail.add_blank_line();
        detail.add_section("Content");
        detail.add_markdown(doc.content.value());
    }

    detail.render(std::cout);
}

}  // namespace

// ---------------------------------------------------------------------------
// Command registration
// ---------------------------------------------------------------------------

void documents_commands::register_commands(CLI::App& app) {
    auto* docs = app.add_subcommand("docs", "Manage documents");
    docs->require_subcommand(1);

    // -----------------------------------------------------------------------
    // docs list [--project NAME] [--all]
    // -----------------------------------------------------------------------
    {
        auto* cmd = docs->add_subcommand("list", "List documents");

        struct ListOpts {
            std::string project;
            bool all = false;
            int limit = 50;
        };
        auto opts = std::make_shared<ListOpts>();

        cmd->add_option("--project", opts->project, "Filter by project ID or name");
        cmd->add_flag("--all,-a", opts->all, "Fetch all pages");
        cmd->add_option("--limit,-n", opts->limit, "Maximum number of documents to return")->default_val(50);

        cmd->callback([opts]() {
            try {
                json filter = nullptr;
                if (!opts->project.empty()) {
                    filter = json::object();
                    json project_filter = json::object();
                    project_filter["name"] = json::object({{"eq", opts->project}});
                    filter["project"] = project_filter;
                }

                if (opts->all) {
                    PaginationOptions pag_opts;
                    pag_opts.first = opts->limit;
                    pag_opts.fetch_all = true;
                    pag_opts.limit = opts->limit;

                    Paginator<Document> paginator(
                        [&](const PaginationOptions& po) -> Connection<Document> {
                            return documents_api::list_documents(po.first, po.after, filter);
                        },
                        pag_opts
                    );

                    auto all_docs = paginator.fetch_all();
                    if (get_output_format() == OutputFormat::Json) {
                        render_document_json(all_docs);
                    } else {
                        render_document_table(all_docs);
                    }
                } else {
                    auto connection = documents_api::list_documents(opts->limit, std::nullopt, filter);
                    if (get_output_format() == OutputFormat::Json) {
                        render_document_json(connection.nodes);
                    } else {
                        render_document_table(connection.nodes);
                        if (connection.page_info.has_next_page) {
                            print_warning("More documents available. Use --all to fetch all pages.");
                        }
                    }
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // docs show <id>
    // -----------------------------------------------------------------------
    {
        auto* cmd = docs->add_subcommand("show", "Show document details and content");
        auto id = std::make_shared<std::string>();
        cmd->add_option("id", *id, "Document ID")->required();

        cmd->callback([id]() {
            try {
                auto doc = documents_api::get_document(*id);
                render_document_detail(doc);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // docs search <query> [--limit N]
    // -----------------------------------------------------------------------
    {
        auto* cmd = docs->add_subcommand("search", "Search documents by text");

        struct SearchOpts {
            std::string query;
            int limit = 20;
        };
        auto opts = std::make_shared<SearchOpts>();

        cmd->add_option("query", opts->query, "Search query text")->required();
        cmd->add_option("--limit,-n", opts->limit, "Maximum results")->default_val(20);

        cmd->callback([opts]() {
            try {
                auto connection = documents_api::search_documents(opts->query, opts->limit);
                if (get_output_format() == OutputFormat::Json) {
                    render_document_json(connection.nodes);
                } else {
                    render_document_table(connection.nodes);
                }
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // docs create --title TEXT [--content TEXT] [--content-file PATH] [--project ID]
    // -----------------------------------------------------------------------
    {
        auto* cmd = docs->add_subcommand("create", "Create a new document");

        struct CreateOpts {
            std::string title;
            std::string content;
            std::string content_file;
            std::string project;
        };
        auto opts = std::make_shared<CreateOpts>();

        cmd->add_option("--title,-t", opts->title, "Document title")->required();
        cmd->add_option("--content,-c", opts->content, "Document content (Markdown)");
        cmd->add_option("--content-file", opts->content_file, "Path to a file containing document content");
        cmd->add_option("--project", opts->project, "Project ID to associate the document with");

        cmd->callback([opts]() {
            try {
                if (!opts->content.empty() && !opts->content_file.empty()) {
                    print_error("Use either --content or --content-file, not both.");
                    return;
                }

                DocumentCreateInput input;
                input.title = opts->title;

                if (!opts->content_file.empty()) {
                    input.content = read_file_content(opts->content_file);
                } else if (!opts->content.empty()) {
                    input.content = opts->content;
                }

                if (!opts->project.empty()) {
                    input.project_id = opts->project;
                }

                auto doc = documents_api::create_document(input);
                print_success("Created document: " + doc.title);
                render_document_detail(doc);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // docs update <id> [--title] [--content] [--content-file]
    // -----------------------------------------------------------------------
    {
        auto* cmd = docs->add_subcommand("update", "Update an existing document");

        struct UpdateOpts {
            std::string id;
            std::string title;
            std::string content;
            std::string content_file;
        };
        auto opts = std::make_shared<UpdateOpts>();

        cmd->add_option("id", opts->id, "Document ID")->required();
        cmd->add_option("--title,-t", opts->title, "New document title");
        cmd->add_option("--content,-c", opts->content, "New document content (Markdown)");
        cmd->add_option("--content-file", opts->content_file, "Path to a file containing new document content");

        cmd->callback([opts]() {
            try {
                if (!opts->content.empty() && !opts->content_file.empty()) {
                    print_error("Use either --content or --content-file, not both.");
                    return;
                }

                DocumentUpdateInput input;

                if (!opts->title.empty()) {
                    input.title = opts->title;
                }

                if (!opts->content_file.empty()) {
                    input.content = read_file_content(opts->content_file);
                } else if (!opts->content.empty()) {
                    input.content = opts->content;
                }

                auto doc = documents_api::update_document(opts->id, input);
                print_success("Updated document: " + doc.title);
                render_document_detail(doc);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }

    // -----------------------------------------------------------------------
    // docs delete <id> [--yes]
    // -----------------------------------------------------------------------
    {
        auto* cmd = docs->add_subcommand("delete", "Delete a document");

        struct DeleteOpts {
            std::string id;
            bool yes = false;
        };
        auto opts = std::make_shared<DeleteOpts>();

        cmd->add_option("id", opts->id, "Document ID")->required();
        cmd->add_flag("--yes,-y", opts->yes, "Skip confirmation prompt");

        cmd->callback([opts]() {
            try {
                if (!opts->yes) {
                    std::cerr << "Are you sure you want to delete document " << opts->id << "? [y/N] ";
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (confirm != "y" && confirm != "Y" && confirm != "yes") {
                        print_warning("Aborted.");
                        return;
                    }
                }

                documents_api::delete_document(opts->id);
                print_success("Deleted document " + opts->id);
            } catch (const LinError& e) {
                print_error(format_error(e));
            }
        });
    }
}
