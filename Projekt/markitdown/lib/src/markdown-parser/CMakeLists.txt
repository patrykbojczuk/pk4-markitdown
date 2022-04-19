cmake_minimum_required(VERSION 3.21)
project(markdownparser)

set(CMAKE_CXX_STANDARD 23)

add_library(markdownparser main.cpp)

# $<TARGET_FILE_PREFIX:markdownparser>$<TARGET_FILE_BASE_NAME:markdownparser>$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:d>$<TARGET_FILE_SUFFIX:markdownparser>
# Prefix (lib if library) + Base (without lib) file name + (${CMAKE_BUILD_TYPE} === 'Debug' ? 'd' : '') + File extension
# e.g. library markdownparser.a built in debug = 'lib' + 'markdownparser' + 'd' + '.a' = libmarkdownparserd.a
add_custom_command(TARGET markdownparser
                   POST_BUILD COMMAND ${CMAKE_COMMAND} -E
                        copy $<TARGET_FILE:markdownparser>
                        $<TARGET_FILE_DIR:markdownparser>/../../$<TARGET_FILE_PREFIX:markdownparser>$<TARGET_FILE_BASE_NAME:markdownparser>$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:d>$<TARGET_FILE_SUFFIX:markdownparser>)
