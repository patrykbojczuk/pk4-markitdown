project(tests)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()

set(TEST_FILES
        src/markdown-document/markdown-elements/plaintextelement.cpp
        src/markdown-document/markdown-elements/linkableelements.cpp
        src/markdown-document/markdown-elements/nestableelements.cpp
        src/markdown-document/markdown-elements/textlineelement.cpp
        src/markdown-document/markdown-elements/multilinetextelement.cpp
        src/markdown-document/markdown-elements/listelements.cpp
        src/markdown-document/markdown-elements/headerelement.cpp
        src/markdown-document/markdown-elements/codeblockelement.cpp
        src/markdown-document/markdowndocument.cpp
        src/markdown-tokens/plaintexttoken.cpp
        src/markdown-tokens/headertoken.cpp
        src/markdown-tokens/headerunderlinetoken.cpp
        src/markdown-tokens/codetoken.cpp
        src/markdown-tokens/unorderedlisttoken.cpp
        src/markdowntokenizer.cpp
        src/markdownparser.cpp) # Files with tests to run

add_executable(run_gtest ${TEST_FILES})
target_link_libraries(run_gtest markdownparser)
target_link_libraries(run_gtest gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(run_gtest)
