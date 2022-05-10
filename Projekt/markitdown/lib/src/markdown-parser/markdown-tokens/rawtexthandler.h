#ifndef RAWTEXTHANDLER_H
#define RAWTEXTHANDLER_H

#include <string>

class RawTextHandler {
private:
    std::wstring rawText;

public:
    RawTextHandler(const std::wstring &rawText = L"");

    const std::wstring &getRawText() const;
};


#endif //RAWTEXTHANDLER_H
