#include "unorderedlisttoken.h"

MarkdownParser::MarkdownParser::UnorderedListToken::UnorderedListToken(const std::wstring &text, size_t indent,
                                                                       const std::wstring &rawText)
        : PlainTextToken(
        text, rawText), indent(indent) {}

const size_t MarkdownParser::MarkdownParser::UnorderedListToken::getIndent() const {
    return indent;
}
