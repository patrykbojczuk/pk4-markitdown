#ifndef TEXTLINEELEMENT_H
#define TEXTLINEELEMENT_H

#include <vector>
#include "vinlinemarkdownelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class TextLineElement
        {
            std::vector<VInlineMarkdownElement> contents;
        public:
            TextLineElement(VInlineMarkdownElement& element);
            void add(VInlineMarkdownElement& element);
            const std::vector<VInlineMarkdownElement>& getContents() const;
        };
    };
};

#endif // TEXTLINEELEMENT_H
