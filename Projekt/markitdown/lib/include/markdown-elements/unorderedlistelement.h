#ifndef UNORDEREDLISTELEMENT_H
#define UNORDEREDLISTELEMENT_H

#include "listelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class UnorderedListElement : public ListElement {
        public:
            UnorderedListElement(const VListItem &item);
        };
    };
};

#endif // UNORDEREDLISTELEMENT_H
