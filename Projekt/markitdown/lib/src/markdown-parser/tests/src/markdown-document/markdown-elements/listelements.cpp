#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/unorderedlistelement.h"
#include "../../../../markdown-document/markdown-elements/orderedlistelement.h"
#include "../../../../markdown-document/markdown-elements/multilinetextelement.h"
#include "../../../../markdown-document/markdown-elements/textlineelement.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(ListElements$UnorderedList, SetsMultilineTextElementOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine(textElement);
    UnorderedListElement ul((ListElement::VListItem(make_recursive<MultilineTextElement>(textLine))));

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
            retStr = std::get<Recursive<PlainTextElement>>(std::get<Recursive<MultilineTextElement>>(
                    ul.getItems()[0])->getLines()[0].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Example text");
}

TEST(ListElements$UnorderedList, AddsMultilineTextElements) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    UnorderedListElement ul((ListElement::VListItem(make_recursive<MultilineTextElement>(text1))));

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ul.add(ListElement::VListItem(make_recursive<MultilineTextElement>(text2)));

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
            retStr = std::get<Recursive<PlainTextElement>>(std::get<Recursive<MultilineTextElement>>(
                    ul.getItems()[1])->getLines()[1].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Yet another text");
}

TEST(ListElements$UnorderedList, ThrowsOnOutOfRangeIndex) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    UnorderedListElement ul((ListElement::VListItem(make_recursive<MultilineTextElement>(text1))));

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ul.add(ListElement::VListItem(make_recursive<MultilineTextElement>(text2)));

    EXPECT_NO_THROW(ul[1]);
    EXPECT_THROW(ul[9], std::out_of_range);
}

TEST(ListElements$UnorderedList, ReturnsElementOnIndex) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    UnorderedListElement ul((ListElement::VListItem(make_recursive<MultilineTextElement>(text1))));

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ul.add(ListElement::VListItem(make_recursive<MultilineTextElement>(text2)));

    EXPECT_STREQ(std::get<Recursive<PlainTextElement>>(
            std::get<Recursive<MultilineTextElement>>(ul[0])->getLines()[0].getContents()[0])->getText().c_str(),
                 L"Example text");
    EXPECT_STREQ(std::get<Recursive<PlainTextElement>>(
            std::get<Recursive<MultilineTextElement>>(ul[1])->getLines()[1].getContents()[0])->getText().c_str(),
                 L"Yet another text");
}

TEST(ListElements$OrderedList, SetsMultilineTextElementOnConstruction) {
    VInlineMarkdownElement textElement(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine(textElement);
    MultilineTextElement text(textLine);
    OrderedListElement ul((ListElement::VListItem(make_recursive<MultilineTextElement>(text))));

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
            retStr = std::get<Recursive<PlainTextElement>>(std::get<Recursive<MultilineTextElement>>(
                    ul.getItems()[0])->getLines()[0].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Example text");
}

TEST(ListElements$OrderedList, AddsMultilineTextElements) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    OrderedListElement ol((ListElement::VListItem(make_recursive<MultilineTextElement>(text1))));

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ol.add(ListElement::VListItem(make_recursive<MultilineTextElement>(text2)));

    std::wstring retStr = L"";

    ASSERT_NO_THROW(
            retStr = std::get<Recursive<PlainTextElement>>(std::get<Recursive<MultilineTextElement>>(
                    ol.getItems()[1])->getLines()[1].getContents()[0])->getText();
    );
    EXPECT_STREQ(retStr.c_str(), L"Yet another text");
}

TEST(ListElements$OrderedList, ThrowsOnOutOfRangeIndex) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    OrderedListElement ol((ListElement::VListItem(make_recursive<MultilineTextElement>(text1))));

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ol.add(ListElement::VListItem(make_recursive<MultilineTextElement>(text2)));

    EXPECT_NO_THROW(ol[1]);
    EXPECT_THROW(ol[9], std::out_of_range);
}

TEST(ListElements$OrderedList, ReturnsElementOnIndex) {
    VInlineMarkdownElement textElement1(make_recursive<PlainTextElement>(L"Example text"));
    TextLineElement textLine1(textElement1);
    MultilineTextElement text1(textLine1);

    VInlineMarkdownElement textElement2(make_recursive<PlainTextElement>(L"Another text"));
    TextLineElement textLine2(textElement2);
    text1.add(textLine2);

    OrderedListElement ol((ListElement::VListItem(make_recursive<MultilineTextElement>(text1))));

    VInlineMarkdownElement textElement3(make_recursive<PlainTextElement>(L"Next example text"));
    TextLineElement textLine3(textElement3);
    MultilineTextElement text2(textLine3);
    VInlineMarkdownElement textElement4(make_recursive<PlainTextElement>(L"Yet another text"));
    TextLineElement textLine4(textElement4);
    text2.add(textLine4);

    ol.add(ListElement::VListItem(make_recursive<MultilineTextElement>(text2)));

    EXPECT_STREQ(std::get<Recursive<PlainTextElement>>(
            std::get<Recursive<MultilineTextElement>>(ol[0])->getLines()[0].getContents()[0])->getText().c_str(),
                 L"Example text");
    EXPECT_STREQ(std::get<Recursive<PlainTextElement>>(
            std::get<Recursive<MultilineTextElement>>(ol[1])->getLines()[1].getContents()[0])->getText().c_str(),
                 L"Yet another text");
}
