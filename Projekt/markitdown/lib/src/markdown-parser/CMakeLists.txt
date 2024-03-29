cmake_minimum_required(VERSION 3.21)
project(markdownparser)
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdinc++ -nodefaultlibs -I/usr/local/Cellar/llvm/13.0.1_1/include/c++/v1 -lc -lc++ -lc++abi -lunwind")

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(H_FILES
        markdown-document/markdown-elements/plaintextelement.h
        markdown-document/markdown-elements/linkableelement.h
        markdown-document/markdown-elements/linkelement.h
        markdown-document/markdown-elements/imageelement.h
        markdown-document/markdown-elements/nestedelement.h
        markdown-document/markdown-elements/strikethroughelement.h
        markdown-document/markdown-elements/strongemphasiselement.h
        markdown-document/markdown-elements/emphasiselement.h
        markdown-document/markdown-elements/inlinecodeelement.h
        markdown-document/markdown-elements/vinlinemarkdownelement.h
        markdown-document/markdown-elements/textlineelement.h
        markdown-document/markdown-elements/multilinetextelement.h
        markdown-document/markdown-elements/listelement.h
        markdown-document/markdown-elements/unorderedlistelement.h
        markdown-document/markdown-elements/orderedlistelement.h
        markdown-document/markdown-elements/headerelement.h
        markdownheaderlevel.enum.h
        markdown-document/markdown-elements/codeblockelement.h
        markdown-document/markdown-elements/blockquoteelement.h
        markdown-document/markdown-elements/horizontalruleelement.h
        markdown-document/markdown-elements/paragraphelement.h
        markdown-document/markdown-elements/vtoplevelmarkdownelement.h
        markdown-document/markdowndocument.h
        markdown-tokens/plaintexttoken.h
        markdown-tokens/headertoken.h
        markdown-tokens/headerunderlinetoken.h
        markdown-tokens/codetoken.h
        markdowntokenizer.h
        markdown-tokens/blockquotetoken.h
        markdown-tokens/emptytoken.h
        markdown-tokens/horizontalruletoken.h
        markdown-tokens/orderedlisttoken.h
        markdown-tokens/unorderedlisttoken.h
        helpers/trim.h
        regex.defs.h
        markdownparser.h
        markdown-tokens/rawtexthandler.h
        markdown-document/markdown-elements/recursivevarianttype.h
        markdowninlineelementsparser.h)

set(SRC_FILES
        markdown-document/markdown-elements/plaintextelement.cpp
        markdown-document/markdown-elements/linkableelement.cpp
        markdown-document/markdown-elements/linkelement.cpp
        markdown-document/markdown-elements/imageelement.cpp
        markdown-document/markdown-elements/nestedelement.cpp
        markdown-document/markdown-elements/strikethroughelement.cpp
        markdown-document/markdown-elements/strongemphasiselement.cpp
        markdown-document/markdown-elements/emphasiselement.cpp
        markdown-document/markdown-elements/inlinecodeelement.cpp
        markdown-document/markdown-elements/textlineelement.cpp
        markdown-document/markdown-elements/multilinetextelement.cpp
        markdown-document/markdown-elements/listelement.cpp
        markdown-document/markdown-elements/unorderedlistelement.cpp
        markdown-document/markdown-elements/orderedlistelement.cpp
        markdown-document/markdown-elements/headerelement.cpp
        markdown-document/markdown-elements/codeblockelement.cpp
        markdown-document/markdown-elements/blockquoteelement.cpp
        markdown-document/markdown-elements/horizontalruleelement.cpp
        markdown-document/markdown-elements/paragraphelement.cpp
        markdown-document/markdowndocument.cpp
        markdown-tokens/plaintexttoken.cpp
        markdown-tokens/headertoken.cpp
        markdown-tokens/headerunderlinetoken.cpp
        markdown-tokens/codetoken.cpp
        markdowntokenizer.cpp
        helpers/trim.cpp
        markdown-tokens/blockquotetoken.cpp
        markdown-tokens/emptytoken.cpp
        markdown-tokens/horizontalruletoken.cpp
        markdown-tokens/orderedlisttoken.cpp
        markdown-tokens/unorderedlisttoken.cpp
        markdownparser.cpp
        markdown-tokens/rawtexthandler.cpp
        markdowninlineelementsparser.cpp)

add_library(markdownparser ${SRC_FILES} ${H_FILES})

# $<TARGET_FILE_PREFIX:markdownparser>$<TARGET_FILE_BASE_NAME:markdownparser>$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:d>$<TARGET_FILE_SUFFIX:markdownparser>
# Prefix (lib if library) + Base (without lib) file name + (${CMAKE_BUILD_TYPE} === 'Debug' ? 'd' : '') + File extension
# e.g. library markdownparser.a built in debug = 'lib' + 'markdownparser' + 'd' + '.a' = libmarkdownparserd.a
add_custom_command(TARGET markdownparser
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E
        copy $<TARGET_FILE:markdownparser>
        $<TARGET_FILE_DIR:markdownparser>/../../$<TARGET_FILE_PREFIX:markdownparser>$<TARGET_FILE_BASE_NAME:markdownparser>$<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:d>$<TARGET_FILE_SUFFIX:markdownparser>)
