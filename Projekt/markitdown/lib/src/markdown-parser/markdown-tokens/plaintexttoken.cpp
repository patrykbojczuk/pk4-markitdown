#include "plaintexttoken.h"

MarkdownParser::MarkdownParser::PlainTextToken::PlainTextToken(const std::wstring& text, const std::wstring& rawText): text(text), rawText(rawText) { }

const std::wstring &MarkdownParser::MarkdownParser::PlainTextToken::getText() const
{
    return text;
}

bool MarkdownParser::MarkdownParser::PlainTextToken::hasRawText() const {
    return rawText.length();
}

const std::wstring &MarkdownParser::MarkdownParser::PlainTextToken::getRawText() const
{
    return rawText;
}
