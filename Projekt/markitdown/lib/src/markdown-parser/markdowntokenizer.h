#ifndef MARKDOWNTOKENIZER_H
#define MARKDOWNTOKENIZER_H

#include <future>
#include <unordered_map>
#include <variant>
#include <vector>
#include "markdown-tokens/blockquotetoken.h"
#include "markdown-tokens/codetoken.h"
#include "markdown-tokens/emptytoken.h"
#include "markdown-tokens/endofdocument.h"
#include "markdown-tokens/headertoken.h"
#include "markdown-tokens/headerunderlinetoken.h"
#include "markdown-tokens/horizontalruletoken.h"
#include "markdown-tokens/orderedlisttoken.h"
#include "markdown-tokens/plaintexttoken.h"
#include "markdown-tokens/unorderedlisttoken.h"
#include "linkablereference.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class MarkdownTokenizer {
        public:
            using VMarkdownToken = std::variant<EmptyToken, EndOfDocument, HorizontalRuleToken, CodeToken, HeaderUnderlineToken, PlainTextToken, OrderedListToken, UnorderedListToken, BlockquoteToken, HeaderToken>;

            MarkdownTokenizer(const std::wstring &markdown);

            const bool isTokenizationFinished() const;

            const std::vector<VMarkdownToken> &getTokens() const;

            bool hasReference(const std::wstring &refId);

            LinkableReference getReference(const std::wstring &refId);

        private:
            std::unordered_map<std::wstring, LinkableReference> references;
            std::vector<VMarkdownToken> tokens;
            const std::wstring sourceMarkdown;
            bool finished = false;
            size_t numOfLines = 0;

            void start();

            std::vector<VMarkdownToken>
            tokenize(std::wstring::const_iterator from, std::wstring::const_iterator to) const;

            void addReference(const std::wstring &refId, const std::wstring &url, const std::wstring &title = L"");

            void createNextThread(std::vector<std::future<std::vector<VMarkdownToken>>> &futures, size_t increment,
                                  std::wstring::const_iterator &start, std::wstring::const_iterator &end) const;
        };
    }
}

#endif //MARKDOWNTOKENIZER_H
