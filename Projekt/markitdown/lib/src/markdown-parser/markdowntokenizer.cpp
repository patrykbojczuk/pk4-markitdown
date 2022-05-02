#include <algorithm>
#include <thread>
#include <future>
#include <ranges>
#include <regex>
#include <string_view>
#include "markdowntokenizer.h"
#include "nthelement.hpp"
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
    std::vector<std::future<std::vector<VMarkdownToken>>> futures;

    unsigned int availableThreads = std::thread::hardware_concurrency() ?: 1;
    unsigned int runOnThreads = numOfLines < availableThreads
                                ? numOfLines
                                : availableThreads;
    unsigned int additionalLineThreadsLeft = numOfLines % runOnThreads;

    size_t i = 0,
            increment = numOfLines / runOnThreads;

    auto start = lines.begin(),
            end = lines.begin();
    std::ranges::advance(end, increment);

    if (additionalLineThreadsLeft) {
        for (i; i < runOnThreads - additionalLineThreadsLeft; ++i) {
            createNextThread(futures, increment, start, end);
        }
        ++increment;
    }
    for (i; i < runOnThreads; ++i) {
        createNextThread(futures, increment, start, end);
    }

    for (i = 0; i < runOnThreads; ++i) {
        auto returnedTokens = futures[i].get();
        tokens.reserve(tokens.size() + returnedTokens.size());

        for (auto &token: returnedTokens) {
            tokens.push_back(std::move(token));
        }
    }

    finished = true;
}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::createNextThread(
        std::vector<std::future<std::vector<MarkdownTokenizer::VMarkdownToken>>> &futures, size_t increment,
        split_view_iterator &start, split_view_iterator &end) const {
    futures.push_back(std::async(std::launch::async, &MarkdownTokenizer::tokenize, this,
                                 std::ranges::subrange(start, end)));
    std::ranges::advance(start, increment);
    std::ranges::advance(end, increment);
}

std::vector<MarkdownParser::MarkdownParser::MarkdownTokenizer::VMarkdownToken>
MarkdownParser::MarkdownParser::MarkdownTokenizer::tokenize(
        std::ranges::subrange<decltype(std::declval<std::ranges::split_view<std::wstring_view, std::wstring_view>>().begin())> sublines) const {
    std::vector<VMarkdownToken> retVec;

    for (auto _line: sublines) {
        std::wstring_view line(_line.begin(), _line.end());
        line = wsv_trim(line, L"\n\r");
        std::match_results<std::wstring_view::const_iterator> match;

        if (wsv_trim(line).empty()) {
            // Empty Token
            retVec.push_back(EmptyToken{});
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(L"^>[ ]?(.*)"))) {
            // Blockquote
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(L"^`{3}(.*)"))) {
            // Code block
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^={3,}\\s*$"))) {
            // Lvl 1 Header Underline
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^-{3,}\\s*$"))) {
            // Lvl 2 Header Underline
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(L"^(#{1,6})\\s+(.*)"))) {
            // Header
            std::match_results<std::wstring_view::const_iterator> idMatch;
            const std::wstring_view text = wsv_rtrim(match[2].first, L"\t\n\v\f\r# ");
            if (std::regex_match(text.begin(), text.end(), idMatch, std::wregex(L"^(.*)\\s+\\{#(.*)\\}\\s*"))) {
                retVec.push_back(
                        HeaderToken((MarkdownHeaderLevel) match[1].length(), std::wstring(idMatch[1].str()),
                                    std::wstring(idMatch[2].str())));
            } else {
                retVec.push_back(HeaderToken((MarkdownHeaderLevel) match[1].length(), std::wstring(text)));
            }
        } else if (std::regex_match(line.begin(), line.end(), match,
                                    std::wregex(L"^((\\*\\s*){3,} | (-\\s*){3,} | (_\\s*){3,} )$",
                                                std::regex_constants::extended))) {
            // Horizontal Rule
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(L"^[-*+]\\s+(.+)"))) {
            // Unordered list
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(L"^\\d+\\.\\s+(.+)"))) {
            // Ordered list
        } else if (std::regex_match(line.begin(), line.end(), match, std::wregex(
                //L"^[ ]{0,3} \\[([^\\]]+)\\] : \\s* (\\S+) \\s* (?| \\\"([^\\\"]+)\\\" | '([^']+)' | \\(([^)]+)\\) | () ) \\s*$",
                L"^[ ]{0,3} ", // Mismatched '(' and ')'
                std::regex_constants::extended))) {
            // Reference
        } else {
            // Plain Text
            retVec.push_back(PlainTextToken(std::wstring(wsv_trim(line)), std::wstring(line)));
        }
    }

    return std::move(retVec);
}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::addReference(const std::wstring &refId, const std::wstring &url,
                                                                     const std::wstring &title) {
    references.insert_or_assign(refId, LinkableReference{url, title});
}
