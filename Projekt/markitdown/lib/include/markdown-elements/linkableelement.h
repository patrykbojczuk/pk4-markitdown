#ifndef LINKABLEELEMENT_H
#define LINKABLEELEMENT_H

#include "plaintextelement.h"

namespace MarkdownParser
{
    namespace MarkdownDocument
    {
        class LinkableElement : public PlainTextElement
        {
        public:
            const std::wstring &getUrl() const;
            bool hasTitle() const;
            const std::wstring &getTitle() const;
        };
    };
};

#endif // LINKABLEELEMENT_H
