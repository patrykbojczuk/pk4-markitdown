#include "blockquoteelement.h"
#include "../../markdownparser.h"

MarkdownParser::MarkdownDocument::BlockquoteElement::BlockquoteElement(const std::wstring &line) : blockquoteBuffer(
        line) {}

void MarkdownParser::MarkdownDocument::BlockquoteElement::parse() {
    document = MarkdownParser::MarkdownParser::MarkdownParser::parse(blockquoteBuffer);
}

const MarkdownParser::MarkdownDocument::MarkdownDocument &
MarkdownParser::MarkdownDocument::BlockquoteElement::getDocument() {
    return document;
}

void MarkdownParser::MarkdownDocument::BlockquoteElement::addLine(const std::wstring &line) {
    blockquoteBuffer += L"\n" + line;
}
