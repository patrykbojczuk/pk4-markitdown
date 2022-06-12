#ifndef REGEX_DEFS_H
#define REGEX_DEFS_H

/** TOKENIZER **/
#define BLOCKQUOTE_TOKEN_REGEXP LR";(^>[ ]?(.*));"
#define CODEBLOCK_TOKEN_REGEXP LR";(^`{3}(.*));"
#define L1_HEADER_UNDERLINE_TOKEN_REGEXP LR";(^={1,}\s*$);"
#define L2_HEADER_UNDERLINE_TOKEN_REGEXP LR";(^-{1,}\s*$);"
#define HEADER_TOKEN_REGEXP LR";(^(#{1,6})\s+(.*)$);"
#define HEADER_TOKEN_SUB_REGEXP LR";(^(.*)\s+\{#(.*)\}\s*$);"
#define HORIZONTAL_RULE_TOKEN_REGEXP LR";(^([-_*][ \t]*){3,}$);"
#define UNORDERED_LIST_TOKEN_REGEXP LR";(^([ ]*)[-*+]\s+(.+)$);"
#define ORDERED_LIST_TOKEN_REGEXP LR";(^\d+\.\s+(.+)$);"
#define LINKABLE_REFERENCE_REGEXP LR";(^\s*\[(.+)\]\s*:\s*(\S+)\s*(?:(?:\"|\')(.*?)(?:\"|\'))?\s*$);"

/** INLINE ELEMENTS **/
// ATOMICS //
#define INLINE_CODE_REGEXP LR";(`{1,2}(.+?)`{1,2});"
#define IMAGE_WITH_URL_REGEXP LR";(!\[(.+)\]\((.+?)(?:\s+(?:\"|\')(.+)(?:\"|\'))?\s*\));"
#define IMAGE_FROM_REF_REGEXP LR";(!\[(.+)\]\[(.+)\]);"
#define LINK_WITH_URL_REGEXP LR";(\[(.+)\]\((.+?)(?:\s+(?:\"|\')(.+)(?:\"|\'))?\s*\));"
#define LINK_FROM_REF_REGEXP LR";(\[(.+)\]\[(.+)\]);"
#define IMPLICIT_LINK_FROM_REF_REGEXP LR";(\[(.+)\]\[\]);"
#define LINK_LITERAL_REGEXP LR";(<(\w+:[^>]+)>);"
#define EMAIL_LITERAL_REGEXP LR";(<([a-zA-Z0-9.!#$%&’*+\/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*)>);"

#define ATOMIC_SUBSTITUTION_REGEXP LR";(\x07(\d+)\x07);"

// NESTABLE //
#define BOLD_REGEXP LR";(^(?:\*\*|__)(.+?)(?:\*\*|__));"
#define ITALIC_REGEXP LR";(^(?:\*|_)(.+?)(?:\*|_));"
#define STRIKETHROUGH_REGEXP LR";(^(?:~~)(.+?)(?:~~));"

#define BOLD_ITALIC_REGEXP LR";(^(?:(?:(?:\*\*|__)(?:\*|_))|(?:(?:\*|_)(?:\*\*|__)))(.+?)(?:(?:(?:\*\*|__)(?:\*|_))|(?:(?:\*|_)(?:\*\*|__))));"
#define BOLD_STRIKETHROUGH_REGEXP LR";(^(?:(?:(?:\*\*|__)(?:~~))|(?:(?:~~)(?:\*\*|__)))(.+?)(?:(?:(?:\*\*|__)(?:~~))|(?:(?:~~)(?:\*\*|__))));"
#define ITALIC_STRIKETHROUGH_REGEXP LR";(^(?:(?:(?:\*|_)(?:~~))|(?:(?:~~)(?:\*|_)))(.+?)(?:(?:(?:\*|_)(?:~~))|(?:(?:~~)(?:\*|_))));"

#define BOLD_ITALIC_STRIKETHROUGH_REGEXP LR";(^(?:(?:(?:\*\*|__)(?:\*|_)(?:~~))|(?:(?:\*\*|__)(?:~~)(?:\*|_))|(?:(?:\*|_)(?:\*\*|__)(?:~~))|(?:(?:\*|_)(?:~~)(?:\*\*|__))|(?:(?:~~)(?:\*\*|__)(?:\*|_))|(?:(?:~~)(?:\*|_)(?:\*\*|__)))(.+?)(?:(?:(?:\*\*|__)(?:\*|_)(?:~~))|(?:(?:\*\*|__)(?:~~)(?:\*|_))|(?:(?:\*|_)(?:\*\*|__)(?:~~))|(?:(?:\*|_)(?:~~)(?:\*\*|__))|(?:(?:~~)(?:\*\*|__)(?:\*|_))|(?:(?:~~)(?:\*|_)(?:\*\*|__))));"

#endif //REGEX_DEFS_H
