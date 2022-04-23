#include "linkableelement.h"

MarkdownParser::MarkdownDocument::LinkableElement::LinkableElement(const std::wstring &url, const std::wstring &text, const std::wstring &title) : PlainTextElement(text), url(url), title(title) { }

const std::wstring &MarkdownParser::MarkdownDocument::LinkableElement::getUrl() const
{
    return url;
}

bool MarkdownParser::MarkdownDocument::LinkableElement::hasTitle() const
{
    return title.length();
}

const std::wstring &MarkdownParser::MarkdownDocument::LinkableElement::getTitle() const
{
    return title;
}
