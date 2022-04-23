#include "linkelement.h"

MarkdownParser::MarkdownDocument::LinkElement::LinkElement(const std::wstring &url, const std::wstring &text, const std::wstring &title) : LinkableElement(url, text, title) { }
