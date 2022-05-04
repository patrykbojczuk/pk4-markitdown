#include "gtest/gtest.h"
#include "../../markdowntokenizer.h"

TEST(MarkdownTokenizer, CreatesNoTokensOnEmptyString) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer(L"");
    EXPECT_EQ(tokenizer.getTokens().size(), 0);
}

TEST(MarkdownTokenizer, CreatesEmptyTokens) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer(L"\n  \n \n\t\n");
    EXPECT_EQ(tokenizer.getTokens().size(), 5);
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokenizer.getTokens()[0]);
            std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokenizer.getTokens()[1]);
            std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokenizer.getTokens()[2]);
            std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokenizer.getTokens()[3]);
            std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokenizer.getTokens()[4]);
    );
}

TEST(MarkdownTokenizer, CreatesHeaderLvl1) {
    // should create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"# Header 1");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level6;
    std::wstring text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level1);
    EXPECT_STREQ(text.c_str(), L"Header 1");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"# Header 1 #  ");
    level = MarkdownHeaderLevel::Level6;
    text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level1);
    EXPECT_STREQ(text.c_str(), L"Header 1");

    // should not create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"#Header 1");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer3.getTokens()[0]),
            std::bad_variant_access
    );
}

TEST(MarkdownTokenizer, CreatesHeaderUnderlineLvl1) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"Header 1\n========");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level6;
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderUnderlineToken>(tokenizer1.getTokens()[1]).getLevel()
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level1);

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"Header 1\n=");
    level = MarkdownHeaderLevel::Level6;
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderUnderlineToken>(tokenizer2.getTokens()[1]).getLevel()
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level1);
}

TEST(MarkdownTokenizer, CreatesHeaderLvl2) {
    // should create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"## Header 2");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level6;
    std::wstring text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level2);
    EXPECT_STREQ(text.c_str(), L"Header 2");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"## Header 2 ##  ");
    level = MarkdownHeaderLevel::Level6;
    text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level2);
    EXPECT_STREQ(text.c_str(), L"Header 2");

    // should not create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"##Header 2");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer3.getTokens()[0]),
            std::bad_variant_access
    );
}

TEST(MarkdownTokenizer, CreatesHeaderUnderlineLvl2) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"Header 2\n--------");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level6;
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderUnderlineToken>(tokenizer1.getTokens()[1]).getLevel()
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level2);

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"Header 2\n-");
    level = MarkdownHeaderLevel::Level6;
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderUnderlineToken>(tokenizer2.getTokens()[1]).getLevel()
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level2);
}

TEST(MarkdownTokenizer, CreatesHeaderLvl3) {
    // should create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"### Header 3");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level6;
    std::wstring text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level3);
    EXPECT_STREQ(text.c_str(), L"Header 3");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"### Header 3 ###  ");
    level = MarkdownHeaderLevel::Level6;
    text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level3);
    EXPECT_STREQ(text.c_str(), L"Header 3");

    // should not create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"###Header 3");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer3.getTokens()[0]),
            std::bad_variant_access
    );
}

TEST(MarkdownTokenizer, CreatesHeaderLvl4) {
    // should create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"#### Header 4");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level6;
    std::wstring text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level4);
    EXPECT_STREQ(text.c_str(), L"Header 4");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"#### Header 4 ####  ");
    level = MarkdownHeaderLevel::Level6;
    text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level4);
    EXPECT_STREQ(text.c_str(), L"Header 4");

    // should not create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"####Header 4");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer3.getTokens()[0]),
            std::bad_variant_access
    );
}

TEST(MarkdownTokenizer, CreatesHeaderLvl5) {
    // should create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"##### Header 5");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level6;
    std::wstring text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level5);
    EXPECT_STREQ(text.c_str(), L"Header 5");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"##### Header 5 #####  ");
    level = MarkdownHeaderLevel::Level6;
    text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level5);
    EXPECT_STREQ(text.c_str(), L"Header 5");

    // should not create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"#####Header 5");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer3.getTokens()[0]),
            std::bad_variant_access
    );
}

