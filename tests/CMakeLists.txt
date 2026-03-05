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
    test_teams_parsing.cpp
    test_teams_name_resolution.cpp
    test_labels_parsing.cpp
    test_users_parsing.cpp
    test_projects_parsing.cpp
    test_cycles_parsing.cpp
    test_comments_parsing.cpp
    test_documents_parsing.cpp
    test_views_parsing.cpp
    test_notifications_parsing.cpp
    test_favorites_parsing.cpp
    test_initiatives_parsing.cpp
    test_search.cpp
    test_webhooks_parsing.cpp
    test_organization_parsing.cpp
    test_integrations_parsing.cpp
    test_tui.cpp
    test_output.cpp
    test_cache.cpp
    test_project_create_input.cpp
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
    ${CMAKE_SOURCE_DIR}/src/modules/teams/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/teams/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/labels/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/labels/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/users/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/users/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/projects/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/projects/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/cycles/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/cycles/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/comments/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/comments/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/documents/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/documents/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/views/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/views/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/notifications/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/notifications/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/favorites/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/favorites/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/initiatives/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/initiatives/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/search/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/search/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/webhooks/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/webhooks/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/organization/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/organization/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/integrations/api.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/integrations/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/config/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/modules/cache/commands.cpp
    ${CMAKE_SOURCE_DIR}/src/core/cache.cpp
    ${CMAKE_SOURCE_DIR}/src/tui/picker.cpp
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
    SQLite::SQLite3
)

target_include_directories(lin_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(lin_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
