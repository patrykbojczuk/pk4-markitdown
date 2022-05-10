#ifndef MARKDOWNTOKENIZER_H
#define MARKDOWNTOKENIZER_H

#include <future>
#include <unordered_map>
#include <variant>
#include <vector>
#include <ranges>
#include <unordered_set>
#include "markdown-tokens/blockquotetoken.h"
#include "markdown-tokens/codetoken.h"
#include "markdown-tokens/emptytoken.h"
#include "markdown-tokens/headertoken.h"
#include "markdown-tokens/headerunderlinetoken.h"
#include "markdown-tokens/horizontalruletoken.h"
#include "markdown-tokens/orderedlisttoken.h"
#include "markdown-tokens/plaintexttoken.h"
#include "markdown-tokens/unorderedlisttoken.h"
#include "linkablereference.h"

namespace std::ranges {
    template<>
    inline constexpr bool enable_view<std::wstring_view> = true;
}

using namespace std::string_view_literals;

using split_view_iterator = decltype(std::declval<std::ranges::split_view<std::wstring_view, std::wstring_view>>().begin());

namespace MarkdownParser {
    namespace MarkdownParser {
        class MarkdownTokenizer {
        public:
            using VMarkdownToken = std::variant<EmptyToken, HeaderUnderlineToken, HeaderToken, HorizontalRuleToken, PlainTextToken, BlockquoteToken, CodeToken, OrderedListToken, UnorderedListToken>;

            MarkdownTokenizer(const std::wstring &markdown);

            const bool isTokenizationFinished() const;

            const std::vector<VMarkdownToken> &getTokens() const;

            bool hasReference(const std::wstring &refId);

            LinkableReference getReference(const std::wstring &refId);

        private:
            std::unordered_map<std::wstring, LinkableReference> references;
            std::vector<VMarkdownToken> tokens;
            const std::wstring sourceMarkdown;
            std::ranges::split_view<std::wstring_view, std::wstring_view> lines;
            bool finished = false;
            size_t numOfLines = 0;

            void start();

            std::tuple<std::vector<VMarkdownToken>, std::unordered_set<size_t>, std::unordered_map<std::wstring, LinkableReference>>
            tokenize(
                    std::ranges::subrange<split_view_iterator> sublines) const;

            void addReference(const std::wstring &refId, const std::wstring &url, const std::wstring &title = L"");

            void createNextThread(
                    std::vector<std::future<std::tuple<std::vector<VMarkdownToken>, std::unordered_set<size_t>, std::unordered_map<std::wstring, LinkableReference>>>> &futures,
                    size_t increment, split_view_iterator &start) const;
        };
    }
}

#endif //MARKDOWNTOKENIZER_H