TEST(MarkdownTokenizer, CreatesHeaderLvl6) {
    // should create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"###### Header 6");
    MarkdownHeaderLevel level = MarkdownHeaderLevel::Level1;
    std::wstring text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer1.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level6);
    EXPECT_STREQ(text.c_str(), L"Header 6");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"###### Header 6 ######  ");
    level = MarkdownHeaderLevel::Level1;
    text = L"";
    EXPECT_NO_THROW(
            level = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getLevel();
            text = std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer2.getTokens()[0]).getText();
    );
    EXPECT_EQ(level, MarkdownHeaderLevel::Level6);
    EXPECT_STREQ(text.c_str(), L"Header 6");

    // should not create header
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"######Header 6");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokenizer3.getTokens()[0]),
            std::bad_variant_access
    );
}

TEST(MarkdownTokenizer, CreatesBlockquotes) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer(L">Blockquote\n>>Blockquote2");
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::BlockquoteToken>(tokenizer.getTokens()[0]);
            std::get<MarkdownParser::MarkdownParser::BlockquoteToken>(tokenizer.getTokens()[1]);
    );
}

TEST(MarkdownTokenizer, CreatesCode) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer(
            L"```typescript\n    let test = () => {\n        code();\n    }\n```");
    std::wstring language1 = L"",
            language2 = L"";
    EXPECT_NO_THROW(
            language1 = std::get<MarkdownParser::MarkdownParser::CodeToken>(tokenizer.getTokens()[0]).getLanguage();
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokenizer.getTokens()[1]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokenizer.getTokens()[2]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokenizer.getTokens()[3]);
            language2 = std::get<MarkdownParser::MarkdownParser::CodeToken>(tokenizer.getTokens()[4]).getLanguage();
    );

    EXPECT_STREQ(language1.c_str(), L"typescript");
    EXPECT_STREQ(language2.c_str(), L"");
}

TEST(MarkdownTokenizer, CreatesHorizontalRule) {
    // should create HR
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"___");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"---");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"***");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer4(L"____");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer5(L"----");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer6(L"****");

    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer7(L"_ _ _  _");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer8(L"--   - -");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer9(L"*  *      **");

    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer1.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer2.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer3.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer4.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer5.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer6.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer7.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer8.getTokens()[0]);
    );
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer9.getTokens()[0]);
    );

    // should not create HR
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer10(L"__");
    // MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer11(L"--");
    //      - it can actually happen as HeaderUnderlineToken collision creates HorizontalRuleToken by default
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer12(L"**");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer10.getTokens()[0]),
            std::bad_variant_access
    );
//    EXPECT_THROW(
//            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer11.getTokens()[0]),
//            std::bad_variant_access
//    );
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer12.getTokens()[0]),
            std::bad_variant_access);


    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer13(L"Example text\n----");
    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokenizer13.getTokens()[1]),
            std::bad_variant_access
    );
}

TEST(MarkdownTokenizer, CreatesOrderedList) {
    // should create list element
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"1. First element\n2. Second\n5. Third");

    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokenizer1.getTokens()[0]);
            std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokenizer1.getTokens()[1]);
            std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokenizer1.getTokens()[2]);
    );

    // should not create list element
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"1.First element\n2.Second\n5.Third");

    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokenizer2.getTokens()[0]);
            std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokenizer2.getTokens()[1]);
            std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokenizer2.getTokens()[2]);,
            std::bad_variant_access);
}

TEST(MarkdownTokenizer, CreatesUnorderedList) {
    // should create list element
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"- First element\n* Second\n+ Third");

    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokenizer1.getTokens()[0]);
            std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokenizer1.getTokens()[1]);
            std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokenizer1.getTokens()[2]);
    );

    // should not create list element
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(L"-First element\n*Second\n+Third");

    EXPECT_THROW(
            std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokenizer2.getTokens()[0]);
            std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokenizer2.getTokens()[1]);
            std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokenizer2.getTokens()[2]);,
            std::bad_variant_access);
}

