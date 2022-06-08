#ifndef PLAINTEXTELEMENT_H
#define PLAINTEXTELEMENT_H

#include <string>

namespace MarkdownParser
{
    namespace MarkdownDocument
    {
        class PlainTextElement
        {
        public:
            PlainTextElement(const std::wstring &text);
            const std::wstring &getText() const;
        };
    };
};

#endif // PLAINTEXTELEMENT_H
