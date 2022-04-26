#include "gtest/gtest.h"
#include "../../../markdown-tokens/plaintexttoken.h"

using namespace MarkdownParser::MarkdownParser;

TEST(PlainTextToken, SetsTextOnConstruction) {
    PlainTextToken token(L"Example text");
    ASSERT_STREQ(token.getText().c_str(), L"Example text");
}

TEST(PlainTextToken, SetsRawTextOnConstruction) {
    PlainTextToken token(L"Example text", L"    Example text  ");
    ASSERT_STREQ(token.getRawText().c_str(), L"    Example text  ");
}
