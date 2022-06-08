#ifndef HEADERELEMENT_H
#define HEADERELEMENT_H

#include "textlineelement.h"
#include "../../markdownheaderlevel.enum.h"

namespace MarkdownParser
{
    namespace MarkdownDocument
    {
        class HeaderElement
        {
            HeaderElement(MarkdownHeaderLevel level, const TextLineElement &text, const std::wstring &id = L"");
            MarkdownHeaderLevel getLevel() const;
            const TextLineElement &getText() const;
            bool hasId() const;
            const std::wstring &getId() const;
        };
    };
};

#endif // HEADERELEMENT_H
