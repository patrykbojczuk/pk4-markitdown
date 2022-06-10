#ifndef PARAGRAPHELEMENT_H
#define PARAGRAPHELEMENT_H

#include "multilinetextelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class ParagraphElement : public MultilineTextElement
        {
        public:
            ParagraphElement(const TextLineElement& line);
        };
    };
};

#endif // PARAGRAPHELEMENT_H
