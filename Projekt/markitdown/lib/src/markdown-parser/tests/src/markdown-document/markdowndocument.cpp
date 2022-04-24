#include "gtest/gtest.h"
#include "../../../../markdown-document/markdowndocument.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(MarkdownDocument, AddsTopLevelElements) {
    MarkdownDocument document;
    document.add(ImageElement(L"https://example.com/image.png", L"Example image"));

    EXPECT_STREQ(std::get<ImageElement>(document.getElements()[0]).getUrl().c_str(), L"https://example.com/image.png");
    EXPECT_STREQ(std::get<ImageElement>(document.getElements()[0]).getText().c_str(), L"Example image");
}

TEST(MarkdownDocument, ThrowsOnOutOfRangeIndex) {
    MarkdownDocument document;
    document.add(ImageElement(L"https://example.com/image.png", L"Example image"));

    EXPECT_NO_THROW(document[0]);
    EXPECT_THROW(document[1], std::out_of_range);
}

TEST(MarkdownDocument, ReturnsElementOnIndex) {
    MarkdownDocument document;
    ImageElement image(L"https://example.com/image.png", L"Example image");
    document.add(image);
    CodeblockElement codeBlock(L"typescript");
    document.add(codeBlock);

    EXPECT_NO_THROW(std::get<ImageElement>(document[0]));
    EXPECT_THROW(std::get<ImageElement>(document[1]), std::bad_variant_access);
}
