#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/linkelement.h"
#include "../../../../markdown-document/markdown-elements/imageelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(LinkableElements$LinkElement, SetsUrlOnConstruction){
    LinkElement element1(L"https://example.com", L"Testing element");
    LinkElement element2(L"https://polsl.pl", L"Silesian University of Technology", L"Politechnika Śląska");
    EXPECT_STREQ(element1.getUrl().c_str(), L"https://example.com");
    EXPECT_STREQ(element2.getUrl().c_str(), L"https://polsl.pl");
}

TEST(LinkableElements$LinkElement, ReturnsTitleExistenceState){
    LinkElement element1(L"https://example.com", L"Testing element");
    LinkElement element2(L"https://polsl.pl", L"Silesian University of Technology", L"Politechnika Śląska");
    EXPECT_FALSE(element1.hasTitle());
    EXPECT_TRUE(element2.hasTitle());
}

TEST(LinkableElements$LinkElement, SetsEmptyTitleIfNotDefined){
    LinkElement element1(L"https://example.com", L"Testing element");
    EXPECT_STREQ(element1.getTitle().c_str(), L"");
}

TEST(LinkableElements$ImageElement, SetsUrlOnConstruction){
    ImageElement element1(L"https://example.com/image.png", L"Testing element");
    ImageElement element2(L"https://polsl.pl/image.png", L"Silesian University of Technology", L"Politechnika Śląska");
    EXPECT_STREQ(element1.getUrl().c_str(), L"https://example.com/image.png");
    EXPECT_STREQ(element2.getUrl().c_str(), L"https://polsl.pl/image.png");
}

TEST(LinkableElements$ImageElement, ReturnsTitleExistenceState){
    ImageElement element1(L"https://example.com/image.png", L"Testing element");
    ImageElement element2(L"https://polsl.pl/image.png", L"Silesian University of Technology", L"Politechnika Śląska");
    EXPECT_FALSE(element1.hasTitle());
    EXPECT_TRUE(element2.hasTitle());
}

TEST(LinkableElements$ImageElement, SetsEmptyTitleIfNotDefined){
    ImageElement element1(L"https://example.com/image.png", L"Testing element");
    EXPECT_STREQ(element1.getTitle().c_str(), L"");
}

