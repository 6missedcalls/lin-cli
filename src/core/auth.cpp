#include "core/auth.h"

#include "core/config.h"
#include "core/error.h"

#include <cstdlib>

std::string get_api_key() {
    const char* env_key = std::getenv("LINEAR_API_KEY");
    if (env_key != nullptr && env_key[0] != '\0') {
        std::string key(env_key);
        if (!validate_api_key(key)) {
            throw LinError(
                ErrorKind::Auth,
                "Invalid API key format. Linear API keys must start with 'lin_api_'. "
                "Check your LINEAR_API_KEY environment variable."
            );
        }
        return key;
    }

    Config config = load_config();
    if (!config.api_key.empty()) {
        if (!validate_api_key(config.api_key)) {
            throw LinError(
                ErrorKind::Auth,
                "Invalid API key format in config file. Linear API keys must start with 'lin_api_'. "
                "Run 'lin config init' to reconfigure."
            );
        }
        return config.api_key;
    }

    throw LinError(
        ErrorKind::Auth,
        "No API key found. Set LINEAR_API_KEY environment variable or run 'lin config init'"
    );
}

bool validate_api_key(const std::string& key) {
    if (key.empty()) {
        return false;
    }

    const std::string prefix = "lin_api_";
    if (key.size() < prefix.size()) {
        return false;
    }

    return key.compare(0, prefix.size(), prefix) == 0;
}
