#include "gtest/gtest.h"
#include "../../../markdown-tokens/headerunderlinetoken.h"

using namespace MarkdownParser::MarkdownParser;

TEST(HeaderUnderlineToken, SetsLevelOnConstruction) {
    HeaderUnderlineToken header1(MarkdownHeaderLevel::Level2);
    HeaderUnderlineToken header2(MarkdownHeaderLevel::Level1);

    EXPECT_EQ(header1.getLevel(), MarkdownHeaderLevel::Level2);
    EXPECT_EQ(header2.getLevel(), MarkdownHeaderLevel::Level1);
}

TEST(HeaderUnderlineToken, SetsOnlyLevel1And2) {
    EXPECT_NO_THROW(
        HeaderUnderlineToken header(MarkdownHeaderLevel::Level1);
    );
    EXPECT_NO_THROW(
        HeaderUnderlineToken header(MarkdownHeaderLevel::Level2);
    );
    EXPECT_THROW(
        HeaderUnderlineToken header(MarkdownHeaderLevel::Level3);,
        std::invalid_argument
    );
    EXPECT_THROW(
        HeaderUnderlineToken header(MarkdownHeaderLevel::Level4);,
        std::invalid_argument
    );
    EXPECT_THROW(
        HeaderUnderlineToken header(MarkdownHeaderLevel::Level5);,
        std::invalid_argument
    );
    EXPECT_THROW(
        HeaderUnderlineToken header(MarkdownHeaderLevel::Level6);,
        std::invalid_argument
    );
}
