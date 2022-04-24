#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/multilinetextelement.h"
#include "../../../../markdown-document/markdown-elements/textlineelement.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(MultilineTextElement, SetsTextLineElementOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine(textElement);
    MultilineTextElement text(textLine);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
        retStr = std::get<Recursive<PlainTextElement>>(text.getLines()[0].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Example text");
}

TEST(MultilineTextElement, AddsTextLineElements) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text.add(textLine2);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
        retStr = std::get<Recursive<PlainTextElement>>(text.getLines()[1].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Another text");
}
