#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/unorderedlistelement.h"
#include "../../../../markdown-document/markdown-elements/orderedlistelement.h"
#include "../../../../markdown-document/markdown-elements/multilinetextelement.h"
#include "../../../../markdown-document/markdown-elements/textlineelement.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(ListElements$UnorderedList, SetsTextLineElementOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine(textElement);
    MultilineTextElement text(textLine);
    UnorderedListElement ul(text);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
        retStr = std::get<Recursive<PlainTextElement>>(ul.getItems()[0].getLines()[0].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Example text");
}

TEST(ListElements$UnorderedList, AddsTextLineElements) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    UnorderedListElement ul(text1);

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ul.add(text2);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
        retStr = std::get<Recursive<PlainTextElement>>(ul.getItems()[1].getLines()[1].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Yet another text");
}

TEST(ListElements$OrderedList, SetsTextLineElementOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine(textElement);
    MultilineTextElement text(textLine);
    OrderedListElement ul(text);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
        retStr = std::get<Recursive<PlainTextElement>>(ul.getItems()[0].getLines()[0].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Example text");
}

TEST(ListElements$OrderedList, AddsTextLineElements) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    OrderedListElement ol(text1);

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ol.add(text2);

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
            retStr = std::get<Recursive<PlainTextElement>>(ol.getItems()[1].getLines()[1].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Yet another text");
}
