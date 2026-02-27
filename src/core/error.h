#pragma once

#include <chrono>
#include <optional>
#include <stdexcept>
#include <string>
#include <thread>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum class ErrorKind {
    Network,
    Auth,
    NotFound,
    RateLimit,
    GraphQL,
    Validation,
    Internal
};

class LinError : public std::runtime_error {
public:
    LinError(ErrorKind kind, const std::string& message);

    ErrorKind kind() const;
    std::optional<int> retry_after() const;
    void set_retry_after(int seconds);

private:
    ErrorKind kind_;
    std::optional<int> retry_after_;
};

// Parse GraphQL errors from response JSON. Throws LinError if errors found.
void check_graphql_errors(const json& response);

// Check HTTP status code and throw appropriate LinError
void check_http_status(long status_code, const std::string& response_body);

// Retry wrapper for rate-limited requests
// F must be callable returning some type T
// Retries up to max_retries times with exponential backoff on RateLimit errors
template <typename F>
auto with_retry(F&& fn, int max_retries = 3) -> decltype(fn()) {
    for (int attempt = 0; attempt <= max_retries; ++attempt) {
        try {
            return fn();
        } catch (const LinError& e) {
            if (e.kind() != ErrorKind::RateLimit || attempt == max_retries) {
                throw;
            }
            int wait_seconds = e.retry_after().value_or(1 << attempt);
            std::this_thread::sleep_for(std::chrono::seconds(wait_seconds));
        }
    }
    throw LinError(ErrorKind::Internal, "Retry loop exited unexpectedly");
}

// Format a user-friendly error message
std::string format_error(const LinError& e);
