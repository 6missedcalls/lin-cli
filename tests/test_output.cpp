#include <gtest/gtest.h>
#include <sstream>
#include <nlohmann/json.hpp>

#include "core/output.h"

using json = nlohmann::json;

// =============================================================================
// print_success JSON support
// =============================================================================

TEST(Output, PrintSuccessDefaultIsHumanReadable) {
    // When output format is Table (default), print_success should emit text
    set_output_format(OutputFormat::Table);

    std::ostringstream captured;
    std::streambuf* old_buf = std::cout.rdbuf(captured.rdbuf());
    print_success("Issue ENG-123 archived");
    std::cout.rdbuf(old_buf);

    std::string output = captured.str();
    EXPECT_TRUE(output.find("ENG-123") != std::string::npos);
    // Should NOT be valid JSON
    EXPECT_TRUE(output.find("{") == std::string::npos);
}

TEST(Output, PrintSuccessEmitsJsonWhenJsonFormat) {
    set_output_format(OutputFormat::Json);

    std::ostringstream captured;
    std::streambuf* old_buf = std::cout.rdbuf(captured.rdbuf());
    print_success("Issue ENG-123 archived");
    std::cout.rdbuf(old_buf);

    std::string output = captured.str();
    // Should be valid JSON with success: true and message
    json j = json::parse(output);
    EXPECT_TRUE(j.at("success").get<bool>());
    EXPECT_EQ(j.at("message").get<std::string>(), "Issue ENG-123 archived");

    // Reset for other tests
    set_output_format(OutputFormat::Table);
}

TEST(Output, PrintErrorEmitsJsonWhenJsonFormat) {
    set_output_format(OutputFormat::Json);

    std::ostringstream captured;
    std::streambuf* old_buf = std::cerr.rdbuf(captured.rdbuf());
    print_error("Not found: ENG-999");
    std::cerr.rdbuf(old_buf);

    std::string output = captured.str();
    json j = json::parse(output);
    EXPECT_FALSE(j.at("success").get<bool>());
    EXPECT_EQ(j.at("error").get<std::string>(), "Not found: ENG-999");

    set_output_format(OutputFormat::Table);
}

TEST(Output, PrintWarningEmitsJsonWhenJsonFormat) {
    set_output_format(OutputFormat::Json);

    std::ostringstream captured;
    std::streambuf* old_buf = std::cerr.rdbuf(captured.rdbuf());
    print_warning("Rate limit approaching");
    std::cerr.rdbuf(old_buf);

    std::string output = captured.str();
    json j = json::parse(output);
    EXPECT_TRUE(j.contains("warning"));
    EXPECT_EQ(j.at("warning").get<std::string>(), "Rate limit approaching");

    set_output_format(OutputFormat::Table);
}

// =============================================================================
// Bare subcommand help behavior (subprocess test)
// =============================================================================

// =============================================================================
// --json flag position (should work before OR after subcommand)
// =============================================================================

TEST(CLI, JsonFlagAfterSubcommand) {
    // `lin me --json` should work (exit 0), not "argument was not expected"
    FILE* pipe = popen("./lin me --json 2>&1", "r");
    ASSERT_NE(pipe, nullptr);

    std::string output;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }
    int ret = pclose(pipe);
    int exit_code = WEXITSTATUS(ret);

    // Should not fail with exit 109 ("argument was not expected")
    EXPECT_NE(exit_code, 109);
    // Should not contain the CLI11 error about unexpected argument
    EXPECT_EQ(output.find("was not expected"), std::string::npos);
}

TEST(CLI, JsonFlagBeforeSubcommand) {
    // `lin --json me` should also work (baseline)
    FILE* pipe = popen("./lin --json me 2>&1", "r");
    ASSERT_NE(pipe, nullptr);

    std::string output;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }
    int ret = pclose(pipe);
    int exit_code = WEXITSTATUS(ret);

    EXPECT_NE(exit_code, 109);
    EXPECT_EQ(output.find("was not expected"), std::string::npos);
}

TEST(CLI, BareSubcommandShowsHelp) {
    // `lin issues` with no subcommand should show help (exit 0), not error
    int ret = std::system("./build/lin issues > /dev/null 2>&1");
    int exit_code = WEXITSTATUS(ret);
    EXPECT_EQ(exit_code, 0);
}

TEST(CLI, BareSubcommandOutputContainsUsage) {
    // The help output should contain subcommand list
    FILE* pipe = popen("./build/lin issues 2>&1", "r");
    ASSERT_NE(pipe, nullptr);

    std::string output;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }
    int ret = pclose(pipe);
    int exit_code = WEXITSTATUS(ret);

    EXPECT_EQ(exit_code, 0);
    // Should contain subcommand info like "list", "create", etc.
    EXPECT_TRUE(output.find("list") != std::string::npos);
    EXPECT_TRUE(output.find("create") != std::string::npos);
}
