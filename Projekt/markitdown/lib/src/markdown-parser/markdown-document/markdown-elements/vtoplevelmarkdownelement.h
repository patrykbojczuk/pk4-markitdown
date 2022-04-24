#ifndef VTOPLEVELMARKDOWNELEMENT_H
#define VTOPLEVELMARKDOWNELEMENT_H

#include <variant>
#include "blockquoteelement.h"
#include "codeblockelement.h"
#include "headerelement.h"
#include "horizontalruleelement.h"
#include "imageelement.h"
#include "orderedlistelement.h"
#include "paragraphelement.h"
#include "unorderedlistelement.h"

namespace MarkdownParser {
    namespace MarkdownDocument {
        using VTopLevelMarkdownElement = std::variant<ImageElement,
                                                      CodeblockElement,
                                                      HeaderElement,
                                                      ParagraphElement,
                                                      BlockquoteElement,
                                                      OrderedListElement,
                                                      UnorderedListElement,
                                                      HorizontalRuleElement>;
    };
};

#endif // VTOPLEVELMARKDOWNELEMENT_H
