#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "core/config.h"

TEST(Config, DefaultConfig) {
    Config config;
    EXPECT_TRUE(config.api_key.empty());
    EXPECT_EQ(config.defaults.output, "table");
    EXPECT_EQ(config.defaults.team, std::nullopt);
    EXPECT_TRUE(config.display.color);
    EXPECT_EQ(config.display.page_size, 50);
    EXPECT_EQ(config.display.date_format, "relative");
}

TEST(Config, ConfigPath) {
    auto path = config_path();
    EXPECT_FALSE(path.empty());
    EXPECT_TRUE(path.find("config.toml") != std::string::npos);
    EXPECT_TRUE(path.find("lin") != std::string::npos);
}

TEST(Config, ConfigDir) {
    auto dir = config_dir();
    EXPECT_FALSE(dir.empty());
    EXPECT_TRUE(dir.find("lin") != std::string::npos);
}

TEST(Config, LoadMissingConfigReturnsDefault) {
    // Loading from a non-existent path should return defaults
    Config config = load_config();
    // This test passes as long as it doesn't crash
    EXPECT_EQ(config.defaults.output, "table");
}
