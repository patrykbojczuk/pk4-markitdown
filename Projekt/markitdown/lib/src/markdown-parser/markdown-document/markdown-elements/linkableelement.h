#ifndef LINKABLEELEMENT_H
#define LINKABLEELEMENT_H

#include "plaintextelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class LinkableElement : public PlainTextElement
        {
        private:
            std::wstring url;
            std::wstring title;
        protected:
            LinkableElement(const std::wstring& url, const std::wstring& text, const std::wstring& title = L"");
        public:
            const std::wstring& getUrl() const;
            bool hasTitle() const;
            const std::wstring& getTitle() const;
        };
    };
};

#endif // LINKABLEELEMENT_H
