#include "blockquotetoken.h"

MarkdownParser::MarkdownParser::BlockquoteToken::BlockquoteToken(const std::wstring &text,
                                                                 const std::wstring &rawText) : PlainTextToken(text,
                                                                                                               rawText) {}
