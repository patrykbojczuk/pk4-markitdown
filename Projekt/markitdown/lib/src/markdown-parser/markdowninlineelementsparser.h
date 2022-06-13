#ifndef MARKDOWNINLINEELEMENTSPARSER_H
#define MARKDOWNINLINEELEMENTSPARSER_H

#include <string>
#include <vector>
#include <regex>
#include "markdown-document/markdowndocument.h"
#include "markdown-document/markdown-elements/textlineelement.h"
#include "linkablereference.h"

namespace MarkdownParser {
    namespace MarkdownParser {
        class MarkdownInlineElementsParser {
        public:
            static MarkdownDocument::TextLineElement parse(const std::wstring &markdownSource,
                                                           const std::function<LinkableReference(
                                                                   const std::wstring &refId)> &getReference);

            static void clearAtomics();

        private:
            std::wstring markdownSource;
            static inline std::vector<MarkdownDocument::VInlineMarkdownElement> atomics{}; // leafs - they don't nest other inline elements

            std::function<LinkableReference(const std::wstring &refId)> getReference;

            MarkdownInlineElementsParser(const std::wstring &markdownSource,
                                         const std::function<LinkableReference(
                                                 const std::wstring &refId)> &getReference);

            // parses atomic elements, stores them in atomics vector
            // and substitutes them with \0x07\{atomics index}\0x07 (\0x07 is BEL) in markdownSource
            void parseAndSubstituteAtomicElements();

            // parses nested elements and replaces substitutions with atomics
            MarkdownDocument::TextLineElement parseNestedElementsAndReplaceSubstitutions();

            void substituteMatchedAtomic(const std::wsmatch &match);

            void addPlainTextElementIfExists(std::wstring &text,
                                             std::vector<MarkdownDocument::VInlineMarkdownElement> &lineElems);

            MarkdownDocument::VInlineMarkdownElement createEmphasisElement(const std::wstring &text);

            MarkdownDocument::VInlineMarkdownElement
            createEmphasisElement(MarkdownDocument::VInlineMarkdownElement element);

            MarkdownDocument::VInlineMarkdownElement createStrongEmphasisElement(const std::wstring &text);

            MarkdownDocument::VInlineMarkdownElement
            createStrongEmphasisElement(MarkdownDocument::VInlineMarkdownElement element);

            MarkdownDocument::VInlineMarkdownElement createStrikethroughElement(const std::wstring &text);

            MarkdownDocument::VInlineMarkdownElement
            createStrikethroughElement(MarkdownDocument::VInlineMarkdownElement element);

            std::vector<MarkdownDocument::VInlineMarkdownElement>
            substitutedAtomic(const std::wstring &text);

            std::vector<MarkdownDocument::VInlineMarkdownElement>
            substitutedAtomic(const MarkdownDocument::TextLineElement &nestedTextLine);
        };
    };
};

#endif //MARKDOWNINLINEELEMENTSPARSER_H
