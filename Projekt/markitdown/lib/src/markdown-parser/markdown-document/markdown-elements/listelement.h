#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <variant>
#include <vector>
#include "recursivevarianttype.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class MultilineTextElement;

        class UnorderedListElement;

        class ListElement {
        public:
            using VListItem = std::variant<Recursive<MultilineTextElement>, Recursive<UnorderedListElement>>;
        private:
            std::vector<VListItem> items;
        protected:
            ListElement(const VListItem &item);

        public:
            void add(const VListItem &item);

            const std::vector<VListItem> &getItems() const;

            VListItem &operator[](int pos);
        };
    };
};

#endif // LISTELEMENT_H
