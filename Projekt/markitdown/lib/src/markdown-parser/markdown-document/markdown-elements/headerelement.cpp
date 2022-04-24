#include "headerelement.h"

MarkdownParser::MarkdownDocument::HeaderElement::HeaderElement(MarkdownHeaderLevel level, const TextLineElement &text, const std::wstring& id) : level(level), text(text), id(id) { }

MarkdownHeaderLevel MarkdownParser::MarkdownDocument::HeaderElement::getLevel() const
{
    return level;
}

const MarkdownParser::MarkdownDocument::TextLineElement& MarkdownParser::MarkdownDocument::HeaderElement::getText() const
{
    return text;
}

bool MarkdownParser::MarkdownDocument::HeaderElement::hasId() const {
    return id.length();
}

const std::wstring &MarkdownParser::MarkdownDocument::HeaderElement::getId() const {
    return id;
}
