#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H

#include <string>
#include "markdown-document/markdowndocument.h"

namespace MarkdownParser
{
    namespace MarkdownParser
    {
        class MarkdownParser
        {
        public:
            static MarkdownDocument::MarkdownDocument parse(const std::wstring &markdown);

            enum ParserState
            {
                MainPass,
                CodeBlock,
                UnorderedList,
                OrderedList,
                Blockquote,
                Paragraph,
                Finished
            };
        };
    };
};

#endif // MARKDOWNPARSER_H
