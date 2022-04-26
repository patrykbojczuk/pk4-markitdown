#include "codetoken.h"

MarkdownParser::MarkdownParser::CodeToken::CodeToken(std::wstring language)
{
    this->language = language;
}

const std::wstring& MarkdownParser::MarkdownParser::CodeToken::getLanguage() const
{
    return language;
}
