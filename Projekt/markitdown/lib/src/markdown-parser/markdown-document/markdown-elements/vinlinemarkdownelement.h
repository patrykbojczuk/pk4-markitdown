#ifndef VINLINEMARKDOWNELEMENT_H
#define VINLINEMARKDOWNELEMENT_H

#include <variant>
#include "recursivevarianttype.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class LinkElement;

        class PlainTextElement;

        class InlineCodeElement;

        class EmphasisElement;

        class StrikethroughElement;

        class StrongEmphasisElement;

        using VInlineMarkdownElement = std::variant<Recursive<LinkElement>,
                Recursive<PlainTextElement>,
                Recursive<InlineCodeElement>,
                Recursive<EmphasisElement>,
                Recursive<StrikethroughElement>,
                Recursive<StrongEmphasisElement>>;
    };
};

#endif // VINLINEMARKDOWNELEMENT_H
