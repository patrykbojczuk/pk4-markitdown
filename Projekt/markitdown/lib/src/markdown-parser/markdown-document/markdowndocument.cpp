#include "markdowndocument.h"

MarkdownParser::MarkdownDocument::MarkdownDocument::MarkdownDocument() { }

void MarkdownParser::MarkdownDocument::MarkdownDocument::add(const VTopLevelMarkdownElement& line)
{
    elements.push_back(line);
}

const std::vector<MarkdownParser::MarkdownDocument::VTopLevelMarkdownElement> &MarkdownParser::MarkdownDocument::MarkdownDocument::getElements() const
{
    return elements;
}

MarkdownParser::MarkdownDocument::VTopLevelMarkdownElement &MarkdownParser::MarkdownDocument::MarkdownDocument::operator[](int pos) {
    return elements.at(pos);
}
