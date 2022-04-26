#ifndef HEADERUNDERLINETOKEN_H
#define HEADERUNDERLINETOKEN_H

#include "../markdownheaderlevel.enum.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class HeaderUnderlineToken
        {
        private:
            bool isLevel1;
        public:
            HeaderUnderlineToken(MarkdownHeaderLevel level);
            MarkdownHeaderLevel getLevel() const;
        };
    };
};

#endif // HEADERUNDERLINETOKEN_H
