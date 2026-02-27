#include "core/config.h"

#include <toml++/toml.hpp>

#include <cstdlib>
#include <filesystem>
#include <fstream>

std::string config_dir() {
    const char* home = std::getenv("HOME");
    if (home == nullptr) {
        return ".config/lin/";
    }
    return std::string(home) + "/.config/lin/";
}

std::string config_path() {
    return config_dir() + "config.toml";
}

Config load_config() {
    Config config;

    try {
        auto tbl = toml::parse_file(config_path());

        if (auto key = tbl["api_key"].value<std::string>()) {
            config.api_key = *key;
        }

        if (auto team = tbl["defaults"]["team"].value<std::string>()) {
            config.defaults.team = *team;
        }

        if (auto output = tbl["defaults"]["output"].value<std::string>()) {
            config.defaults.output = *output;
        }

        if (auto color = tbl["display"]["color"].value<bool>()) {
            config.display.color = *color;
        }

        if (auto page_size = tbl["display"]["page_size"].value<int64_t>()) {
            config.display.page_size = static_cast<int>(*page_size);
        }

        if (auto date_format = tbl["display"]["date_format"].value<std::string>()) {
            config.display.date_format = *date_format;
        }
    } catch (const toml::parse_error&) {
        return config;
    } catch (const std::exception&) {
        return config;
    }

    return config;
}

void save_config(const Config& config) {
    std::filesystem::create_directories(config_dir());

    auto tbl = toml::table{};

    if (!config.api_key.empty()) {
        tbl.insert("api_key", config.api_key);
    }

    auto defaults_tbl = toml::table{};
    if (config.defaults.team.has_value()) {
        defaults_tbl.insert("team", *config.defaults.team);
    }
    defaults_tbl.insert("output", config.defaults.output);
    tbl.insert("defaults", defaults_tbl);

    auto display_tbl = toml::table{};
    display_tbl.insert("color", config.display.color);
    display_tbl.insert("page_size", static_cast<int64_t>(config.display.page_size));
    display_tbl.insert("date_format", config.display.date_format);
    tbl.insert("display", display_tbl);

    std::ofstream file(config_path());
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file for writing: " + config_path());
    }

    file << tbl;
    file.close();

    std::filesystem::permissions(
        config_path(),
        std::filesystem::perms::owner_read | std::filesystem::perms::owner_write,
        std::filesystem::perm_options::replace
    );
}
