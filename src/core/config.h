#pragma once

#include <optional>
#include <string>

struct Config {
    std::string api_key;

    struct Defaults {
        std::optional<std::string> team;
        std::string output = "table";
    } defaults;

    struct Display {
        bool color = true;
        int page_size = 50;
        std::string date_format = "relative";
    } display;
};

// Load config from ~/.config/lin/config.toml. Returns default Config if file doesn't exist.
Config load_config();

// Save config to ~/.config/lin/config.toml. Creates directories if needed.
void save_config(const Config& config);

// Returns the config file path: ~/.config/lin/config.toml
std::string config_path();

// Returns the config directory: ~/.config/lin/
std::string config_dir();
