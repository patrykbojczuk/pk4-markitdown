project(tests)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()

set(TEST_FILES src/markdown-document/markdown-elements/plaintextelement.cpp) # Files with tests to run

add_executable(run_gtest ${TEST_FILES})
target_link_libraries(run_gtest markdownparser)
target_link_libraries(run_gtest gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(run_gtest)