TEST(MarkdownTokenizer, AddsLinkableReferences) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer1(L"[test-id]:https://example.com/ \"Example title\"");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer2(
            L"  [test-id]  :  https://example.com/    \"Example title\"   ");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer3(L"  [test-id]  :  https://example.com/     ");
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer4(
            L"  [test-id]  :  https://example.com/     \n[test-id]:https://polsl.pl/ \"Politechnika Śląska\"");

    EXPECT_STREQ(tokenizer1.getReference(L"test-id").url.c_str(), L"https://example.com/");
    EXPECT_STREQ(tokenizer1.getReference(L"test-id").title.c_str(), L"Example title");

    EXPECT_STREQ(tokenizer2.getReference(L"test-id").url.c_str(), L"https://example.com/");
    EXPECT_STREQ(tokenizer2.getReference(L"test-id").title.c_str(), L"Example title");

    EXPECT_STREQ(tokenizer3.getReference(L"test-id").url.c_str(), L"https://example.com/");
    EXPECT_STREQ(tokenizer3.getReference(L"test-id").title.c_str(), L"");

    EXPECT_STREQ(tokenizer4.getReference(L"test-id").url.c_str(), L"https://polsl.pl/");
    EXPECT_STREQ(tokenizer4.getReference(L"test-id").title.c_str(), L"Politechnika Śląska");
}

TEST(MarkdownTokenizer, Combination) {
    MarkdownParser::MarkdownParser::MarkdownTokenizer tokenizer(
            LR";(##### Sed sed placerat elit.
Nunc ac rhoncus risus. Phasellus viverra erat quis tempus bibendum. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.
- - -
- First element
- Second element
  - Subelement
- Third element

1. First element
2. Second element
  - Subelement
3. Third element

>Nullam vel lorem eu risus dapibus posuere.
>>Aliquam venenatis luctus malesuada.

```typescript
const isPrime = (num: number) => {
    for (let i = 2; i*i <= num; ++i) {
        if (!(num % i)) {
            return false
        }
    }
    return num >= 2
}
```

Curabitur id eros leo.
---

Duis ornare libero varius quam blandit, id lobortis ante ultrices. Morbi rutrum et lectus ut mollis. Nulla magna ante, congue ut purus non, accumsan finibus lacus. Sed tincidunt placerat enim, ac placerat nisl semper elementum.);");

    auto &tokens = tokenizer.getTokens();

    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::HeaderToken>(tokens[0]));          // Sed sed placerat elit.
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::PlainTextToken>(
            tokens[1]));       // Nunc ac ... inceptos himenaeos.
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::HorizontalRuleToken>(tokens[2]));  // - - -
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokens[3]));   // First element
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokens[4]));   // Second element
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokens[5]));   // Subelement
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokens[6]));   // Third element
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokens[7]));           // \n
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokens[8]));     // First element
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokens[9]));     // Second element
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::UnorderedListToken>(tokens[10]));  // Subelement
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::OrderedListToken>(tokens[11]));    // Third element
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokens[12]));          // \n
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::BlockquoteToken>(
            tokens[13]));     // Nullam vel lorem eu risus dapibus posuere.
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::BlockquoteToken>(
            tokens[14]));     // >Aliquam venenatis luctus malesuada.
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokens[15]));          // \n
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::CodeToken>(tokens[16]));           // typescript
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[17]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[18]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[19]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[20]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[21]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[22]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[23]);
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[24]);
    );
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::CodeToken>(tokens[25]));           //
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokens[26]));          // \n
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(tokens[27]));      // Curabitur id eros leo.
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::HeaderUnderlineToken>(tokens[28]));// Following tokens[27]
    EXPECT_NO_THROW(std::get<MarkdownParser::MarkdownParser::EmptyToken>(tokens[29]));          // \n
    EXPECT_NO_THROW(
            std::get<MarkdownParser::MarkdownParser::PlainTextToken>(
                    tokens[30]));      // Duis ornare ... semper elementum.
}
