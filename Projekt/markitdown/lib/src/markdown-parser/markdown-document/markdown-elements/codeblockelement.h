#ifndef CODEBLOCKELEMENT_H
#define CODEBLOCKELEMENT_H

#include <string>
#include <vector>
#include "plaintextelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class CodeblockElement
        {
        private:
            std::wstring language;
            std::vector<PlainTextElement> lines;
        public:
            CodeblockElement(const std::wstring& language);
            void add(const PlainTextElement& line);
            const std::vector<PlainTextElement>& getLines() const;
            const std::wstring& getLanguage() const;
        };
    };
};

#endif // CODEBLOCKELEMENT_H
