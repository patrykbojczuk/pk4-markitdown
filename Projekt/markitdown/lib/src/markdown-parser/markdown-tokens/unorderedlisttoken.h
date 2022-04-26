#ifndef UNORDEREDLISTTOKEN_H
#define UNORDEREDLISTTOKEN_H

#include "plaintexttoken.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class UnorderedListToken : public PlainTextToken
        {
        public:
            UnorderedListToken(const std::wstring& text);
        };
    };
};

#endif // UNORDEREDLISTTOKEN_H
