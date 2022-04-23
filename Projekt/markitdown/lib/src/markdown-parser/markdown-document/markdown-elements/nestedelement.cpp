#include "nestedelement.h"

MarkdownParser::MarkdownDocument::NestedElement::NestedElement(VInlineMarkdownElement& element) : element(element) { }

const MarkdownParser::MarkdownDocument::VInlineMarkdownElement &MarkdownParser::MarkdownDocument::NestedElement::getElement() const
{
    return element;
}
