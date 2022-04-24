#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include "multilinetextelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class ListElement
        {
        private:
            std::vector<MultilineTextElement> items;
        protected:
            ListElement(MultilineTextElement& item);
        public:
            void add(MultilineTextElement& item);
            const std::vector<MultilineTextElement>& getItems() const;
        };
    };
};

#endif // LISTELEMENT_H
