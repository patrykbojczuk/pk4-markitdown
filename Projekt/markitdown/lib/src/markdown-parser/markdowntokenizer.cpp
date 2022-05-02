#include <algorithm>
#include <thread>
#include <future>
#include <ranges>
#include <regex>
#include <string_view>
#include "markdowntokenizer.h"
#include "nthelement.hpp"
#include "helpers/trim.cpp"

MarkdownParser::MarkdownParser::MarkdownTokenizer::MarkdownTokenizer(const std::wstring &markdown) : sourceMarkdown(
        markdown), lines(std::wstring_view(sourceMarkdown.begin(), sourceMarkdown.end()) |
                         std::views::split(L"\n"sv)), numOfLines(std::ranges::distance(lines)) {}

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

        if (wsv_trim(line).empty()) {
            // Empty Token
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^>[ ]?(.*)"))) {
            // Blockquote
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^`{3}(.*)"))) {
            // Code block
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^={3,}\\s*$"))) {
            // Lvl 1 Header Underline
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^-{3,}\\s*$"))) {
            // Lvl 2 Header Underline
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^(#{1,6})\\s+(.*)"))) {
            // Header
        } else if (std::regex_match(line.begin(), line.end(),
                                    std::wregex(L"^((\\*\\s*){3,} | (-\\s*){3,} | (_\\s*){3,} )$",
                                                std::regex_constants::extended))) {
            // Horizontal Rule
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^[-*+]\\s+(.+)"))) {
            // Unordered list
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(L"^\\d+\\.\\s+(.+)"))) {
            // Ordered list
        } else if (std::regex_match(line.begin(), line.end(), std::wregex(
                L"^[ ]{0,3} \\[([^\\]]+)\\] : \\s* (\\S+) \\s* (?| \\\"([^\\\"]+)\\\" | '([^']+)' | \\(([^)]+)\\) | () ) \\s*$",
                std::regex_constants::extended))) {
            // Reference
        } else {
            // Plain Text
        }
    }

    return std::move(retVec);
}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::addReference(const std::wstring &refId, const std::wstring &url,
                                                                     const std::wstring &title) {
    references.insert_or_assign(refId, LinkableReference{url, title});
}
