#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"

TEST(PlainTextElement, SetsTextOnConstruction){
    MarkdownParser::MarkdownDocument::PlainTextElement element1(L"Testing element");
    MarkdownParser::MarkdownDocument::PlainTextElement element2(L"Testing another element");
    EXPECT_STREQ(element1.getText().c_str(), L"Testing element");
    EXPECT_STRNE(element2.getText().c_str(), L"Testing element");
}
