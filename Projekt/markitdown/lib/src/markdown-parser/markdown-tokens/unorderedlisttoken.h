#ifndef UNORDEREDLISTTOKEN_H
#define UNORDEREDLISTTOKEN_H

#include "plaintexttoken.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class UnorderedListToken : public PlainTextToken {
        public:
            UnorderedListToken(const std::wstring &text, size_t indent = 0);

            const size_t getIndent() const;

        private:
            size_t indent;
        };
    };
};

#endif // UNORDEREDLISTTOKEN_H
