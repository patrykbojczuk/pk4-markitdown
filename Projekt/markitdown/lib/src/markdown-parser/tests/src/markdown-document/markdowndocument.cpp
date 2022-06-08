#include "gtest/gtest.h"
#include "../../../../markdown-document/markdowndocument.h"
#include "../../../../markdown-document/markdown-elements/recursivevarianttype.h"
#include "../../../markdown-document/markdown-elements/headerelement.h"
#include "../../../markdown-document/markdown-elements/codeblockelement.h"
#include "../../../markdownheaderlevel.enum.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(MarkdownDocument, AddsTopLevelElements) {
    MarkdownDocument document;
    VInlineMarkdownElement text = make_recursive<PlainTextElement>(L"Example header");
    document.add(make_recursive<HeaderElement>(MarkdownHeaderLevel::Level1, TextLineElement(text), L"ex_header"));

    EXPECT_STREQ(std::get<Recursive<PlainTextElement>>(
            std::get<Recursive<HeaderElement>>(
                    document.getElements()[0])->getText().getContents()[0])->getText().c_str(),
                 L"Example header");
    EXPECT_STREQ(std::get<Recursive<HeaderElement>>(document.getElements()[0])->getId().c_str(),
                 L"ex_header");
}

TEST(MarkdownDocument, ThrowsOnOutOfRangeIndex) {
    MarkdownDocument document;
    VInlineMarkdownElement text = make_recursive<PlainTextElement>(L"Example header");
    document.add(make_recursive<HeaderElement>(MarkdownHeaderLevel::Level1, TextLineElement(text), L"ex_header"));

    EXPECT_NO_THROW(document[0]);
    EXPECT_THROW(document[1], std::out_of_range);
}

TEST(MarkdownDocument, ReturnsElementOnIndex) {
    MarkdownDocument document;
    VInlineMarkdownElement text = make_recursive<PlainTextElement>(L"Example header");
    HeaderElement header(MarkdownHeaderLevel::Level1, TextLineElement(text), L"ex_header");
    document.add(Recursive<HeaderElement>(&header));
    CodeblockElement codeBlock(L"typescript");
    document.add(Recursive<CodeblockElement>(&codeBlock));

    EXPECT_NO_THROW(std::get<Recursive<HeaderElement>>(document[0]));
    EXPECT_THROW(std::get<Recursive<HeaderElement>>(document[1]), std::bad_variant_access);
}
