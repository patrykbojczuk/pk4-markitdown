#include "gtest/gtest.h"
#include "../../markdownparser.h"

//using namespace MarkdownParser::MarkdownParser;

template<class... Ts>
struct overloaded : Ts ... {
    using Ts::operator()...;
};

TEST(MarkdownParser, Combination) {
    auto parsed = MarkdownParser::MarkdownParser::MarkdownParser::parse(LR";(##### Sed sed placerat elit.
Nunc ac rhoncus risus. Phasellus viverra erat quis tempus bibendum. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.
- - -
- First element
- Second element
  - Subelement
- Third element

1. First element
2. Second element
  - Subelement
3. Third element

>Nullam vel lorem eu risus dapibus posuere.
>>Aliquam venenatis luctus malesuada.

```typescript
const isPrime = (num: number) => {
    for (let i = 2; i*i <= num; ++i) {
        if (!(num % i)) {
            return false
        }
    }
    return num >= 2
}
```

[Link test](https://example.com)

Curabitur id eros leo.
---

Duis ornare libero varius quam blandit, id lobortis ante ultrices. Morbi rutrum et lectus ut mollis. Nulla magna ante, congue ut purus non, accumsan finibus lacus. Sed tincidunt placerat enim, ac placerat nisl semper elementum.
);");

    for (const auto &el: parsed.getElements()) {
        std::visit(overloaded{
                [](const Recursive<MarkdownParser::MarkdownDocument::BlockquoteElement> &el) {
                    //
                    std::cout << "blockquote\n";
                },
                [](const Recursive<MarkdownParser::MarkdownDocument::CodeblockElement> &el) {
                    //
                    std::cout << "codeblock\n";
                },
                [](const Recursive<MarkdownParser::MarkdownDocument::HeaderElement> &el) {
                    //
                    std::cout << "header\n";
                },
                [](const Recursive<MarkdownParser::MarkdownDocument::HorizontalRuleElement> &el) {
                    //
                    std::cout << "horizontal rule\n";
                },
                [](const Recursive<MarkdownParser::MarkdownDocument::OrderedListElement> &el) {
                    //
                    std::cout << "ol\n";
                },
                [](const Recursive<MarkdownParser::MarkdownDocument::UnorderedListElement> &el) {
                    //
                    std::cout << "ul\n";
                },
                [](const Recursive<MarkdownParser::MarkdownDocument::ParagraphElement> &el) {
                    //
                    std::cout << "para\n";
                },
                [](auto &el) {
                    std::cout << "auto\n";
                }
        }, el);
    }
}
