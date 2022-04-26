#include "headerunderlinetoken.h"
#include <stdexcept>

MarkdownParser::MarkdownParser::HeaderUnderlineToken::HeaderUnderlineToken(MarkdownHeaderLevel level)
{
    switch (level){
        case MarkdownHeaderLevel::Level3:
        case MarkdownHeaderLevel::Level4:
        case MarkdownHeaderLevel::Level5:
        case MarkdownHeaderLevel::Level6:
            throw std::invalid_argument("HeaderUnderlineToken can only be level 1 or 2");
        case MarkdownHeaderLevel::Level1:
        case MarkdownHeaderLevel::Level2:
            break;
    }
    this->isLevel1 = ((int)level - 1);
}

MarkdownHeaderLevel MarkdownParser::MarkdownParser::HeaderUnderlineToken::getLevel() const
{
    return (MarkdownHeaderLevel)(this->isLevel1 + 1);
}
