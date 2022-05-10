#include "rawtexthandler.h"

RawTextHandler::RawTextHandler(const std::wstring &rawText) : rawText(rawText) {}

const std::wstring &RawTextHandler::getRawText() const {
    return rawText;
}
