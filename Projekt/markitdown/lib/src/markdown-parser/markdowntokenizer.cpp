#include <algorithm>
#include <thread>
#include <future>
#include <ranges>
#include <string_view>
#include "markdowntokenizer.h"
#include "nthelement.hpp"

MarkdownParser::MarkdownParser::MarkdownTokenizer::MarkdownTokenizer(const std::wstring &markdown) : sourceMarkdown(
        markdown) {
    numOfLines = std::ranges::count(markdown, '\n');
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
    
}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::createNextThread(
        std::vector<std::future<std::vector<MarkdownTokenizer::VMarkdownToken>>> &futures, size_t increment,
        std::wstring::const_iterator &start, std::wstring::const_iterator &end) const {

}

std::vector<MarkdownParser::MarkdownParser::MarkdownTokenizer::VMarkdownToken>
MarkdownParser::MarkdownParser::MarkdownTokenizer::tokenize(std::wstring::const_iterator from,
                                                            std::wstring::const_iterator to) const {

}

void MarkdownParser::MarkdownParser::MarkdownTokenizer::addReference(const std::wstring &refId, const std::wstring &url,
                                                                     const std::wstring &title) {
    references.insert_or_assign(refId, LinkableReference{url, title});
}
