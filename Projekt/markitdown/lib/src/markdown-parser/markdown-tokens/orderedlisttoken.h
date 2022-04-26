#ifndef ORDEREDLISTTOKEN_H
#define ORDEREDLISTTOKEN_H

#include "plaintexttoken.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class OrderedListToken : public PlainTextToken
        {
        public:
            OrderedListToken(const std::wstring& text);
        };
    };
};

#endif // ORDEREDLISTTOKEN_H
