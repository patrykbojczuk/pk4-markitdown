#include "gtest/gtest.h"
#include "../../../../markdown-document/markdowndocument.h"
#include "../../../../markdown-document/markdown-elements/recursivevarianttype.h"
#include "../../../markdown-document/markdown-elements/imageelement.h"
#include "../../../markdown-document/markdown-elements/codeblockelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(MarkdownDocument, AddsTopLevelElements) {
    MarkdownDocument document;
    document.add(make_recursive<ImageElement>(L"https://example.com/image.png", L"Example image"));

    EXPECT_STREQ(std::get<Recursive<ImageElement>>(document.getElements()[0])->getUrl().c_str(),
                 L"https://example.com/image.png");
    EXPECT_STREQ(std::get<Recursive<ImageElement>>(document.getElements()[0])->getText().c_str(), L"Example image");
}

TEST(MarkdownDocument, ThrowsOnOutOfRangeIndex) {
    MarkdownDocument document;
    document.add(make_recursive<ImageElement>(L"https://example.com/image.png", L"Example image"));

    EXPECT_NO_THROW(document[0]);
    EXPECT_THROW(document[1], std::out_of_range);
}

TEST(MarkdownDocument, ReturnsElementOnIndex) {
    MarkdownDocument document;
    ImageElement image(L"https://example.com/image.png", L"Example image");
    document.add(Recursive<ImageElement>(&image));
    CodeblockElement codeBlock(L"typescript");
    document.add(Recursive<CodeblockElement>(&codeBlock));

    EXPECT_NO_THROW(std::get<Recursive<ImageElement>>(document[0]));
    EXPECT_THROW(std::get<Recursive<ImageElement>>(document[1]), std::bad_variant_access);
}
