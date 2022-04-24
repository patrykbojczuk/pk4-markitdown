#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/codeblockelement.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(CodeBlockElement, SetsLanguageOnConstruction) {
    CodeblockElement element(L"javascript");
    ASSERT_STREQ(element.getLanguage().c_str(), L"javascript");
}

TEST(CodeBlockElement, AddsPlainTextElements) {
    CodeblockElement element(L"typescript");
    element.add(PlainTextElement(L"const sum = (arr: number[]): number => {"));
    element.add(PlainTextElement(L"    let x = 0"));
    element.add(PlainTextElement(L"    arr.forEach((v) => {"));
    element.add(PlainTextElement(L"        x += v"));
    element.add(PlainTextElement(L"    })"));
    element.add(PlainTextElement(L"    return x"));
    element.add(PlainTextElement(L"}"));

    ASSERT_STREQ(element.getLines()[2].getText().c_str(), L"    arr.forEach((v) => {");
    ASSERT_STRNE(element.getLines()[6].getText().c_str(), L"{");
}
