#ifndef PLAINTEXTTOKEN_H
#define PLAINTEXTTOKEN_H

#include <string>

namespace MarkdownParser {
    namespace MarkdownParser {
        class PlainTextToken
        {
        private:
            std::wstring text;
            std::wstring rawText;

        public:
            PlainTextToken(const std::wstring& text, const std::wstring& rawText = L"");
            const std::wstring& getText() const;
            bool hasRawText() const;
            const std::wstring& getRawText() const;
        };
    };
};

#endif // PLAINTEXTTOKEN_H
