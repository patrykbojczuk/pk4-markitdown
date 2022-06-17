#ifndef HTMLCONVERTER_H
#define HTMLCONVERTER_H

#include "iconverter.h"

class HtmlConverter : public IConverter
{
public:
    HtmlConverter();

    // IConverter interface
public:
    void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::CodeblockElement> &codeblock) override;
    void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::HeaderElement> &header) override;
    void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::ParagraphElement> &paragraph) override;
    void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::BlockquoteElement> &blockquote) override;
    void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::OrderedListElement> &orderedList) override;
    void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::UnorderedListElement> &unorderedList) override;
    void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::HorizontalRuleElement> &_) override;

    void listItemHandler(const MarkdownParser::MarkdownDocument::ListElement::VListItem &listItem) override;

    void multilineTextHandler(const MarkdownParser::MarkdownDocument::MultilineTextElement &multilineText) override;

    void textLineHandler(const MarkdownParser::MarkdownDocument::TextLineElement &textLine) override;

    void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::ImageElement> &image) override;
    void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::LinkElement> &link) override;
    void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::PlainTextElement> &plainText) override;
    void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::InlineCodeElement> &inlineCode) override;
    void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::EmphasisElement> &emphasis) override;
    void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::StrikethroughElement> &strikethrough) override;
    void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::StrongEmphasisElement> &strongEmphasis) override;

    virtual ~HtmlConverter() = default;
};

#endif // HTMLCONVERTER_H
