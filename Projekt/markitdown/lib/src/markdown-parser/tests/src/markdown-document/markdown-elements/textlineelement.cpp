#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/textlineelement.h"
#include "../../../../markdown-document/markdown-elements/emphasiselement.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(TextLineElement, SetsInlineElementOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    VInlineMarkdownElement emphasisElement(make_recursive<EmphasisElement>(textElement));
    TextLineElement element(emphasisElement);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
        retStr = std::get<Recursive<PlainTextElement>>(std::get<Recursive<EmphasisElement>>(element.getContents()[0])->getElement())->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Example text");
}

TEST(TextLineElement, AddsInlineElements) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    VInlineMarkdownElement emphasisElement(make_recursive<EmphasisElement>(textElement));
    TextLineElement element(emphasisElement);
    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    element.add(textElement2);
    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Yet another text"));
    element.add(textElement3);

    std::wstring retStr1 = L"", retStr2 = L"";

    ASSERT_NO_THROW(
        retStr1 = std::get<Recursive<PlainTextElement>>(element.getContents()[1])->getText();
        retStr2 = std::get<Recursive<PlainTextElement>>(element.getContents()[2])->getText();
    );
    EXPECT_STREQ(retStr1.c_str(), L"Another text");
    EXPECT_STREQ(retStr2.c_str(), L"Yet another text");
}
