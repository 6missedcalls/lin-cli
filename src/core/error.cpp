#include "error.h"

#include <sstream>
#include <string>
#include <vector>

LinError::LinError(ErrorKind kind, const std::string& message)
    : std::runtime_error(message), kind_(kind), retry_after_(std::nullopt) {}

ErrorKind LinError::kind() const {
    return kind_;
}

std::optional<int> LinError::retry_after() const {
    return retry_after_;
}

void LinError::set_retry_after(int seconds) {
    retry_after_ = seconds;
}

void check_graphql_errors(const json& response) {
    if (!response.contains("errors") || !response["errors"].is_array()) {
        return;
    }

    const auto& errors = response["errors"];
    if (errors.empty()) {
        return;
    }

    std::vector<std::string> messages;
    messages.reserve(errors.size());

    for (const auto& err : errors) {
        if (err.contains("message") && err["message"].is_string()) {
            messages.push_back(err["message"].get<std::string>());
        }
    }

    if (messages.empty()) {
        throw LinError(ErrorKind::GraphQL, "Unknown GraphQL error");
    }

    std::ostringstream joined;
    for (std::size_t i = 0; i < messages.size(); ++i) {
        if (i > 0) {
            joined << "; ";
        }
        joined << messages[i];
    }

    throw LinError(ErrorKind::GraphQL, joined.str());
}

void check_http_status(long status_code, const std::string& response_body) {
    if (status_code >= 200 && status_code < 300) {
        return;
    }

    if (status_code == 401 || status_code == 403) {
        throw LinError(ErrorKind::Auth, "Authentication failed — check your LINEAR_API_KEY");
    }

    if (status_code == 404) {
        throw LinError(ErrorKind::NotFound, "Resource not found");
    }

    if (status_code == 429) {
        LinError err(ErrorKind::RateLimit, "Rate limited by Linear API");

        try {
            auto body = json::parse(response_body);
            if (body.contains("retry_after") && body["retry_after"].is_number()) {
                err.set_retry_after(body["retry_after"].get<int>());
            }
        } catch (const json::parse_error&) {
            // Response body is not JSON — no retry_after available
        }

        throw err;
    }

    if (status_code >= 500) {
        std::string message =
            "Linear API internal error (HTTP " + std::to_string(status_code) + ")";
        throw LinError(ErrorKind::Internal, message);
    }

    std::string message =
        "Unexpected HTTP status " + std::to_string(status_code);
    throw LinError(ErrorKind::Network, message);
}

std::string format_error(const LinError& e) {
    switch (e.kind()) {
        case ErrorKind::Auth:
            return std::string("Authentication error: ") + e.what();
        case ErrorKind::RateLimit: {
            std::string msg = "Rate limited";
            if (e.retry_after().has_value()) {
                msg += ", retry after " + std::to_string(e.retry_after().value()) + "s";
            }
            return msg;
        }
        case ErrorKind::NotFound:
            return std::string("Not found: ") + e.what();
        case ErrorKind::GraphQL:
            return std::string("GraphQL error: ") + e.what();
        case ErrorKind::Validation:
            return std::string("Validation error: ") + e.what();
        case ErrorKind::Network:
            return std::string("Network error: ") + e.what();
        case ErrorKind::Internal:
            return std::string("Internal error: ") + e.what();
    }
    return std::string("Error: ") + e.what();
}
