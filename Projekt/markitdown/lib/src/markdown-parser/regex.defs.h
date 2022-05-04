#ifndef REGEX_DEFS_H
#define REGEX_DEFS_H

#define BLOCKQUOTE_TOKEN_REGEXP LR";(^>[ ]?(.*));"
#define CODEBLOCK_TOKEN_REGEXP LR";(^`{3}(.*));"
#define L1_HEADER_UNDERLINE_TOKEN_REGEXP LR";(^={1,}\s*$);"
#define L2_HEADER_UNDERLINE_TOKEN_REGEXP LR";(^-{1,}\s*$);"
#define HEADER_TOKEN_REGEXP LR";(^(#{1,6})\s+(.*)$);"
#define HEADER_TOKEN_SUB_REGEXP LR";(^(.*)\s+\{#(.*)\}\s*$);"
#define HORIZONTAL_RULE_TOKEN_REGEXP LR";(^([-_*][ \t]*){3,}$);"
#define UNORDERED_LIST_TOKEN_REGEXP LR";(^([ ]*)[-*+]\s+(.+)$);"
#define ORDERED_LIST_TOKEN_REGEXP LR";(^\d+\.\s+(.+)$);"
#define LINKABLE_REFERENCE_REGEXP LR";(^\s*\[\s*([a-zA-Z0-9_-]+)\s*\]\s*:\s*(\S+)\s*(?:\"(.*?)\")?\s*$);"

#endif //REGEX_DEFS_H
