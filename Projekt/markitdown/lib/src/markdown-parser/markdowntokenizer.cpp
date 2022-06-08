#include <algorithm>
#include <thread>
#include <future>
#include <ranges>
#include <regex>
#include <string_view>
#include "markdowntokenizer.h"
#include "helpers/trim.h"
#include "regex.defs.h"

MarkdownParser::MarkdownParser::MarkdownTokenizer::MarkdownTokenizer(const std::wstring &markdown) : sourceMarkdown(
        markdown), lines(std::wstring_view(std::begin(sourceMarkdown), std::end(sourceMarkdown)) |
                         std::views::split(L"\n"sv)), numOfLines(std::ranges::distance(lines)) {
    start();
}

const bool MarkdownParser::MarkdownParser::MarkdownTokenizer::isTokenizationFinished() const {
    return finished;
}

const std::vector<MarkdownParser::MarkdownParser::MarkdownTokenizer::VMarkdownToken> &
MarkdownParser::MarkdownParser::MarkdownTokenizer::getTokens() const {
    return tokens;
}

bool MarkdownParser::MarkdownParser::MarkdownTokenizer::hasReference(const std::wstring &refId) {
    return references.contains(refId);
}

MarkdownParser::MarkdownParser::LinkableReference
MarkdownParser::MarkdownParser::MarkdownTokenizer::getReference(const std::wstring &refId) {
    return references.at(refId);
}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::start() {
    if (!numOfLines) {
        finished = true;
        return;
    }
    std::vector<std::future<std::tuple<std::vector<VMarkdownToken>, std::unordered_set<size_t>, std::unordered_map<std::wstring, LinkableReference>>>> futures;

    unsigned int availableThreads = std::thread::hardware_concurrency() ?: 1;
    unsigned int runOnThreads = numOfLines < availableThreads
                                ? numOfLines
                                : availableThreads;
    unsigned int additionalLineThreadsLeft = numOfLines % runOnThreads;

    size_t i = 0,
            increment = numOfLines / runOnThreads;

    auto start = std::begin(lines);

    if (additionalLineThreadsLeft) {
        for (i; i < runOnThreads - additionalLineThreadsLeft; ++i) {
            createNextThread(futures, increment, start);
        }
        ++increment;
    }
    for (i; i < runOnThreads; ++i) {
        createNextThread(futures, increment, start);
    }

    for (i = 0; i < runOnThreads; ++i) {
        auto [returnedTokens, encounteredCollisions, returnedReferences] = futures[i].get();
        tokens.reserve(tokens.size() + returnedTokens.size());

        // Check for returnedReferences' size is slower than just merging with references
        references.merge(returnedReferences);
        for (const auto &ref: returnedReferences) {
            references.insert_or_assign(std::move(ref.first), std::move(ref.second));
        }

        if (encounteredCollisions.size()) {
            for (auto collision: encounteredCollisions) {
                if ((collision != 0 && !std::holds_alternative<PlainTextToken>(returnedTokens[collision - 1])) ||
                    (collision == 0 && tokens.size() &&
                     !std::holds_alternative<PlainTextToken>(tokens[tokens.size() - 1])) ||
                    !tokens.size()) {
                    returnedTokens[collision] = HorizontalRuleToken{};
                }
            }
        }

        tokens.insert(std::end(tokens), std::make_move_iterator(std::begin(returnedTokens)),
                      std::make_move_iterator(std::end(returnedTokens)));
    }

    VMarkdownToken endToken = EmptyToken();
    tokens.push_back(endToken);

    finished = true;
}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::createNextThread(
        std::vector<std::future<std::tuple<std::vector<MarkdownTokenizer::VMarkdownToken>, std::unordered_set<size_t>, std::unordered_map<std::wstring, LinkableReference>>>> &futures,
        size_t increment, split_view_iterator &start) const {
    futures.push_back(std::async(std::launch::async, &MarkdownTokenizer::tokenize, this,
                                 std::ranges::subrange(start, std::next(start, increment))));
    std::ranges::advance(start, increment);
}

