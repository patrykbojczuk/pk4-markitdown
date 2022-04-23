#ifndef NESTEDELEMENT_H
#define NESTEDELEMENT_H

#include "vinlinemarkdownelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {

        class NestedElement
        {
        private:
            VInlineMarkdownElement element;
        public:
            NestedElement(VInlineMarkdownElement& element);
            const VInlineMarkdownElement& getElement() const;
        };
    };
};

#endif // NESTEDELEMENT_H
