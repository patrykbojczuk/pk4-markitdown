#include <stack>
#include "markdownparser.h"
#include "markdown-document/markdown-elements/recursivevarianttype.h"
#include "markdown-document/markdown-elements/blockquoteelement.h"
#include "markdown-document/markdown-elements/codeblockelement.h"
#include "markdown-document/markdown-elements/emphasiselement.h"
#include "markdown-document/markdown-elements/headerelement.h"
#include "markdown-document/markdown-elements/horizontalruleelement.h"
#include "markdown-document/markdown-elements/imageelement.h"
#include "markdown-document/markdown-elements/inlinecodeelement.h"
#include "markdown-document/markdown-elements/linkableelement.h"
#include "markdown-document/markdown-elements/linkelement.h"
#include "markdown-document/markdown-elements/multilinetextelement.h"
#include "markdown-document/markdown-elements/orderedlistelement.h"
#include "markdown-document/markdown-elements/unorderedlistelement.h"
#include "markdown-document/markdown-elements/paragraphelement.h"
#include "markdown-document/markdown-elements/plaintextelement.h"
#include "markdown-document/markdown-elements/strikethroughelement.h"
#include "markdown-document/markdown-elements/strongemphasiselement.h"
#include "markdown-document/markdown-elements/textlineelement.h"
#include "markdown-document/markdown-elements/unorderedlistelement.h"
#include "markdowninlineelementsparser.h"

MarkdownParser::MarkdownParser::MarkdownParser::MarkdownParser(const std::wstring &markdown) : tokenizer(markdown) {
    indentLevel.push(0);
}

