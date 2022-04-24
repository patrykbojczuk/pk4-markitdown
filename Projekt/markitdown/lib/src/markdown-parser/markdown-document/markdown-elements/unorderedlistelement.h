#ifndef UNORDEREDLISTELEMENT_H
#define UNORDEREDLISTELEMENT_H

#include "listelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class UnorderedListElement : public ListElement
        {
        public:
            UnorderedListElement(MultilineTextElement& item);
        };
    };
};

#endif // UNORDEREDLISTELEMENT_H