std::tuple<std::vector<MarkdownParser::MarkdownParser::MarkdownTokenizer::VMarkdownToken>, std::unordered_set<size_t>, std::unordered_map<std::wstring, MarkdownParser::MarkdownParser::LinkableReference>>
MarkdownParser::MarkdownParser::MarkdownTokenizer::tokenize(
        std::ranges::subrange<decltype(std::declval<std::ranges::split_view<std::wstring_view, std::wstring_view>>().begin())> sublines) const {
    std::vector<VMarkdownToken> retVec;
    std::unordered_set<size_t> retVecCollisionIds;
    std::unordered_map<std::wstring, LinkableReference> retRefs;

    for (auto _line: sublines) {
        std::wstring_view line(std::begin(_line), std::end(_line));
        line = wsv_trim(line, L"\n\r");
        std::match_results<std::wstring_view::const_iterator> match;
        auto lineBegin = std::begin(line),
                lineEnd = std::end(line);

        if (wsv_trim(line).empty()) {
            // Empty Token
            retVec.push_back(EmptyToken{});
        } else if (std::regex_match(lineBegin, lineEnd, match, std::wregex(BLOCKQUOTE_TOKEN_REGEXP))) {
            // Blockquote
            retVec.push_back(BlockquoteToken(std::wstring(match[1].str()), std::wstring(line)));
        } else if (std::regex_match(lineBegin, lineEnd, match, std::wregex(CODEBLOCK_TOKEN_REGEXP))) {
            // Code block
            retVec.push_back(CodeToken(std::wstring(match[1].str())));
        } else if (std::regex_match(lineBegin, lineEnd, std::wregex(L1_HEADER_UNDERLINE_TOKEN_REGEXP))) {
            // Lvl 1 Header Underline
            retVec.push_back(HeaderUnderlineToken(MarkdownHeaderLevel::Level1, std::wstring(line)));
        } else if (std::regex_match(lineBegin, lineEnd, std::wregex(L2_HEADER_UNDERLINE_TOKEN_REGEXP))) {
            // Lvl 2 Header Underline
            retVecCollisionIds.insert(retVec.size());
            retVec.push_back(HeaderUnderlineToken(MarkdownHeaderLevel::Level2, std::wstring(line)));
        } else if (std::regex_match(lineBegin, lineEnd, match, std::wregex(HEADER_TOKEN_REGEXP))) {
            // Header
            std::match_results<std::wstring_view::const_iterator> idMatch;
            const std::wstring matchedText = match[2].str();
            const std::wstring_view text = wsv_rtrim(matchedText, L"\t\n\v\f\r# ");
            if (std::regex_match(std::begin(text), std::end(text), idMatch,
                                 std::wregex(HEADER_TOKEN_SUB_REGEXP))) {
                retVec.push_back(
                        HeaderToken((MarkdownHeaderLevel) match[1].length(), std::wstring(idMatch[1].str()),
                                    std::wstring(idMatch[2].str()), std::wstring(line)));
            } else {
                retVec.push_back(HeaderToken((MarkdownHeaderLevel) match[1].length(), std::wstring(text), L"",
                                             std::wstring(line)));
            }
        } else if (std::regex_match(lineBegin, lineEnd,
                                    std::wregex(HORIZONTAL_RULE_TOKEN_REGEXP))) {
            // Horizontal Rule
            retVec.push_back(HorizontalRuleToken{std::wstring(line)});
        } else if (std::regex_match(lineBegin, lineEnd, match,
                                    std::wregex(UNORDERED_LIST_TOKEN_REGEXP))) {
            // Unordered list
            retVec.push_back(UnorderedListToken(
                    std::wstring(match[2].str()), match[1].length(), std::wstring(line)));
        } else if (std::regex_match(lineBegin, lineEnd, match, std::wregex(ORDERED_LIST_TOKEN_REGEXP))) {
            // Ordered list
            retVec.push_back(OrderedListToken(std::wstring(match[1].str()), std::wstring(line)));
        } else if (std::regex_match(lineBegin, lineEnd, match, std::wregex(
                LINKABLE_REFERENCE_REGEXP
        ))) {
            // Reference
            retRefs.insert_or_assign(match[1].str(), LinkableReference{
                    .url = match[2].str(),
                    .title = (match.size() == 4 && match[3].str().length())
                             ? match[3].str()
                             : L"",
                    .rawText = std::wstring(line)
            });
        } else {
            // Plain Text
            retVec.push_back(PlainTextToken(std::wstring(wsv_trim(line)), std::wstring(line)));
        }
    }

    return std::make_tuple(std::move(retVec), std::move(retVecCollisionIds), std::move(retRefs));
}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::addReference(const std::wstring &refId, const std::wstring &url,
                                                                     const std::wstring &title) {
    references.insert_or_assign(refId, LinkableReference{url, title});
}
