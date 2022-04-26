#ifndef BLOCKQUOTETOKEN_H
#define BLOCKQUOTETOKEN_H

#include "plaintexttoken.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class BlockquoteToken : public PlainTextToken
        {
        public:
            BlockquoteToken(const std::wstring& text);
        };
    };
};

#endif // BLOCKQUOTETOKEN_H
