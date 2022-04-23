#ifndef VINLINEMARKDOWNELEMENT_H
#define VINLINEMARKDOWNELEMENT_H

#include <variant>
#include <memory>

template <class T>
using Recursive = std::shared_ptr<T>;

template <class T, typename... _Args>
Recursive<T> make_recursive(_Args&&... __args){
    return std::make_shared<T>(std::forward<_Args>(__args)...);
}

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
