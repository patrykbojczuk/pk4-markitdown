#ifndef BLOCKQUOTEELEMENT_H
#define BLOCKQUOTEELEMENT_H

#include <stack>
#include "multilinetextelement.h"
#include "../markdowndocument.h"
#include "../../markdownparser.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class BlockquoteElement {
        private:
            std::wstring blockquoteBuffer = L"";
            MarkdownDocument document;

        public:
            BlockquoteElement(const std::wstring &line);

            const MarkdownDocument &getDocument();

            void parse();

            void addLine(const std::wstring &line);
        };
    };
};

#endif // BLOCKQUOTEELEMENT_H
