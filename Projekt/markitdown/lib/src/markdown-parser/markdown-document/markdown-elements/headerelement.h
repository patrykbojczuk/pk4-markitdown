#ifndef HEADERELEMENT_H
#define HEADERELEMENT_H

#include "textlineelement.h"
#include "../../markdownheaderlevel.enum.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class HeaderElement
        {
        private:
            MarkdownHeaderLevel level;
            TextLineElement text;
        public:
            HeaderElement(MarkdownHeaderLevel level, const TextLineElement& text);
            MarkdownHeaderLevel getLevel() const;
            const TextLineElement& getText() const;
        };
    };
};

#endif // HEADERELEMENT_H
