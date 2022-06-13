#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include "markdown-document/markdowndocument.h"
#include "markdowntokenizer.h"
#include "markdown-document/markdown-elements/textlineelement.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class MarkdownParser {
        public:
            static MarkdownDocument::MarkdownDocument parse(const std::wstring &markdown);

            static MarkdownDocument::MarkdownDocument parse(const wchar_t *markdown, size_t size);

            enum ParserState {
                MainPass,
                CodeBlock,
                UnorderedList,
                OrderedList,
                Blockquote,
                Paragraph,
                Finished
            };

        private:
            MarkdownDocument::MarkdownDocument document;
            MarkdownTokenizer tokenizer;
            std::stack<ParserState> stateStack;
            std::stack<MarkdownDocument::VTopLevelMarkdownElement> currentElementStack;
            std::stack<size_t> indentLevel;
            size_t stateMachineTokenIndex = 0;

            MarkdownParser(const std::wstring &markdown);

            MarkdownDocument::MarkdownDocument docFromTokens();

            MarkdownDocument::TextLineElement parseInlineElements(const std::wstring &refId);

            void stateMachineMainPassOp(const MarkdownTokenizer::VMarkdownToken &currentToken,
                                        const MarkdownTokenizer::VMarkdownToken &nextToken);

            void stateMachineBlockquoteOp(const MarkdownTokenizer::VMarkdownToken &currentToken,
                                          const MarkdownTokenizer::VMarkdownToken &nextToken);

            void stateMachineCodeBlockOp(const MarkdownTokenizer::VMarkdownToken &currentToken,
                                         const MarkdownTokenizer::VMarkdownToken &nextToken);

            void stateMachineUnorderedListOp(const MarkdownTokenizer::VMarkdownToken &currentToken,
                                             const MarkdownTokenizer::VMarkdownToken &nextToken);

            void stateMachineOrderedListOp(const MarkdownTokenizer::VMarkdownToken &currentToken,
                                           const MarkdownTokenizer::VMarkdownToken &nextToken);

            void stateMachineParagraphOp(const MarkdownTokenizer::VMarkdownToken &currentToken,
                                         const MarkdownTokenizer::VMarkdownToken &nextToken);

            void stateMachineBackLevel();

            void stateMachineBackAndRedo();
        };
    };
};

#endif // MARKDOWNPARSER_H
