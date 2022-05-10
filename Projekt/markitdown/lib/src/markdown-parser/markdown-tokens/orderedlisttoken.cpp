#include "orderedlisttoken.h"

MarkdownParser::MarkdownParser::OrderedListToken::OrderedListToken(const std::wstring &text,
                                                                   const std::wstring &rawText) : PlainTextToken(text,
                                                                                                                 rawText) {}
