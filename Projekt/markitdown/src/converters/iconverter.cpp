#include "iconverter.h"

QString IConverter::convert(
    const MarkdownParser::MarkdownDocument::MarkdownDocument &document) {
    returnString = "";
    topLevelConverter(document.getElements());
    return returnString;
}

void IConverter::topLevelConverter(
    const std::vector<
        MarkdownParser::MarkdownDocument::VTopLevelMarkdownElement> &elements) {
    for (const auto &element : elements) {
        if (element.index() != std::variant_npos){
            std::visit([this](auto &&el) { topLevelHandler(el); }, element);
        }
    }
}
