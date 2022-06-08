#ifndef NESTEDELEMENT_H
#define NESTEDELEMENT_H

#include "vinlinemarkdownelement.h"
#include "textlineelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class NestedElement : public TextLineElement {
        public:
            NestedElement(VInlineMarkdownElement &element);
        };
    };
};

#endif // NESTEDELEMENT_H
