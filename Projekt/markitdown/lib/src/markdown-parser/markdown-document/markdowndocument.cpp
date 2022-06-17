#include "markdowndocument.h"

MarkdownParser::MarkdownDocument::MarkdownDocument::MarkdownDocument() {}

MarkdownParser::MarkdownDocument::MarkdownDocument::MarkdownDocument(MarkdownDocument &&old)
{
    elements.swap(old.elements);
}

MarkdownParser::MarkdownDocument::MarkdownDocument::MarkdownDocument(const MarkdownDocument &other)
{
    elements = other.elements;
}

void MarkdownParser::MarkdownDocument::MarkdownDocument::operator=(MarkdownDocument &&old)
{
    elements.swap(old.elements);
}

void MarkdownParser::MarkdownDocument::MarkdownDocument::operator=(const MarkdownDocument& other)
{
    elements = other.elements;
}

void MarkdownParser::MarkdownDocument::MarkdownDocument::add(const VTopLevelMarkdownElement &line) {
    elements.push_back(line);
}

const std::vector<MarkdownParser::MarkdownDocument::VTopLevelMarkdownElement> &
MarkdownParser::MarkdownDocument::MarkdownDocument::getElements() const {
    return elements;
}

MarkdownParser::MarkdownDocument::VTopLevelMarkdownElement &
MarkdownParser::MarkdownDocument::MarkdownDocument::operator[](int pos) {
    return elements.at(pos);
}

const size_t MarkdownParser::MarkdownDocument::MarkdownDocument::size() const {
    return elements.size();
}

MarkdownParser::MarkdownDocument::VTopLevelMarkdownElement &MarkdownParser::MarkdownDocument::MarkdownDocument::back() {
    return elements.back();
}
