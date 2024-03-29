#ifndef HEADERELEMENT_H
#define HEADERELEMENT_H

#include <string>
#include "textlineelement.h"
#include "../../markdownheaderlevel.enum.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class HeaderElement {
        private:
            MarkdownHeaderLevel level;
            TextLineElement text;
            std::wstring id;
        public:
            HeaderElement(MarkdownHeaderLevel level, const TextLineElement &text, const std::wstring &id = L"");

            MarkdownHeaderLevel getLevel() const;

            const TextLineElement &getText() const;

            bool hasId() const;

            const std::wstring &getId() const;
        };
    };
};

#endif // HEADERELEMENT_H