template<class... Ts>
struct overloaded : Ts ... {
    using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

MarkdownParser::MarkdownDocument::MarkdownDocument MarkdownParser::MarkdownParser::MarkdownParser::docFromTokens() {
    auto &tokens = tokenizer.getTokens();
    stateStack.push(ParserState::MainPass);

    // Starting from i = 1 so nextToken doesn't go out of range
    for (stateMachineTokenIndex = 1; stateMachineTokenIndex < tokens.size(); ++stateMachineTokenIndex) {
        auto &currentToken = tokens[stateMachineTokenIndex - 1];
        auto &nextToken = tokens[stateMachineTokenIndex];

        switch (stateStack.top()) {
            case ParserState::MainPass: {
                stateMachineMainPassOp(currentToken, nextToken);
                break;
            }
            case ParserState::Blockquote: {
                stateMachineBlockquoteOp(currentToken, nextToken);
                break;
            }
            case ParserState::CodeBlock: {
                stateMachineCodeBlockOp(currentToken, nextToken);
                break;
            }
            case ParserState::UnorderedList: {
                stateMachineUnorderedListOp(currentToken, nextToken);
                break;
            }
            case ParserState::OrderedList: {
                stateMachineOrderedListOp(currentToken, nextToken);
                break;
            }
            case ParserState::Paragraph: {
                stateMachineParagraphOp(currentToken, nextToken);
                break;
            }
        }
    }

    stateStack.pop();
    stateStack.push(ParserState::Finished);

    return std::move(document);
}

MarkdownParser::MarkdownDocument::TextLineElement
MarkdownParser::MarkdownParser::MarkdownParser::parseInlineElements(const std::wstring &markdown) {
    return std::move(MarkdownInlineElementsParser::parse(markdown, [this](const std::wstring &refId) {
        return tokenizer.getReference(refId);
    }));
}

MarkdownParser::MarkdownDocument::MarkdownDocument
MarkdownParser::MarkdownParser::MarkdownParser::parse(const wchar_t *markdown, size_t size) {
    std::wstring markdownString(markdown, size);
    return MarkdownParser::parse(markdownString);
}

MarkdownParser::MarkdownDocument::MarkdownDocument
MarkdownParser::MarkdownParser::MarkdownParser::parse(const std::wstring &markdown) {
    MarkdownParser parser(markdown);
    return parser.docFromTokens();
}

// DONE?
void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineMainPassOp(
        const MarkdownTokenizer::VMarkdownToken &currentToken,
        const MarkdownTokenizer::VMarkdownToken &nextToken) {
    // clearing currentElementStack every time, control is regained by MainPass
    // might not be needed, if creators clean after themselves
    // std::stack<MarkdownDocument::VTopLevelMarkdownElement>().swap(currentElementStack);

    std::visit(overloaded{
            [this](const HeaderToken &token) {
                document.add(
                        make_recursive<MarkdownDocument::HeaderElement>(token.getLevel(),
                                                                        parseInlineElements(token.getText()),
                                                                        token.getId()));
            },
            [this](const HorizontalRuleToken &token) {
                document.add(make_recursive<MarkdownDocument::HorizontalRuleElement>());
            },
            [this, nextToken](const PlainTextToken &token) {
                if (auto nextTokenUnderline = std::get_if<HeaderUnderlineToken>(&nextToken)) {
                    document.add(
                            make_recursive<MarkdownDocument::HeaderElement>(nextTokenUnderline->getLevel(),
                                                                            parseInlineElements(token.getText())));
                    return;
                }
                stateStack.push(Paragraph);
                document.add(
                        make_recursive<MarkdownDocument::ParagraphElement>(parseInlineElements(token.getText())));
                currentElementStack.push(document.back());
            },
            [this](const BlockquoteToken &token) {
                stateStack.push(Blockquote);
                this->document.add(
                        make_recursive<MarkdownDocument::BlockquoteElement>(token.getRawText()));
                currentElementStack.push(document.back());
            },
            [this](const CodeToken &token) {
                stateStack.push(CodeBlock);
                document.add(make_recursive<MarkdownDocument::CodeblockElement>(token.getLanguage()));
                currentElementStack.push(document.back());
            },
            [this](const OrderedListToken &token) {
                stateStack.push(OrderedList);
                this->document.add(make_recursive<MarkdownDocument::OrderedListElement>(
                        make_recursive<MarkdownDocument::MultilineTextElement>(parseInlineElements(token.getText()))));
                currentElementStack.push(document.back());
            },
            [this](const UnorderedListToken &token) {
                stateStack.push(UnorderedList);
                this->document.add(make_recursive<MarkdownDocument::UnorderedListElement>(
                        make_recursive<MarkdownDocument::MultilineTextElement>(parseInlineElements(token.getText()))));
                currentElementStack.push(document.back());
            },
            [](auto &token) {}
    }, currentToken);
}

// DONE
void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineBlockquoteOp(
        const MarkdownTokenizer::VMarkdownToken &currentToken,
        const MarkdownTokenizer::VMarkdownToken &nextToken) {
    auto &lastElement = std::get<Recursive<MarkdownDocument::BlockquoteElement>>(
            currentElementStack.top());
    std::visit(overloaded{
            [&lastElement](const BlockquoteToken &token) {
                lastElement->addLine(token.getText());
            },
            [this, &lastElement](const auto &token) {
                lastElement->parse();
                stateMachineBackAndRedo();
            }
    }, currentToken);
}

// DONE
void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineCodeBlockOp(
        const MarkdownTokenizer::VMarkdownToken &currentToken,
        const MarkdownTokenizer::VMarkdownToken &nextToken) {
    auto &lastElement = std::get<Recursive<MarkdownDocument::CodeblockElement>>(
            currentElementStack.top());
    std::visit(overloaded{
            [&lastElement](const EmptyToken &token) {
                lastElement->add(MarkdownDocument::PlainTextElement(L"\n"));
            },
            [&lastElement](const auto &token) {
                lastElement->add(MarkdownDocument::PlainTextElement(token.getRawText()));
            },
            [this](const CodeToken &token) {
                stateMachineBackLevel();
            },
    }, currentToken);
}

// DONE?
void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineUnorderedListOp(
        const MarkdownTokenizer::VMarkdownToken &currentToken,
        const MarkdownTokenizer::VMarkdownToken &nextToken) {
    auto &currentLastElement = std::get<Recursive<MarkdownDocument::UnorderedListElement>>(
            currentElementStack.top());

    std::visit(overloaded{
            [this, &currentLastElement](const PlainTextToken &token) {
                auto &lastSubelement = currentLastElement->back();
                std::visit(overloaded{
                        [this, token](const Recursive<MarkdownDocument::MultilineTextElement> &element) {
                            element->add(parseInlineElements(token.getText()));
                        },
                        [this, token, &currentLastElement](
                                const Recursive<MarkdownDocument::UnorderedListElement> &element) {
                            // should never hit with valid markdown
                            currentLastElement->add(make_recursive<MarkdownDocument::MultilineTextElement>(
                                    parseInlineElements(token.getText())));
                        }
                }, lastSubelement);
            },
            [this, &currentLastElement](const UnorderedListToken &token) {
                // if indent of token is at least 2 greater than current indent
                if (token.getIndent() >= indentLevel.top() + 2) {
                    stateStack.push(UnorderedList);
                    indentLevel.push(token.getIndent());
                    auto newUl = make_recursive<MarkdownDocument::UnorderedListElement>(
                            make_recursive<MarkdownDocument::MultilineTextElement>(
                                    parseInlineElements(token.getText())));
                    currentLastElement->add(MarkdownDocument::ListElement::VListItem(newUl));
                    currentElementStack.push(MarkdownDocument::VTopLevelMarkdownElement(newUl));
                    return;
                }
                // otherwise, it's the same level of indent
                currentLastElement->add(make_recursive<MarkdownDocument::MultilineTextElement>(
                        parseInlineElements(token.getText())));
            },
            [this](const auto &token) {
                indentLevel.pop();
                stateMachineBackAndRedo();
            },
    }, currentToken);
}

// DONE?
void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineOrderedListOp(
        const MarkdownTokenizer::VMarkdownToken &currentToken,
        const MarkdownTokenizer::VMarkdownToken &nextToken) {
    auto &lastElement = std::get<Recursive<MarkdownDocument::OrderedListElement>>(
            currentElementStack.top());

    std::visit(overloaded{
            [this, &lastElement](const PlainTextToken &token) {
                auto &lastSubelement = lastElement->getItems().back();

                std::visit(overloaded{
                        [this, token](const Recursive<MarkdownDocument::MultilineTextElement> &element) {
                            element->add(parseInlineElements(token.getText()));
                        },
                        [this, token, &lastElement](const Recursive<MarkdownDocument::UnorderedListElement> &element) {
                            // should never hit with valid markdown
                            lastElement->add(make_recursive<MarkdownDocument::MultilineTextElement>(
                                    parseInlineElements(token.getText())));
                        }
                }, lastSubelement);
            },
            [this, &lastElement](const OrderedListToken &token) {
                lastElement->add(make_recursive<MarkdownDocument::MultilineTextElement>(
                        parseInlineElements(token.getText())));
            },
            [this, &lastElement](const UnorderedListToken &token) {
                if (!token.getIndent()) {
                    // no indent (indent = 0) - new list
                    stateMachineBackAndRedo();
                    return;
                }
                stateStack.push(UnorderedList);
                indentLevel.push(token.getIndent());
                auto newUl = make_recursive<MarkdownDocument::UnorderedListElement>(
                        make_recursive<MarkdownDocument::MultilineTextElement>(parseInlineElements(token.getText())));
                lastElement->add(MarkdownDocument::ListElement::VListItem(newUl));
                currentElementStack.push(MarkdownDocument::VTopLevelMarkdownElement(newUl));
            },
            [this](const auto &token) {
                stateMachineBackAndRedo();
            }
    }, currentToken);
}

// DONE
void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineParagraphOp(
        const MarkdownTokenizer::VMarkdownToken &currentToken,
        const MarkdownTokenizer::VMarkdownToken &nextToken) {
    auto &lastElement = std::get<Recursive<MarkdownDocument::ParagraphElement>>(
            currentElementStack.top());

    std::visit(overloaded{
            [&lastElement, this](const PlainTextToken &token) {
                lastElement->add(parseInlineElements(token.getText()));
            },
            [this](const auto &token) {
                stateMachineBackAndRedo();
            },
    }, currentToken);
}

void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineBackAndRedo() {
    stateMachineBackLevel();
    --stateMachineTokenIndex;
}

void MarkdownParser::MarkdownParser::MarkdownParser::stateMachineBackLevel() {
    stateStack.pop();
    currentElementStack.pop();
}
