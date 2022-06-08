#ifndef IMAGEELEMENT_H
#define IMAGEELEMENT_H

#include "linkableelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class ImageElement : public LinkableElement
        {
        public:
            ImageElement(const std::wstring& url, const std::wstring& text, const std::wstring& title = L"");
        };
    };
};

#endif // IMAGEELEMENT_H
