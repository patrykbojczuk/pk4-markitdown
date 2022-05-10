#ifndef HORIZONTALRULETOKEN_H
#define HORIZONTALRULETOKEN_H

#include "rawtexthandler.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class HorizontalRuleToken : public RawTextHandler {
        public:
            HorizontalRuleToken(const std::wstring &rawText = L"");
        };
    };
};

#endif // HORIZONTALRULETOKEN_H
