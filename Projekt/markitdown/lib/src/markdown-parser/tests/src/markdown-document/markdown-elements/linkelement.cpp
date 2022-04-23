#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/linkelement.h"

TEST(LinkElement, SetsUrlOnConstruction){
    MarkdownParser::MarkdownDocument::LinkElement element1(L"https://example.com", L"Testing element");
    MarkdownParser::MarkdownDocument::LinkElement element2(L"https://polsl.pl", L"Silesian University of Technology", L"Politechnika Śląska");
    EXPECT_STREQ(element1.getUrl().c_str(), L"https://example.com");
    EXPECT_STREQ(element2.getUrl().c_str(), L"https://polsl.pl");
}

TEST(LinkElement, ReturnsTitleExistenceState){
    MarkdownParser::MarkdownDocument::LinkElement element1(L"https://example.com", L"Testing element");
    MarkdownParser::MarkdownDocument::LinkElement element2(L"https://polsl.pl", L"Silesian University of Technology", L"Politechnika Śląska");
    EXPECT_FALSE(element1.hasTitle());
    EXPECT_TRUE(element2.hasTitle());
}

TEST(LinkElement, SetsEmptyTitleIfNotDefined){
    MarkdownParser::MarkdownDocument::LinkElement element1(L"https://example.com", L"Testing element");
    EXPECT_STREQ(element1.getTitle().c_str(), L"");
}

