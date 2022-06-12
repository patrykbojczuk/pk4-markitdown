#include <regex>
#include "markdowninlineelementsparser.h"
#include "regex.defs.h"
#include "markdown-document/markdown-elements/inlinecodeelement.h"
#include "markdown-document/markdown-elements/imageelement.h"
#include "markdown-document/markdown-elements/linkelement.h"
#include "markdown-document/markdown-elements/emphasiselement.h"
#include "markdown-document/markdown-elements/strongemphasiselement.h"
#include "markdown-document/markdown-elements/strikethroughelement.h"
#include "linkablereference.h"

MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::MarkdownInlineElementsParser(
        const std::wstring &markdownSource,
        const std::function<LinkableReference(const std::wstring &refId)> &getReference)
        : markdownSource(markdownSource),
          getReference(getReference) {}

MarkdownParser::MarkdownDocument::TextLineElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::parse(const std::wstring &markdownSource,
                                                                    const std::function<LinkableReference(
                                                                            const std::wstring &refId)> &getReference) {
    MarkdownInlineElementsParser parser(markdownSource, getReference);
    parser.parseAndSubstituteAtomicElements();
    return parser.parseNestedElementsAndReplaceSubstitutions();
}

void MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::parseAndSubstituteAtomicElements() {
    std::wsmatch match;

    // code
    while (std::regex_search(markdownSource, match, std::wregex(INLINE_CODE_REGEXP))) {
        atomics.push_back(make_recursive<MarkdownDocument::InlineCodeElement>(match[1].str()));

        substituteMatchedAtomic(match);
    }

    // image direct
    while (std::regex_search(markdownSource, match, std::wregex(IMAGE_WITH_URL_REGEXP))) {
        atomics.push_back(make_recursive<MarkdownDocument::ImageElement>(match[2].str(), match[1].str(),
                                                                         match[3].str()));

        substituteMatchedAtomic(match);
    }

    // image reference
    while (std::regex_search(markdownSource, match, std::wregex(IMAGE_FROM_REF_REGEXP))) {
        try {
            auto reference = getReference(match[2].str());
            atomics.push_back(
                    make_recursive<MarkdownDocument::ImageElement>(reference.url, match[1].str(), reference.title));
        } catch (std::out_of_range &e) {
            atomics.push_back(make_recursive<MarkdownDocument::PlainTextElement>(match[0]));
        }

        substituteMatchedAtomic(match);
    }

    // link direct
    while (std::regex_search(markdownSource, match, std::wregex(LINK_WITH_URL_REGEXP))) {
        atomics.push_back(make_recursive<MarkdownDocument::LinkElement>(match[2].str(), match[1].str(),
                                                                        match[3].str()));

        substituteMatchedAtomic(match);
    }

    // link reference
    while (std::regex_search(markdownSource, match, std::wregex(LINK_FROM_REF_REGEXP))) {
        try {
            // get reference from match[2].str() from parser
            auto reference = getReference(match[2].str());
            atomics.push_back(
                    make_recursive<MarkdownDocument::LinkElement>(reference.url, match[1].str(), reference.title));
        } catch (std::out_of_range &e) {
            atomics.push_back(make_recursive<MarkdownDocument::PlainTextElement>(match[0]));
        }

        substituteMatchedAtomic(match);
    }

    // link implicit
    while (std::regex_search(markdownSource, match, std::wregex(IMPLICIT_LINK_FROM_REF_REGEXP))) {
        try {
            // get reference from match[1].str() from parser
            auto reference = getReference(match[1].str());
            atomics.push_back(
                    make_recursive<MarkdownDocument::LinkElement>(reference.url, match[1].str(), reference.title));
        } catch (std::out_of_range &e) {
            atomics.push_back(make_recursive<MarkdownDocument::PlainTextElement>(match[0]));
        }

        substituteMatchedAtomic(match);
    }

    // link literal
    while (std::regex_search(markdownSource, match, std::wregex(LINK_LITERAL_REGEXP))) {
        atomics.push_back(
                make_recursive<MarkdownDocument::LinkElement>(match[1].str(), match[1].str()));

        substituteMatchedAtomic(match);
    }

    // email literal
    while (std::regex_search(markdownSource, match, std::wregex(EMAIL_LITERAL_REGEXP))) {
        atomics.push_back(
                make_recursive<MarkdownDocument::LinkElement>(L"mailto:" + match[1].str(), match[1].str()));

        substituteMatchedAtomic(match);
    }
}

void MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::substituteMatchedAtomic(
        const std::wsmatch &match) {
    markdownSource.replace(match.position(), match.length(), L"\x07" + std::to_wstring(
            atomics.size() - 1) + L"\x07");
}

MarkdownParser::MarkdownDocument::TextLineElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::parseNestedElementsAndReplaceSubstitutions() {
    std::vector<MarkdownDocument::VInlineMarkdownElement> lineElems;
    std::match_results<std::wstring_view::const_iterator> match;
    std::wstring_view textView{markdownSource};
    std::wstring currentPlainText = L"";

    while (!textView.empty()) {
        if (std::regex_search(std::begin(textView), std::end(textView), match,
                              std::wregex(BOLD_ITALIC_STRIKETHROUGH_REGEXP))) {
            // bold + italic + strikethrough
            addPlainTextElementIfExists(currentPlainText, lineElems);
            lineElems.push_back(createStrongEmphasisElement(createEmphasisElement(match[1])));
            textView = textView.substr(match[0].length());
        } else if (std::regex_search(std::begin(textView), std::end(textView), match,
                                     std::wregex(BOLD_ITALIC_REGEXP))) {
            // bold + italic
            addPlainTextElementIfExists(currentPlainText, lineElems);
            lineElems.push_back(createStrongEmphasisElement(createEmphasisElement(match[1])));
            textView = textView.substr(match[0].length());
        } else if (std::regex_search(std::begin(textView), std::end(textView), match,
                                     std::wregex(BOLD_STRIKETHROUGH_REGEXP))) {
            // bold + strikethrough
            addPlainTextElementIfExists(currentPlainText, lineElems);
            lineElems.push_back(createStrikethroughElement(createStrongEmphasisElement(match[1])));
            textView = textView.substr(match[0].length());
        } else if (std::regex_search(std::begin(textView), std::end(textView), match,
                                     std::wregex(ITALIC_STRIKETHROUGH_REGEXP))) {
            // italic + strikethrough
            addPlainTextElementIfExists(currentPlainText, lineElems);
            lineElems.push_back(createStrikethroughElement(createEmphasisElement(match[1])));
            textView = textView.substr(match[0].length());
        } else if (std::regex_search(std::begin(textView), std::end(textView), match, std::wregex(BOLD_REGEXP))) {
            // bold
            addPlainTextElementIfExists(currentPlainText, lineElems);
            lineElems.push_back(createStrongEmphasisElement(match[1]));
            textView = textView.substr(match[0].length());
        } else if (std::regex_search(std::begin(textView), std::end(textView), match, std::wregex(ITALIC_REGEXP))) {
            // italic
            addPlainTextElementIfExists(currentPlainText, lineElems);
            lineElems.push_back(createEmphasisElement(match[1]));
            textView = textView.substr(match[0].length());
        } else if (std::regex_search(std::begin(textView), std::end(textView), match,
                                     std::wregex(STRIKETHROUGH_REGEXP))) {
            // strikethrough
            addPlainTextElementIfExists(currentPlainText, lineElems);
            lineElems.push_back(createStrikethroughElement(match[1]));
            textView = textView.substr(match[0].length());
        } else {
            // plain text
            currentPlainText += textView[0];
            textView = textView.substr(1);
        }
    }
    addPlainTextElementIfExists(currentPlainText, lineElems);

    MarkdownDocument::TextLineElement returnElement{};
    returnElement.push_back_many(std::begin(lineElems), std::end(lineElems));
    return returnElement;
}

