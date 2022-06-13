#include "htmlconverter.h"

HtmlConverter::HtmlConverter() { }

void HtmlConverter::topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::CodeblockElement> &codeblock)
{
    addToReturnString("<pre class=\"code-formatted\"><code>");
    for(const auto &line: codeblock->getLines()){
        addToReturnString(QString::fromStdWString(line.getText()).toHtmlEscaped() + "\n");
    }
    addToReturnString("</code></pre>");
}

void HtmlConverter::topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::HeaderElement> &header)
{
    unsigned short level = static_cast<unsigned short>(header->getLevel());
    addToReturnString("<h" + QString::number(level) + (header->hasId() ? " id=\"" + QString::fromStdWString(header->getId()) + "\"" : "") + ">");
    textLineHandler(header->getText());
    addToReturnString("</h" + QString::number(level) + ">");
}

void HtmlConverter::topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::ParagraphElement> &paragraph)
{
    addToReturnString("<p>");
    paragraphConverter(paragraph);
    addToReturnString("</p>");
}

void HtmlConverter::topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::BlockquoteElement> &blockquote)
{
    addToReturnString("<blockquote>");
    HtmlConverter converter;
    addToReturnString(converter.convert(blockquote->getDocument()));
    addToReturnString("</blockquote>");
}

void HtmlConverter::topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::OrderedListElement> &orderedList)
{
    addToReturnString("<ol>");
    for (const auto& listItem: orderedList->getItems()){
        listItemHandler(listItem);
    }
    addToReturnString("</ol>");
}

void HtmlConverter::topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::UnorderedListElement> &unorderedList)
{
    addToReturnString("<ul>");
    for (const auto& listItem: unorderedList->getItems()){
        listItemHandler(listItem);
    }
    addToReturnString("</ul>");
}

void HtmlConverter::topLevelHandler(const Recursive<MarkdownParser::MarkdownDocument::HorizontalRuleElement> &_)
{
    addToReturnString("<hr />");
}

void HtmlConverter::listItemHandler(const MarkdownParser::MarkdownDocument::ListElement::VListItem &listItem)
{
    addToReturnString("<li>");
    listItemConverter(listItem);
    addToReturnString("</li>");
}

void HtmlConverter::multilineTextHandler(const MarkdownParser::MarkdownDocument::MultilineTextElement &multilineText)
{
    if (multilineText.getLines().size()) {
        textLineHandler(multilineText.getLines()[0]);
    }
    for (auto lineIt = std::next(multilineText.getLines().cbegin(), 1); lineIt != multilineText.getLines().cend(); ++lineIt){
        addToReturnString("<br />");
        textLineHandler(*lineIt);
    }
}

void HtmlConverter::textLineHandler(const MarkdownParser::MarkdownDocument::TextLineElement &textLine)
{
    //addToReturnString("<span>");
    textLineConverter(textLine);
    //addToReturnString("</span>");
}

void HtmlConverter::inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::ImageElement> &image)
{
    addToReturnString("<img src=\"" + QString::fromStdWString(image->getUrl()) + "\" alt=\"" + QString::fromStdWString(image->getText()) + "\"" + (image->hasTitle() ? " title=\"" + QString::fromStdWString(image->getTitle()) + "\"" : "") + " />");
}

void HtmlConverter::inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::LinkElement> &link)
{
    addToReturnString("<a href=\"" + QString::fromStdWString(link->getUrl()) + "\"" + (link->hasTitle() ? " title=\"" + QString::fromStdWString(link->getTitle()) + "\"" : "") + ">" + QString::fromStdWString(link->getText()) + "</a>");
}

void HtmlConverter::inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::PlainTextElement> &plainText)
{
    addToReturnString(QString::fromStdWString(plainText->getText()));
}

void HtmlConverter::inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::InlineCodeElement> &inlineCode)
{
    addToReturnString("<code class=\"inline-code\">" + QString::fromStdWString(inlineCode->getText()) + "</code>");
}

void HtmlConverter::inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::EmphasisElement> &emphasis)
{
    addToReturnString("<em>");
    emphasisConverter(emphasis);
    addToReturnString("</em>");
}

void HtmlConverter::inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::StrikethroughElement> &strikethrough)
{
    addToReturnString("<s>");
    strikethroughConverter(strikethrough);
    addToReturnString("</s>");
}

void HtmlConverter::inlineElementHandler(const Recursive<MarkdownParser::MarkdownDocument::StrongEmphasisElement> &strongEmphasis)
{
    addToReturnString("<strong>");
    strongEmphasisConverter(strongEmphasis);
    addToReturnString("</strong>");
}
