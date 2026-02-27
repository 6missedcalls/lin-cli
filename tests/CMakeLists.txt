FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
    test_issue_parsing.cpp
    test_table_renderer.cpp
    test_filter_builder.cpp
    test_config_parser.cpp
    test_pagination.cpp
    test_color.cpp
    test_error_parsing.cpp
    test_graphql.cpp
)

set(LIN_CORE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/core/http_client.cpp
    ${CMAKE_SOURCE_DIR}/src/core/graphql.cpp
    ${CMAKE_SOURCE_DIR}/src/core/auth.cpp
    ${CMAKE_SOURCE_DIR}/src/core/config.cpp
    ${CMAKE_SOURCE_DIR}/src/core/output.cpp
    ${CMAKE_SOURCE_DIR}/src/core/color.cpp
    ${CMAKE_SOURCE_DIR}/src/core/paginator.cpp
    ${CMAKE_SOURCE_DIR}/src/core/filter.cpp
    ${CMAKE_SOURCE_DIR}/src/core/error.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/issues/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/issues/commands.cpp
)

add_executable(lin_tests
    ${TEST_SOURCES}
    ${LIN_CORE_SOURCES}
)

target_link_libraries(lin_tests PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    CLI11::CLI11
    tomlplusplus::tomlplusplus
    CURL::libcurl
)

target_include_directories(lin_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(lin_tests)
