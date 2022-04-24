#include "codeblockelement.h"

MarkdownParser::MarkdownDocument::CodeblockElement::CodeblockElement(const std::wstring &language) : language(language) { }

void MarkdownParser::MarkdownDocument::CodeblockElement::add(const PlainTextElement &line)
{
    lines.push_back(line);
}

const std::vector<MarkdownParser::MarkdownDocument::PlainTextElement> &MarkdownParser::MarkdownDocument::CodeblockElement::getLines() const
{
    return lines;
}

const std::wstring &MarkdownParser::MarkdownDocument::CodeblockElement::getLanguage() const {
    return language;
}

MarkdownParser::MarkdownDocument::PlainTextElement &MarkdownParser::MarkdownDocument::CodeblockElement::operator[](int pos) {
    return lines.at(pos);
}
