#include "http_client.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include <curl/curl.h>

namespace {

struct WriteContext {
    std::string* buffer;
};

struct HeaderContext {
    std::optional<int>* retry_after;
};

auto write_callback(
    char* ptr,
    size_t size,
    size_t nmemb,
    void* userdata
) -> size_t {
    auto* context = static_cast<WriteContext*>(userdata);
    const size_t total_bytes = size * nmemb;
    context->buffer->append(ptr, total_bytes);
    return total_bytes;
}

auto header_callback(
    char* ptr,
    size_t size,
    size_t nmemb,
    void* userdata
) -> size_t {
    auto* context = static_cast<HeaderContext*>(userdata);
    const size_t total_bytes = size * nmemb;
    const std::string header(ptr, total_bytes);

    // Find the colon separator
    const auto colon_pos = header.find(':');
    if (colon_pos == std::string::npos) {
        return total_bytes;
    }

    // Extract and lowercase the header name
    std::string name = header.substr(0, colon_pos);
    std::transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if (name != "retry-after") {
        return total_bytes;
    }

    // Extract the value, trimming whitespace
    std::string value = header.substr(colon_pos + 1);
    const auto start = value.find_first_not_of(" \t");
    const auto end = value.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos) {
        return total_bytes;
    }
    value = value.substr(start, end - start + 1);

    try {
        const int seconds = std::stoi(value);
        if (seconds >= 0) {
            *(context->retry_after) = seconds;
        }
    } catch (const std::exception&) {
        // Not a numeric Retry-After value; ignore date-based values
    }

    return total_bytes;
}

} // namespace

HttpClient::HttpClient()
    : curl_handle_(curl_easy_init()) {
    if (curl_handle_ == nullptr) {
        throw std::runtime_error("Failed to initialize libcurl handle");
    }
}

HttpClient::~HttpClient() {
    if (curl_handle_ != nullptr) {
        curl_easy_cleanup(curl_handle_);
    }
}

HttpClient::HttpClient(HttpClient&& other) noexcept
    : curl_handle_(other.curl_handle_),
      timeout_ms_(other.timeout_ms_) {
    other.curl_handle_ = nullptr;
    other.timeout_ms_ = 30000;
}

HttpClient& HttpClient::operator=(HttpClient&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    if (curl_handle_ != nullptr) {
        curl_easy_cleanup(curl_handle_);
    }
    curl_handle_ = other.curl_handle_;
    timeout_ms_ = other.timeout_ms_;
    other.curl_handle_ = nullptr;
    other.timeout_ms_ = 30000;
    return *this;
}

HttpResponse HttpClient::post(
    const std::string& url,
    const std::string& body,
    const std::vector<std::pair<std::string, std::string>>& headers
) {
    if (curl_handle_ == nullptr) {
        return HttpResponse{0, "", "HttpClient has been moved from", std::nullopt};
    }

    auto* curl = curl_handle_;

    // Reset all options from any previous request
    curl_easy_reset(curl);

    HttpResponse response;
    std::string response_body;
    std::optional<int> retry_after;

    WriteContext write_ctx{&response_body};
    HeaderContext header_ctx{&retry_after};

    // Build the headers slist
    struct curl_slist* header_list = nullptr;
    for (const auto& [name, value] : headers) {
        const std::string formatted = name + ": " + value;
        header_list = curl_slist_append(header_list, formatted.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(body.size()));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_ctx);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_ctx);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout_ms_);
    // Disable redirects — GraphQL endpoints should not redirect,
    // and following redirects could leak the Authorization header
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    // Explicitly enforce TLS certificate verification
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    // Enable TCP keepalive
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

    const CURLcode result = curl_easy_perform(curl);

    // Clean up the headers slist regardless of outcome
    if (header_list != nullptr) {
        curl_slist_free_all(header_list);
    }

    if (result != CURLE_OK) {
        response.status_code = 0;
        response.body = "";
        response.error_message = curl_easy_strerror(result);
        response.retry_after = std::nullopt;
        return response;
    }

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    response.status_code = http_code;
    response.body = std::move(response_body);
    response.error_message = "";
    response.retry_after = retry_after;

    return response;
}

void HttpClient::set_timeout(long timeout_ms) noexcept {
    timeout_ms_ = timeout_ms;
}
