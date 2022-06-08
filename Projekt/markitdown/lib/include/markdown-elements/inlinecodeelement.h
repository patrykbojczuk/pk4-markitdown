#ifndef INLINECODEELEMENT_H
#define INLINECODEELEMENT_H

#include "plaintextelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class InlineCodeElement : public PlainTextElement
        {
        public:
            InlineCodeElement(const std::wstring& text);
        };
    };
};

#endif // INLINECODEELEMENT_H
