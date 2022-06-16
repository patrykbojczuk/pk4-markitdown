#include "tab.h"
#include "lib/src/markdown-parser/markdownparser.h"
#include "src/converters/htmlconverter.h"
#include <future>
#include "filemanager.h"
#include "tabmanager.h"
#include <QtConcurrent>
#include <QTextDocument>
#include <QPrinter>

const QString &Tab::content() const { return m_content; }

void Tab::setContent(const QString &newContent) {
    s_content.acquire();
    m_content = newContent;
    s_content.release();
    emit contentChanged();
    convertContentToHtml();
}

void Tab::save(const QString &filename) {
    if (filename != ""){
        setFilename(filename);
    }
    s_content.acquire();
    MarkdownFileManager::GetInstance().save(m_filename, content());
    s_content.release();
    emit contentSaved(this);
}

void Tab::exportHtml(const QString &filename)
{
    save<HtmlConverter>(filename);
}

void Tab::exportPdf(const QString &filename)
{
    qDebug() << "Start exporting PDF...";
    getParsedContent()
        .then([filename](const MarkdownParser::MarkdownDocument::MarkdownDocument& document){
            qDebug() << "Starting saving PDF...";
            MarkdownFileManager::GetInstance().savePdf(filename.sliced(7), document);
        });
}

void Tab::convertContentToHtml() {
    getParsedContent()
       .then([this](const MarkdownParser::MarkdownDocument::MarkdownDocument& document){
            return htmlConverter.convert(document);
        })
        .then([this](const QString& html){
            setHtmlContent(html);
        });
}

void Tab::setHtmlContent(const QString &convertedContent) {
    s_parsedContent.acquire();
    m_htmlContent = convertedContent;
    s_parsedContent.release();
    emit htmlContentChanged();
    //qDebug() << m_htmlContent << "\n\n";
}

void Tab::setFilename(const QString &filename)
{
    m_filename = filename;
    emit filenameChanged();
}

QFuture<MarkdownParser::MarkdownDocument::MarkdownDocument> Tab::getParsedContent() {
    s_content.acquire();
    auto WS_content = content().toStdWString();
    s_content.release();

    QFuture<MarkdownParser::MarkdownDocument::MarkdownDocument> future = QtConcurrent::run([WS_content](){
        return MarkdownParser::MarkdownParser::MarkdownParser::parse(WS_content);
    });
    return future;
}

Tab::Tab(const QString &filename, QObject *parent): QObject(parent) {
    MarkdownFileManager::GetInstance().open(filename).then([this](const QString& content){
        setContent(content);
    });
    m_filename = filename;
    emit filenameChanged();
    m_id = TabManager::GetInstance().addTabAndGetId(this);
    emit idChanged();
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
