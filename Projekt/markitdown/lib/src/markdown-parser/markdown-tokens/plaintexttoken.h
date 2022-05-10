#ifndef PLAINTEXTTOKEN_H
#define PLAINTEXTTOKEN_H

#include <string>
#include "rawtexthandler.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class PlainTextToken : public RawTextHandler {
        private:
            std::wstring text;
            std::wstring rawText;

        public:
            PlainTextToken(const std::wstring &text, const std::wstring &rawText = L"");

            const std::wstring &getText() const;
        };
    };
};

#endif // PLAINTEXTTOKEN_H
