#ifndef STRIKETHROUGHELEMENT_H
#define STRIKETHROUGHELEMENT_H

#include "nestedelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class StrikethroughElement : public NestedElement
        {
        public:
            StrikethroughElement(VInlineMarkdownElement& element);
        };
    };
};

#endif // STRIKETHROUGHELEMENT_H
