#include "markdownfilemanager.h"
#include "filemanager.h"
#include "lib/src/markdown-parser/markdownparser.h"

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

void MarkdownFileManager::save(const QString &filename, MarkdownParser::MarkdownDocument::MarkdownDocument document, std::unique_ptr<IConverter> converter)
{
    if (filename.contains("file://")) {
        MarkdownFileManager::save(filename.sliced(7), converter->convert(document));
        return;
    }
    MarkdownFileManager::save(filename, converter->convert(document));
}
