#include "textlineelement.h"

MarkdownParser::MarkdownDocument::TextLineElement::TextLineElement(VInlineMarkdownElement &element)
{
    this->add(element);
}

void MarkdownParser::MarkdownDocument::TextLineElement::add(VInlineMarkdownElement &element)
{
    contents.push_back(element);
}

const std::vector<MarkdownParser::MarkdownDocument::VInlineMarkdownElement> &MarkdownParser::MarkdownDocument::TextLineElement::getContents() const
{
    return contents;
}
