#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

struct HttpResponse {
    long status_code = 0;
    std::string body;
    std::string error_message;
    // Rate limit headers
    std::optional<int> retry_after;
};

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    HttpClient(const HttpClient&) = delete;
    HttpClient& operator=(const HttpClient&) = delete;
    HttpClient(HttpClient&& other) noexcept;
    HttpClient& operator=(HttpClient&& other) noexcept;

    HttpResponse post(
        const std::string& url,
        const std::string& body,
        const std::vector<std::pair<std::string, std::string>>& headers
    );

    void set_timeout(long timeout_ms);

private:
    void* curl_handle_;  // CURL* but avoid including curl.h in header
    long timeout_ms_ = 30000;
};
