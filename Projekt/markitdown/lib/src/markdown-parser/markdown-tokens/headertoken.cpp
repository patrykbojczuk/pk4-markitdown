#include "headertoken.h"

MarkdownParser::MarkdownParser::HeaderToken::HeaderToken(MarkdownHeaderLevel level, const std::wstring& text, const std::wstring& id) : PlainTextToken(text), level(level), id(id) { }

MarkdownHeaderLevel MarkdownParser::MarkdownParser::HeaderToken::getLevel()
{
    return level;
}

bool MarkdownParser::MarkdownParser::HeaderToken::hasId() const
{
    return id.length();
}

const std::wstring& MarkdownParser::MarkdownParser::HeaderToken::getId() const
{
    return id;
}