#ifndef HEADERUNDERLINETOKEN_H
#define HEADERUNDERLINETOKEN_H

#include "../markdownheaderlevel.enum.h"
#include "rawtexthandler.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class HeaderUnderlineToken : public RawTextHandler {
        private:
            bool isLevel1;
        public:
            HeaderUnderlineToken(MarkdownHeaderLevel level, const std::wstring &rawText = L"");

            MarkdownHeaderLevel getLevel() const;
        };
    };
};

#endif // HEADERUNDERLINETOKEN_H
