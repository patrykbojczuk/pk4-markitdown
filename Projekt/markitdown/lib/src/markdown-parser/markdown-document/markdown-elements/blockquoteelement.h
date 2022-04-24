#ifndef BLOCKQUOTEELEMENT_H
#define BLOCKQUOTEELEMENT_H

#include "multilinetextelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class BlockquoteElement : public MultilineTextElement
        {
        public:
            BlockquoteElement(const TextLineElement& line);
        };
    };
};

#endif // BLOCKQUOTEELEMENT_H
