#include "textlineelement.h"

MarkdownParser::MarkdownDocument::TextLineElement::TextLineElement(VInlineMarkdownElement &element) {
    this->add(element);
}

void MarkdownParser::MarkdownDocument::TextLineElement::add(VInlineMarkdownElement &element) {
    contents.push_back(element);
}

const std::vector<MarkdownParser::MarkdownDocument::VInlineMarkdownElement> &
MarkdownParser::MarkdownDocument::TextLineElement::getContents() const {
    return contents;
}

MarkdownParser::MarkdownDocument::VInlineMarkdownElement &
MarkdownParser::MarkdownDocument::TextLineElement::operator[](int pos) {
    return contents.at(pos);
}

void MarkdownParser::MarkdownDocument::TextLineElement::push_back_many(
        std::vector<MarkdownParser::MarkdownDocument::VInlineMarkdownElement>::iterator begin,
        std::vector<MarkdownParser::MarkdownDocument::VInlineMarkdownElement>::iterator end) {
    contents.insert(std::end(contents), begin, end);
}
