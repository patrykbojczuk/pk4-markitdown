#include "gtest/gtest.h"
#include "../../../../markdown-document/markdown-elements/nestedelement.h"
#include "../../../../markdown-document/markdown-elements/plaintextelement.h"
#include "../../../../markdown-document/markdown-elements/emphasiselement.h"
#include "../../../../markdown-document/markdown-elements/strikethroughelement.h"
#include "../../../../markdown-document/markdown-elements/strongemphasiselement.h"
#include "../../../../markdown-document/markdown-elements/inlinecodeelement.h"
#include "../../../../markdown-document/markdown-elements/linkelement.h"

using namespace MarkdownParser::MarkdownDocument;

TEST(NestableElements, CanNestLeaves){
    EXPECT_NO_THROW(
        VInlineMarkdownElement text{make_recursive<PlainTextElement>(L"Example text")};
        EmphasisElement emphasisElement(text);

        std::get<Recursive<PlainTextElement>>(emphasisElement.getElement())->getText();
    );
    EXPECT_NO_THROW(
        VInlineMarkdownElement inlineCode{make_recursive<InlineCodeElement>(L"javascript")};
        EmphasisElement emphasisElement(inlineCode);

        std::get<Recursive<InlineCodeElement>>(emphasisElement.getElement())->getText();
    );
    EXPECT_NO_THROW(
        VInlineMarkdownElement link{make_recursive<LinkElement>(L"https://example.com", L"Example text")};
        EmphasisElement emphasisElement(link);

        std::get<Recursive<LinkElement>>(emphasisElement.getElement())->getText();
    );
}

TEST(NestableElements, CanNestNestablesAndLeaves){
    EXPECT_NO_THROW(
            VInlineMarkdownElement text{make_recursive<PlainTextElement>(L"Example text")};
            VInlineMarkdownElement emphasisElement{make_recursive<EmphasisElement>(text)};
            StrikethroughElement strikethroughElement{emphasisElement};

            std::get<Recursive<PlainTextElement>>(
                std::get<Recursive<EmphasisElement>>(strikethroughElement.getElement())->getElement()
            )->getText();
    );
}
