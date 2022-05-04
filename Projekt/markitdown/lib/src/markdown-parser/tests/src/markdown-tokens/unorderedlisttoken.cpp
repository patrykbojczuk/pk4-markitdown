#include "gtest/gtest.h"
#include "../../../markdown-tokens/unorderedlisttoken.h"

using namespace MarkdownParser::MarkdownParser;

TEST(UnorderedListToken, SetsIndentSize) {
    UnorderedListToken token1(L"Example text", 2);
    UnorderedListToken token2(L"Example text", 8);
    EXPECT_EQ(token1.getIndent(), 2);
    EXPECT_EQ(token2.getIndent(), 8);
}

TEST(UnorderedListToken, SetsIndentSizeZeroIfNotDefined) {
    UnorderedListToken token(L"Example text");
    ASSERT_EQ(token.getIndent(), 0);
}
