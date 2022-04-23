#include "plaintextelement.h"


MarkdownParser::MarkdownDocument::PlainTextElement::PlainTextElement(const std::wstring &text): text(text) { }

const std::wstring& MarkdownParser::MarkdownDocument::PlainTextElement::getText() const
{
    return text;
}
