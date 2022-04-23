cmake_minimum_required(VERSION 3.21)
project(markdownparser)
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 23)

set(H_FILES
        markdown-document/markdown-elements/plaintextelement.h
        markdown-document/markdown-elements/linkableelement.h
        markdown-document/markdown-elements/linkelement.h
        markdown-document/markdown-elements/imageelement.h)

set(SRC_FILES
        markdown-document/markdown-elements/plaintextelement.cpp
        markdown-document/markdown-elements/linkableelement.cpp
        markdown-document/markdown-elements/linkelement.cpp
        markdown-document/markdown-elements/imageelement.cpp)

add_library(markdownparser ${SRC_FILES} ${H_FILES})

# $<TARGET_FILE_PREFIX:markdownparser>$<TARGET_FILE_BASE_NAME:markdownparser>$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:d>$<TARGET_FILE_SUFFIX:markdownparser>
# Prefix (lib if library) + Base (without lib) file name + (${CMAKE_BUILD_TYPE} === 'Debug' ? 'd' : '') + File extension
# e.g. library markdownparser.a built in debug = 'lib' + 'markdownparser' + 'd' + '.a' = libmarkdownparserd.a
add_custom_command(TARGET markdownparser
                   POST_BUILD COMMAND ${CMAKE_COMMAND} -E
                        copy $<TARGET_FILE:markdownparser>
                        $<TARGET_FILE_DIR:markdownparser>/../../$<TARGET_FILE_PREFIX:markdownparser>$<TARGET_FILE_BASE_NAME:markdownparser>$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:d>$<TARGET_FILE_SUFFIX:markdownparser>)
