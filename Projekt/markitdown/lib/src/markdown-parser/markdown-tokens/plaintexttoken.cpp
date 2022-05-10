#include "plaintexttoken.h"

MarkdownParser::MarkdownParser::PlainTextToken::PlainTextToken(const std::wstring &text, const std::wstring &rawText)
        : text(text), RawTextHandler(rawText) {}

const std::wstring &MarkdownParser::MarkdownParser::PlainTextToken::getText() const {
    return text;
}
