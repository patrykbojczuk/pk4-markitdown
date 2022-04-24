#ifndef ORDEREDLISTELEMENT_H
#define ORDEREDLISTELEMENT_H

#include "listelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class OrderedListElement : public ListElement
        {
        public:
            OrderedListElement(MultilineTextElement& item);
        };
    };
};

#endif // ORDEREDLISTELEMENT_H
