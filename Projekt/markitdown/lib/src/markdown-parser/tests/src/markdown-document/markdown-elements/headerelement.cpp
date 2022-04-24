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
