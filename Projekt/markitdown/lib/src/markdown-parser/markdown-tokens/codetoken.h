#ifndef CODETOKEN_H
#define CODETOKEN_H

#include <string>

namespace MarkdownParser {
    namespace MarkdownParser {
        class CodeToken
        {
        private:
            std::wstring language;
        public:
            CodeToken(std::wstring language);
            const std::wstring& getLanguage() const;
        };
    };
};

#endif // CODETOKEN_H
