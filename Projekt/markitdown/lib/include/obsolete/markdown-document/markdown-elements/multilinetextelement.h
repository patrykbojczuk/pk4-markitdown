#ifndef MULTILINETEXTELEMENT_H
#define MULTILINETEXTELEMENT_H

#include <vector>
#include "textlineelement.h"

namespace MarkdownParser
{
    namespace MarkdownDocument
    {
        class MultilineTextElement
        {
        public:
            MultilineTextElement(const TextLineElement &line);
            void add(const TextLineElement &line);
            const std::vector<TextLineElement> &getLines() const;
            TextLineElement &operator[](int pos);
        };
    };
};

#endif // MULTILINETEXTELEMENT_H
