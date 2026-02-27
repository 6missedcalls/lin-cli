#pragma once

#include <string>

// Returns the API key. Priority:
// 1. LINEAR_API_KEY env var
// 2. api_key from config file
// 3. Throws LinError(Auth) with setup instructions
std::string get_api_key();

// Validate the API key by checking its format.
// Returns true if the key is non-empty and starts with "lin_api_".
// Full validation (calling viewer() query) will be added when the HTTP client is wired up.
bool validate_api_key(const std::string& key);
