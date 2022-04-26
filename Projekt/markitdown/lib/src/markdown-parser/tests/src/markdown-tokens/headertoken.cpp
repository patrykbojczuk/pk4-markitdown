#include "gtest/gtest.h"
#include "../../../markdown-tokens/headertoken.h"

using namespace MarkdownParser::MarkdownParser;

TEST(HeaderToken, SetsLevelOnConstruction) {
    HeaderToken header(MarkdownHeaderLevel::Level5, L"");

    ASSERT_EQ(header.getLevel(), MarkdownHeaderLevel::Level5);
}

TEST(HeaderToken, ReturnsIdExistenceState){
    HeaderToken header1(MarkdownHeaderLevel::Level5, L"");
    HeaderToken header2(MarkdownHeaderLevel::Level5, L"", L"example_id");

    EXPECT_FALSE(header1.hasId());
    EXPECT_TRUE(header2.hasId());
}

TEST(HeaderToken, SetsEmptyIdIfNotDefined){
    HeaderToken header(MarkdownHeaderLevel::Level5, L"");

    EXPECT_STREQ(header.getId().c_str(), L"");
}


