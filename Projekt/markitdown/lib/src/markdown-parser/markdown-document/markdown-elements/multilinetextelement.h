#ifndef MULTILINETEXTELEMENT_H
#define MULTILINETEXTELEMENT_H

#include "textlineelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class MultilineTextElement
        {
        private:
            std::vector<TextLineElement> lines;
        public:
            MultilineTextElement(const TextLineElement& line);
            void add(const TextLineElement& line);
            const std::vector<TextLineElement>& getLines() const;
        };
    };
};

#endif // MULTILINETEXTELEMENT_H
