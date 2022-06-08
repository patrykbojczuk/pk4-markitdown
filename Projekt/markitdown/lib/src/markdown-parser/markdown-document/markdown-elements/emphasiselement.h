#ifndef EMPHASISELEMENT_H
#define EMPHASISELEMENT_H

#include "nestedelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class EmphasisElement : public NestedElement {
        public:
            EmphasisElement(VInlineMarkdownElement &element);
        };
    };
};

#endif // EMPHASISELEMENT_H
