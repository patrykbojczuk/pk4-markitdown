#include "gtest/gtest.h"
#include "../../../markdown-tokens/codetoken.h"

using namespace MarkdownParser::MarkdownParser;

TEST(CodeToken, SetsLanguageOnConstruction) {
    CodeToken token(L"javascript");
    ASSERT_STREQ(token.getLanguage().c_str(), L"javascript");
}
