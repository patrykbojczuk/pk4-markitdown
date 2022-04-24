#include "listelement.h"

MarkdownParser::MarkdownDocument::ListElement::ListElement(MultilineTextElement &item)
{
    this->add(item);
}

void MarkdownParser::MarkdownDocument::ListElement::add(MultilineTextElement &item)
{
    items.push_back(item);
}

const std::vector<MarkdownParser::MarkdownDocument::MultilineTextElement> &MarkdownParser::MarkdownDocument::ListElement::getItems() const
{
    return items;
}
