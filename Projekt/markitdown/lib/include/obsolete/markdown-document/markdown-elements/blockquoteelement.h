#ifndef BLOCKQUOTEELEMENT_H
#define BLOCKQUOTEELEMENT_H

#include <stack>
#include "multilinetextelement.h"
#include "../markdowndocument.h"

namespace MarkdownParser
{
    namespace MarkdownDocument
    {
        class BlockquoteElement
        {
        public:
            BlockquoteElement(const std::wstring &line);

            const MarkdownDocument &getDocument();

            void parse();

            void addLine(const std::wstring &line);
        };
    };
};

#endif // BLOCKQUOTEELEMENT_H
