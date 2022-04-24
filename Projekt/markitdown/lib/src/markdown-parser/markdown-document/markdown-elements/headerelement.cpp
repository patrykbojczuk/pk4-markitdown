#include "headerelement.h"

MarkdownParser::MarkdownDocument::HeaderElement::HeaderElement(MarkdownHeaderLevel level, const TextLineElement &text) : level(level), text(text) { }

MarkdownHeaderLevel MarkdownParser::MarkdownDocument::HeaderElement::getLevel() const
{
    return level;
}

const MarkdownParser::MarkdownDocument::TextLineElement& MarkdownParser::MarkdownDocument::HeaderElement::getText() const
{
    return text;
}
