#ifndef MARKDOWNFILEMANAGER_H
#define MARKDOWNFILEMANAGER_H

#include <QObject>
#include <QString>
#include <QFuture>
#include "converters/iconverter.h"
#include "lib/src/markdown-parser/markdown-document/markdowndocument.h"

class MarkdownFileManager : public QObject
{
    Q_OBJECT
public:
    static MarkdownFileManager &GetInstance();

    Q_INVOKABLE
    QFuture<QString> open(const QString &filename);

    Q_INVOKABLE
    void save(const QString &filename, const QString &document);

    Q_INVOKABLE
    template <typename T = IConverter>
    void save(const QString &filename, MarkdownParser::MarkdownDocument::MarkdownDocument document);

private:
    MarkdownFileManager();
    void save(const QString &filename, MarkdownParser::MarkdownDocument::MarkdownDocument document, std::unique_ptr<IConverter> converter);
};

template<typename T>
void MarkdownFileManager::save(const QString &filename, MarkdownParser::MarkdownDocument::MarkdownDocument document)
{
    MarkdownFileManager::save(filename, document, std::move(std::unique_ptr<T>()));
}

#endif // MARKDOWNFILEMANAGER_H
