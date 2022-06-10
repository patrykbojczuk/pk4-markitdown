#ifndef LINKELEMENT_H
#define LINKELEMENT_H

#include "linkableelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class LinkElement : public LinkableElement
        {
        public:
            LinkElement(const std::wstring& url, const std::wstring& text, const std::wstring& title = L"");
        };
    };
};

#endif // LINKELEMENT_H
