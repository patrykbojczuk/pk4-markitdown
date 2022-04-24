#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/textlineelement.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"
#include "../../../../markdown-document/markdown-elements/headerelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(HeaderElement, SetsLevelOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement element(textElement);

    HeaderElement header(MarkdownHeaderLevel::Level5, element);

    ASSERT_EQ(header.getLevel(), MarkdownHeaderLevel::Level5);
}

TEST(HeaderElement, SetsTextLineElementOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement element(textElement);

    HeaderElement header(MarkdownHeaderLevel::Level5, element);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
        retStr = std::get<Recursive<PlainTextElement>>(header.getText().getContents()[0])->getText();
    );

    ASSERT_STREQ(retStr.c_str(), L"Example text");
}

TEST(HeaderElement, ReturnsIdExistenceState){
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement element1(textElement1);
    HeaderElement header1(MarkdownHeaderLevel::Level5, element1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement element2(textElement2);
    HeaderElement header2(MarkdownHeaderLevel::Level5, element2, L"example_id");

    EXPECT_FALSE(header1.hasId());
    EXPECT_TRUE(header2.hasId());
}

TEST(HeaderElement, SetsEmptyIdIfNotDefined){
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement element(textElement);
    HeaderElement header(MarkdownHeaderLevel::Level5, element);

    EXPECT_STREQ(header.getId().c_str(), L"");
}
