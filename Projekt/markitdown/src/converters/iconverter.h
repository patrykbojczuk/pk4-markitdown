#ifndef ICONVERTER_H
#define ICONVERTER_H

#include <QString>
#include <QTextStream>
#include "lib/src/markdown-parser/markdown-document/markdowndocument.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/codeblockelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/headerelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/paragraphelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/blockquoteelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/orderedlistelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/unorderedlistelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/horizontalruleelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/multilinetextelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/textlineelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/imageelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/linkelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/plaintextelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/inlinecodeelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/emphasiselement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/strikethroughelement.h"
#include "lib/src/markdown-parser/markdown-document/markdown-elements/strongemphasiselement.h"

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class IConverter
{
public:
    QString convert(const MarkdownParser::MarkdownDocument::MarkdownDocument &document);

    inline void listItemConverter(const MarkdownParser::MarkdownDocument::ListElement::VListItem& listItem);
    inline void textLineConverter(const MarkdownParser::MarkdownDocument::TextLineElement &textLine);
    inline void paragraphConverter(const Recursive<MarkdownParser::MarkdownDocument::ParagraphElement> &paragraph);

    inline void inlineElementConverter(const MarkdownParser::MarkdownDocument::VInlineMarkdownElement& inlineElement);

    inline void emphasisConverter(const Recursive<MarkdownParser::MarkdownDocument::EmphasisElement>& emphasis);
    inline void strikethroughConverter(const Recursive<MarkdownParser::MarkdownDocument::StrikethroughElement>& strikethrough);
    inline void strongEmphasisConverter(const Recursive<MarkdownParser::MarkdownDocument::StrongEmphasisElement>& strongEmphasis);

    virtual void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::CodeblockElement>& codeblock) = 0;
    virtual void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::HeaderElement>& header) = 0;
    virtual void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::ParagraphElement>& paragraph) = 0;
    virtual void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::BlockquoteElement>& blockquote) = 0;
    virtual void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::OrderedListElement>& orderedList) = 0;
    virtual void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::UnorderedListElement>& unorderedList) = 0;
    virtual void topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::HorizontalRuleElement>& horizontalRule) = 0;

    virtual void multilineTextHandler(const MarkdownParser::MarkdownDocument::MultilineTextElement& multilineText) = 0;

    virtual void textLineHandler(const MarkdownParser::MarkdownDocument::TextLineElement& textLine) = 0;

    virtual void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::ImageElement>& image) = 0;
    virtual void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::LinkElement>& link) = 0;
    virtual void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::PlainTextElement>& plainText) = 0;
    virtual void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::InlineCodeElement>& inlineCode) = 0;
    virtual void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::EmphasisElement>& emphasis) = 0;
    virtual void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::StrikethroughElement>& strikethrough) = 0;
    virtual void inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::StrongEmphasisElement>& strongEmphasis) = 0;

protected:
    IConverter() = default;
    inline void addToReturnString(const QString &string);

private:
    QString returnString;
    void topLevelConverter(const std::vector<MarkdownParser::MarkdownDocument::VTopLevelMarkdownElement> &elements);
};

void IConverter::listItemConverter(
    const MarkdownParser::MarkdownDocument::ListElement::VListItem &listItem) {
    if (listItem.index() != std::variant_npos) {
        std::visit(
          overloaded{
              [this](const Recursive<
                     MarkdownParser::MarkdownDocument::UnorderedListElement>
                         &unorderedList) { topLevelHandler(unorderedList); },
              [this](const Recursive<
                     MarkdownParser::MarkdownDocument::MultilineTextElement>
                         &multilineText) { multilineTextHandler(*multilineText); }},
          listItem);
    }
}

void IConverter::textLineConverter(
    const MarkdownParser::MarkdownDocument::TextLineElement &textLine) {
  for (const auto &inlineElement : textLine.getContents()) {
    inlineElementConverter(inlineElement);
  }
}

void IConverter::paragraphConverter(
    const Recursive<MarkdownParser::MarkdownDocument::ParagraphElement>
        &paragraph) {
  multilineTextHandler(
      static_cast<MarkdownParser::MarkdownDocument::MultilineTextElement>(
          *paragraph));
}

void IConverter::inlineElementConverter(
    const MarkdownParser::MarkdownDocument::VInlineMarkdownElement
        &inlineElement) {
    if (inlineElement.index() != std::variant_npos) {
        std::visit([this](auto &&el) { inlineElementHandler(el); }, inlineElement);
    }
}

void IConverter::emphasisConverter(
    const Recursive<MarkdownParser::MarkdownDocument::EmphasisElement>
        &emphasis) {
  textLineConverter(
      static_cast<MarkdownParser::MarkdownDocument::TextLineElement>(
          *emphasis));
}

void IConverter::strikethroughConverter(
    const Recursive<MarkdownParser::MarkdownDocument::StrikethroughElement>
        &strikethrough) {
  textLineConverter(
      static_cast<MarkdownParser::MarkdownDocument::TextLineElement>(
          *strikethrough));
}

void IConverter::strongEmphasisConverter(
    const Recursive<MarkdownParser::MarkdownDocument::StrongEmphasisElement>
        &strongEmphasis) {
  textLineConverter(
      static_cast<MarkdownParser::MarkdownDocument::TextLineElement>(
          *strongEmphasis));
}

void IConverter::addToReturnString(const QString &string) {
  returnString.append(string);
}

#endif // ICONVERTER_H
