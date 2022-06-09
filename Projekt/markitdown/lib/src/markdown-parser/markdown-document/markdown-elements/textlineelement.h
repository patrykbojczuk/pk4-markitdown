#ifndef TEXTLINEELEMENT_H
#define TEXTLINEELEMENT_H

#include "vinlinemarkdownelement.h"
#include <vector>

namespace MarkdownParser {
    namespace MarkdownDocument {
        class TextLineElement {
            std::vector<VInlineMarkdownElement> contents;

        public:
            TextLineElement() = default;

            TextLineElement(VInlineMarkdownElement &element);

            void add(VInlineMarkdownElement &element);

            const std::vector<VInlineMarkdownElement> &getContents() const;

            VInlineMarkdownElement &operator[](int pos);

            void push_back_many(typename std::vector<VInlineMarkdownElement>::iterator begin,
                                typename std::vector<VInlineMarkdownElement>::iterator end);
        };
    };
};

#endif // TEXTLINEELEMENT_H
