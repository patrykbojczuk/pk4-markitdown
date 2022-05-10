#include "headertoken.h"

MarkdownParser::MarkdownParser::HeaderToken::HeaderToken(MarkdownHeaderLevel level, const std::wstring &text,
                                                         const std::wstring &id, const std::wstring &rawText)
        : PlainTextToken(text, rawText), level(level), id(id) {}

MarkdownHeaderLevel MarkdownParser::MarkdownParser::HeaderToken::getLevel() const {
    return level;
}

bool MarkdownParser::MarkdownParser::HeaderToken::hasId() const {
    return id.length();
}

const std::wstring &MarkdownParser::MarkdownParser::HeaderToken::getId() const {
    return id;
}
