cmake_minimum_required(VERSION 3.20)
project(lin VERSION 0.2.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(src/core/version.h.in src/core/version.h)

include(FetchContent)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_Declare(cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.2
)

FetchContent_Declare(tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
    GIT_TAG v5.0.0
)

FetchContent_MakeAvailable(json cli11 tomlplusplus ftxui)

find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(lin
    src/main.cpp
    src/core/http_client.cpp
    src/core/graphql.cpp
    src/core/auth.cpp
    src/core/config.cpp
    src/core/output.cpp
    src/core/color.cpp
    src/core/paginator.cpp
    src/core/filter.cpp
    src/core/error.cpp
    src/modules/issues/api.cpp
    src/modules/issues/commands.cpp
    src/modules/teams/api.cpp
    src/modules/teams/commands.cpp
    src/modules/labels/api.cpp
    src/modules/labels/commands.cpp
    src/modules/users/api.cpp
    src/modules/users/commands.cpp
    src/modules/projects/api.cpp
    src/modules/projects/commands.cpp
    src/modules/cycles/api.cpp
    src/modules/cycles/commands.cpp
    src/modules/comments/api.cpp
    src/modules/comments/commands.cpp
    src/modules/documents/api.cpp
    src/modules/documents/commands.cpp
    src/modules/views/api.cpp
    src/modules/views/commands.cpp
    src/modules/notifications/api.cpp
    src/modules/notifications/commands.cpp
    src/modules/favorites/api.cpp
    src/modules/favorites/commands.cpp
    src/modules/initiatives/api.cpp
    src/modules/initiatives/commands.cpp
    src/modules/search/api.cpp
    src/modules/search/commands.cpp
    src/modules/webhooks/api.cpp
    src/modules/webhooks/commands.cpp
    src/modules/organization/api.cpp
    src/modules/organization/commands.cpp
    src/modules/integrations/api.cpp
    src/modules/integrations/commands.cpp
    src/modules/config/commands.cpp
    src/modules/cache/commands.cpp
    src/core/cache.cpp
    src/tui/app.cpp
    src/tui/kanban.cpp
    src/tui/issue_detail.cpp
    src/tui/search.cpp
    src/tui/picker.cpp
)

target_include_directories(lin PRIVATE src ${CMAKE_BINARY_DIR}/src)

target_link_libraries(lin PRIVATE
    nlohmann_json::nlohmann_json
    CLI11::CLI11
    tomlplusplus::tomlplusplus
    CURL::libcurl
    SQLite::SQLite3
    ftxui::screen
    ftxui::dom
    ftxui::component
)

install(TARGETS lin DESTINATION bin)

enable_testing()
add_subdirectory(tests)
