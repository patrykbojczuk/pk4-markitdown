#ifndef TAB_H
#define TAB_H

#include <atomic>
#include <unordered_map>
#include <memory>
#include <semaphore>
#include <QString>
#include <QObject>
#include "lib/src/markdown-parser/markdown-document/markdowndocument.h"
#include "lib/src/markdown-parser/markdownparser.h"
#include "src/converters/iconverter.h"
#include "src/converters/htmlconverter.h"
#include "markdownfilemanager.h"
#include <QFuture>

class Tab : public QObject
{
    Q_OBJECT

    Q_PROPERTY(unsigned short id READ id NOTIFY idChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString htmlContent READ htmlContent NOTIFY htmlContentChanged)
    Q_PROPERTY(QString filename READ filename NOTIFY filenameChanged)
public:
    Tab(const QString &filename, QObject *parent = nullptr);

    unsigned short id() const;

    const QString &content() const;
    const QString &htmlContent() const;

    void setContent(const QString &newContent);

    Q_INVOKABLE
    void save(const QString &filename = "");

    Q_INVOKABLE
    void exportHtml(const QString &filename);
    Q_INVOKABLE
    void exportPdf(const QString &filename);

    const QString &filename() const;

    Q_INVOKABLE
    QString getFilenameStem() const;

    Q_INVOKABLE
    void close();

private:
    unsigned short m_id;
    QString m_filename;
    QString m_content;
    QString m_htmlContent;

    std::binary_semaphore s_content{1};
    std::binary_semaphore s_parsedContent{1};

    HtmlConverter htmlConverter;

    void convertContentToHtml();
    void setHtmlContent(const QString &htmlContent);

    template <typename T = IConverter>
    void save(const QString &filename);

    void setFilename(const QString &filename);

    QFuture<MarkdownParser::MarkdownDocument::MarkdownDocument> getParsedContent();

signals:
    void idChanged();
    void contentChanged();
    void htmlContentChanged();
    void filenameChanged();
    void contentSaved(Tab* thisTab);
};

template<typename T>
void Tab::save(const QString &filename)
{
    getParsedContent().then([filename](const MarkdownParser::MarkdownDocument::MarkdownDocument &document){
        MarkdownFileManager::GetInstance().save<T>(filename, document);
    });
}

#endif // TAB_H
