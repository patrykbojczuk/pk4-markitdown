#include "imageelement.h"

MarkdownParser::MarkdownDocument::ImageElement::ImageElement(const std::wstring &url, const std::wstring &text, const std::wstring &title) : LinkableElement(url, text, title) { }
