#include "markdownfilemanager.h"
#include <QtConcurrent>
#include <QTextDocument>
#include <QPrinter>
#include "filemanager.h"
#include "lib/src/markdown-parser/markdownparser.h"
#include "converters/htmlconverter.h"

MarkdownFileManager::MarkdownFileManager() {}


MarkdownFileManager &MarkdownFileManager::GetInstance()
{
    static MarkdownFileManager manager;
    return manager;
}

QFuture<QString> MarkdownFileManager::open(const QString &filename)
{
    if (filename.contains("file://")) {
        return FileManager::openTextFile(filename.sliced(7));
    }

    return FileManager::openTextFile(filename);
}

void MarkdownFileManager::save(const QString &filename, const QString &document)
{
    if (filename.contains("file://")) {
        FileManager::saveTextFile(filename.sliced(7), document);
        return;
    }

    FileManager::saveTextFile(filename, document);
}

void MarkdownFileManager::savePdf(const QString &filename, MarkdownParser::MarkdownDocument::MarkdownDocument document){
    QtConcurrent::run([document, filename](){
        HtmlConverter converter;

        QTextDocument textDocument;
        textDocument.setHtml(converter.convert(document));

        QPrinter printer(QPrinter::HighResolution);
        printer.setPageSize(QPageSize::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);

        printer.setOutputFileName(filename);

        textDocument.print(&printer);
    });
}

void MarkdownFileManager::save(const QString &filename, const MarkdownParser::MarkdownDocument::MarkdownDocument &document, std::unique_ptr<IConverter> &converter)
{
    if (filename.contains("file://")) {
        MarkdownFileManager::save(filename.sliced(7), converter->convert(document));
        return;
    }
    MarkdownFileManager::save(filename, converter->convert(document));
}
