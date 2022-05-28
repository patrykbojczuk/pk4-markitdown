#ifndef MARKDOWNDOCUMENT_H
#define MARKDOWNDOCUMENT_H

#include <vector>
#include "markdown-elements/vtoplevelmarkdownelement.h"
#include "markdown-elements/emphasiselement.h"
#include "markdown-elements/inlinecodeelement.h"
#include "markdown-elements/linkelement.h"
#include "markdown-elements/strikethroughelement.h"
#include "markdown-elements/strongemphasiselement.h"
#include "markdown-elements/plaintextelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class MarkdownDocument {
        private:
            std::vector<VTopLevelMarkdownElement> elements;

        public:
            MarkdownDocument();

            void add(const VTopLevelMarkdownElement &line);

            const std::vector<VTopLevelMarkdownElement> &getElements() const;

            const size_t size() const;

            VTopLevelMarkdownElement &operator[](int pos);

            VTopLevelMarkdownElement &back();
        };
    };
};

#endif // MARKDOWNDOCUMENT_H
