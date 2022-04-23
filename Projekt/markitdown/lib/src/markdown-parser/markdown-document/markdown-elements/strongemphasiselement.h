#ifndef STRONGEMPHASISELEMENT_H
#define STRONGEMPHASISELEMENT_H

#include "nestedelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class StrongEmphasisElement : public NestedElement
        {
        public:
            StrongEmphasisElement(VInlineMarkdownElement& element);
        };
    };
};

#endif // STRONGEMPHASISELEMENT_H
