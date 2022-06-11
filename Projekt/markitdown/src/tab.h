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
#include "tabmanager.h"

class Tab : public QObject
{
    Q_OBJECT

    Q_PROPERTY(unsigned short id READ id NOTIFY idChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString htmlContent READ htmlContent NOTIFY htmlContentChanged)
public:
    Tab(const QString &filename);

    unsigned short id() const;

    const QString &content() const;
    const QString &htmlContent() const;

    void setContent(const QString &newContent);

    Q_INVOKABLE
    void save();

    Q_INVOKABLE
    template <typename T = IConverter>
    void save(const QString &filename);

private:
    unsigned short m_id;
    QString filename;
    QString m_content;
    QString m_htmlContent;

    std::binary_semaphore s_content{1};
    std::binary_semaphore s_parsedContent{1};

    HtmlConverter htmlConverter;

    void convertContentToHtml();
    void setHtmlContent(const QString &htmlContent);

    MarkdownParser::MarkdownDocument::MarkdownDocument getParsedContent();

    friend void TabManager::assignTabId(Tab *tab);

signals:
    void idChanged();
    void contentChanged();
    void htmlContentChanged();
};

template<typename T>
void Tab::save(const QString &filename)
{
    s_content.acquire();
    MarkdownFileManager::GetInstance().save<T>(filename, getParsedContent());
    s_content.release();
}

#endif // TAB_H
