#include "multilinetextelement.h"

MarkdownParser::MarkdownDocument::MultilineTextElement::MultilineTextElement(const TextLineElement &line)
{
    this->add(line);
}

void MarkdownParser::MarkdownDocument::MultilineTextElement::add(const TextLineElement &line)
{
    lines.push_back(line);
}

const std::vector<MarkdownParser::MarkdownDocument::TextLineElement> &MarkdownParser::MarkdownDocument::MultilineTextElement::getLines() const
{
    return lines;
}
