#ifndef LINKABLEREFERENCE_H
#define LINKABLEREFERENCE_H

#include <string>
#include "markdown-tokens/rawtexthandler.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        struct LinkableReference {
            std::wstring url;
            std::wstring title;
            std::wstring rawText;
        };
    };
};

#endif // LINKABLEREFERENCE_H
