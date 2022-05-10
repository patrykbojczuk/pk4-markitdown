#ifndef VTOPLEVELMARKDOWNELEMENT_H
#define VTOPLEVELMARKDOWNELEMENT_H

#include <variant>
#include "recursivevarianttype.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        class ImageElement;

        class CodeblockElement;

        class HeaderElement;

        class ParagraphElement;

        class BlockquoteElement;

        class OrderedListElement;

        class UnorderedListElement;

        class HorizontalRuleElement;

        using VTopLevelMarkdownElement = std::variant<Recursive<ImageElement>,
                Recursive<CodeblockElement>,
                Recursive<HeaderElement>,
                Recursive<ParagraphElement>,
                Recursive<BlockquoteElement>,
                Recursive<OrderedListElement>,
                Recursive<UnorderedListElement>,
                Recursive<HorizontalRuleElement>>;
    };
};

#endif // VTOPLEVELMARKDOWNELEMENT_H
