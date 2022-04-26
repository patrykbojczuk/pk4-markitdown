#ifndef HEADERTOKEN_H
#define HEADERTOKEN_H

#include "plaintexttoken.h"
#include "../markdownheaderlevel.enum.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class HeaderToken : public PlainTextToken
        {
        private:
            MarkdownHeaderLevel level;
            std::wstring id;
        public:
            HeaderToken(MarkdownHeaderLevel level, const std::wstring& text, const std::wstring& id = L"");
            MarkdownHeaderLevel getLevel();
            bool hasId() const;
            const std::wstring& getId() const;
        };
    };
};

#endif // HEADERTOKEN_H
