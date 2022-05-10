#include "listelement.h"

MarkdownParser::MarkdownDocument::ListElement::ListElement(
        const VListItem &item) {
    this->add(item);
}

void
MarkdownParser::MarkdownDocument::ListElement::add(const VListItem &item) {
    items.push_back(item);
}

const std::vector<MarkdownParser::MarkdownDocument::ListElement::VListItem> &
MarkdownParser::MarkdownDocument::ListElement::getItems() const {
    return items;
}

MarkdownParser::MarkdownDocument::ListElement::VListItem &
MarkdownParser::MarkdownDocument::ListElement::operator[](int pos) {
    return items.at(pos);
}
