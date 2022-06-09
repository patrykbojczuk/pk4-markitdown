#ifndef PLAINTEXTELEMENT_H
#define PLAINTEXTELEMENT_H

#include <string>

namespace MarkdownParser {
    namespace MarkdownDocument {
        class PlainTextElement {
        private:
            std::wstring text;
        public:
            PlainTextElement() = default;

            PlainTextElement(const std::wstring &text);

            const std::wstring &getText() const;
        };
    };
};

#endif // PLAINTEXTELEMENT_H