std::vector<MarkdownParser::MarkdownDocument::VInlineMarkdownElement>
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::substitutedAtomic(const std::wstring &text) {
    std::vector<MarkdownDocument::VInlineMarkdownElement> returnData;
    std::match_results<std::wstring_view::const_iterator> match;
    std::wstring_view textView{text};

    while (std::regex_search(textView.begin(), textView.end(), match, std::wregex(ATOMIC_SUBSTITUTION_REGEXP))) {
        if (match.prefix().length()) {
            MarkdownDocument::VInlineMarkdownElement prefix = make_recursive<MarkdownDocument::PlainTextElement>(
                    match.prefix());
            returnData.push_back(prefix);
        }
        size_t position = std::stoull(match[1].str().c_str());
        returnData.push_back(atomics.at(position));
        textView = textView.substr(match.position() + match.length());
    }

    if (!textView.empty()) {
        MarkdownDocument::VInlineMarkdownElement text = make_recursive<MarkdownDocument::PlainTextElement>(
                std::wstring(textView));
        returnData.push_back(text);
    }

    return returnData;
}

MarkdownParser::MarkdownDocument::VInlineMarkdownElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::createEmphasisElement(const std::wstring &text) {
    auto substitute = substitutedAtomic(text);
    Recursive<MarkdownDocument::EmphasisElement> emphasisElement = make_recursive<MarkdownDocument::EmphasisElement>(
            substitute[0]);
    emphasisElement->push_back_many(std::next(std::begin(substitute), 1),
                                    std::end(substitute));
    MarkdownDocument::VInlineMarkdownElement returnElement = emphasisElement;
    return returnElement;
}

MarkdownParser::MarkdownDocument::VInlineMarkdownElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::createEmphasisElement(
        MarkdownDocument::VInlineMarkdownElement element) {
    MarkdownDocument::VInlineMarkdownElement returnElement = make_recursive<MarkdownDocument::EmphasisElement>(element);
    return returnElement;
}

MarkdownParser::MarkdownDocument::VInlineMarkdownElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::createStrongEmphasisElement(const std::wstring &text) {
    auto substitute = substitutedAtomic(text);
    Recursive<MarkdownDocument::StrongEmphasisElement> strongEmphasisElement = make_recursive<MarkdownDocument::StrongEmphasisElement>(
            substitute[0]);
    strongEmphasisElement->push_back_many(std::next(std::begin(substitute), 1),
                                          std::end(substitute));
    MarkdownDocument::VInlineMarkdownElement returnElement = strongEmphasisElement;
    return returnElement;
}

MarkdownParser::MarkdownDocument::VInlineMarkdownElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::createStrongEmphasisElement(
        MarkdownDocument::VInlineMarkdownElement element) {
    MarkdownDocument::VInlineMarkdownElement returnElement = make_recursive<MarkdownDocument::StrongEmphasisElement>(
            element);
    return returnElement;
}

MarkdownParser::MarkdownDocument::VInlineMarkdownElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::createStrikethroughElement(const std::wstring &text) {
    auto substitute = substitutedAtomic(text);
    Recursive<MarkdownDocument::StrikethroughElement> strikethroughElement = make_recursive<MarkdownDocument::StrikethroughElement>(
            substitute[0]);
    strikethroughElement->push_back_many(std::next(std::begin(substitute), 1),
                                         std::end(substitute));
    MarkdownDocument::VInlineMarkdownElement returnElement = strikethroughElement;
    return returnElement;
}

MarkdownParser::MarkdownDocument::VInlineMarkdownElement
MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::createStrikethroughElement(
        MarkdownDocument::VInlineMarkdownElement element) {
    MarkdownDocument::VInlineMarkdownElement returnElement = make_recursive<MarkdownDocument::StrikethroughElement>(
            element);
    return returnElement;
}

void MarkdownParser::MarkdownParser::MarkdownInlineElementsParser::addPlainTextElementIfExists(std::wstring &text,
                                                                                               std::vector<MarkdownDocument::VInlineMarkdownElement> &lineElems) {
    if (!text.empty()) {
        auto substitute = substitutedAtomic(text);
        if (!substitute.empty()) {
            lineElems.insert(std::end(lineElems), std::move_iterator(std::begin(substitute)),
                             std::move_iterator(std::end(substitute)));
        }
        text = L"";
    }
}




