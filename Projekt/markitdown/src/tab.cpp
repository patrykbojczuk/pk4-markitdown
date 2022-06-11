#include "tab.h"
#include "lib/src/markdown-parser/markdownparser.h"
#include "src/converters/htmlconverter.h"
#include <future>
#include "filemanager.h"
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
    MarkdownFileManager::GetInstance().save(m_filename, content());
    s_content.release();
}

void Tab::convertContentToHtml() {
    setHtmlContent(htmlConverter.convert(getParsedContent()));
}

void Tab::setHtmlContent(const QString &convertedContent) {
    s_parsedContent.acquire();
    m_htmlContent = convertedContent;
    s_parsedContent.release();
    emit htmlContentChanged();
}

MarkdownParser::MarkdownDocument::MarkdownDocument Tab::getParsedContent() {
    s_content.acquire();
    auto returnDoc = MarkdownParser::MarkdownParser::MarkdownParser::parse(content().toStdWString());
    s_content.release();
    return returnDoc;
}

Tab::Tab(const QString &filename, QObject *parent): QObject(parent) {
    auto fileContent = std::async([filename](){return MarkdownFileManager::GetInstance().open(filename);});
    m_filename = filename;
    emit filenameChanged();
    m_id = TabManager::GetInstance().addTabAndGetId(this);
    emit idChanged();
    setContent(fileContent.get());
}

unsigned short Tab::id() const { return m_id; }

const QString &Tab::htmlContent() const { return m_htmlContent; }

const QString &Tab::filename() const
{
    return m_filename;
}

QString Tab::getFilenameStem() const
{
    return FileManager::getFilenameStem(filename());
}

void Tab::close()
{
    TabManager::GetInstance().closeTab(id());
}
