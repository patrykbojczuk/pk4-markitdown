#include "tab.h"
#include "lib/src/markdown-parser/markdownparser.h"
#include "src/converters/htmlconverter.h"
#include <future>
#include "tabmanager.h"

const QString &Tab::content() const { return m_content; }

void Tab::setContent(const QString &newContent) {
    s_content.acquire();
    m_content = newContent;
    s_content.release();
    emit contentChanged();
    convertContentToHtml();
}

void Tab::save() {
    s_content.acquire();
    MarkdownFileManager::GetInstance().save(filename, content());
    s_content.release();
}

void Tab::convertContentToHtml() {
    setHtmlContent(htmlConverter.convert(getParsedContent()));
}

void Tab::setHtmlContent(const QString &parsedContent) {
    s_parsedContent.acquire();
    m_htmlContent = parsedContent;
    s_parsedContent.release();
    emit htmlContentChanged();
}

MarkdownParser::MarkdownDocument::MarkdownDocument Tab::getParsedContent() {
    s_content.acquire();
    auto returnDoc = MarkdownParser::MarkdownParser::MarkdownParser::parse(content().toStdWString());
    s_content.release();
    return returnDoc;
}

Tab::Tab(const QString &filename) {
    auto fileContent = std::async([filename](){return MarkdownFileManager::GetInstance().open(filename);});
    TabManager::GetInstance().addTabAndAssignId(this);
    setContent(fileContent.get());
}

unsigned short Tab::id() const { return m_id; }

const QString &Tab::htmlContent() const { return m_htmlContent; }
