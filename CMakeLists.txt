cmake_minimum_required(VERSION 3.20)
project(lin VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

FetchContent_MakeAvailable(json cli11 tomlplusplus)

find_package(CURL REQUIRED)

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
)

target_include_directories(lin PRIVATE src)

target_link_libraries(lin PRIVATE
    nlohmann_json::nlohmann_json
    CLI11::CLI11
    tomlplusplus::tomlplusplus
    CURL::libcurl
)

install(TARGETS lin DESTINATION bin)

enable_testing()
add_subdirectory(tests)
