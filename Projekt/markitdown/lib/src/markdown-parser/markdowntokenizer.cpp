#include <algorithm>
#include <thread>
#include <future>
#include <ranges>
#include <regex>
#include <string_view>
#include "markdowntokenizer.h"
#include "helpers/trim.h"

MarkdownParser::MarkdownParser::MarkdownTokenizer::MarkdownTokenizer(const std::wstring &markdown) : sourceMarkdown(
        markdown), lines(std::wstring_view(sourceMarkdown.begin(), sourceMarkdown.end()) |
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

    auto start = lines.begin();

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
        std::vector<VMarkdownToken> returnedTokens;
        std::unordered_set<size_t> encounteredCollisions;
        std::unordered_map<std::wstring, LinkableReference> returnedReferences;

        std::tie(returnedTokens, encounteredCollisions, returnedReferences) = futures[i].get();
        tokens.reserve(tokens.size() + returnedTokens.size());

        // Check for returnedReferences' size is slower than just merging with references
        references.merge(returnedReferences);
        for (const auto &ref: returnedReferences) {
            references.insert_or_assign(ref.first, std::move(ref.second));
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
        std::wstring_view line(_line.begin(), _line.end());
        line = wsv_trim(line, L"\n\r");
        std::match_results<std::wstring_view::const_iterator> match;

        if (wsv_trim(line).empty()) {
            // Empty Token
            retVec.push_back(EmptyToken{});
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(LR";(^>[ ]?(.*));"))) {
            // Blockquote
            retVec.push_back(BlockquoteToken(std::wstring(match[1].str())));
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(LR";(^`{3}(.*));"))) {
            // Code block
            retVec.push_back(CodeToken(std::wstring(match[1].str())));
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(LR";(^={1,}\s*$);"))) {
            // Lvl 1 Header Underline
            retVec.push_back(HeaderUnderlineToken(MarkdownHeaderLevel::Level1));
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(LR";(^-{1,}\s*$);"))) {
            // Lvl 2 Header Underline
            retVecCollisionIds.insert(retVec.size());
            retVec.push_back(HeaderUnderlineToken(MarkdownHeaderLevel::Level2));
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(LR";(^(#{1,6})\s+(.*)$);"))) {
            // Header
            std::match_results<std::wstring_view::const_iterator> idMatch;
            const std::wstring matchedText = match[2].str();
            const std::wstring_view text = wsv_rtrim(matchedText, L"\t\n\v\f\r# ");
            if (std::regex_match(text.begin(), text.end(), idMatch, std::wregex(LR";(^(.*)\s+\{#(.*)\}\s*$);"))) {
                retVec.push_back(
                        HeaderToken((MarkdownHeaderLevel) match[1].length(), std::wstring(idMatch[1].str()),
                                    std::wstring(idMatch[2].str())));
            } else {
                retVec.push_back(HeaderToken((MarkdownHeaderLevel) match[1].length(), std::wstring(text)));
            }
        } else if (std::regex_match(line.begin(), line.end(),
                                    std::wregex(L"^([-_*][ \\t]*){3,}$"))) {
            // Horizontal Rule
            retVec.push_back(HorizontalRuleToken{});
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(LR";(^([ ]*)[-*+]\s+(.+)$);"))) {
            // Unordered list
            retVec.push_back(UnorderedListToken(std::wstring(match[2].str()))); // TODO: Add preceding spaces count
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(LR";(^\d+\.\s+(.+)$);"))) {
            // Ordered list
            retVec.push_back(OrderedListToken(std::wstring(match[1].str())));
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(
                LR";(^\s*\[\s*([a-zA-Z0-9_-]+)\s*\]\s*:\s*(\S+)\s*(?:\"(.*?)\")?\s*$);"
        ))) {
            // Reference
            retRefs.insert_or_assign(match[1].str(), LinkableReference{
                    .url = match[2].str(),
                    .title = (match.size() == 4 && match[3].str().length())
                             ? match[3].str()
                             : L""
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
