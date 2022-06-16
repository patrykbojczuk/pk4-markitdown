#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QObject>
#include <QtQml/qqml.h>
#include <atomic>
#include <semaphore>
#include <QHash>
#include <QSharedPointer>
#include "tab.h"

class TabManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QHash<unsigned short, QSharedPointer<Tab>> openedTabs READ openedTabs NOTIFY openedTabsChanged)
public:
    static TabManager &GetInstance();

    Q_INVOKABLE
    void createTab(const QString &filename);

    Q_INVOKABLE
    Tab *getTabById(unsigned short id);

    const QHash<unsigned short, QSharedPointer<Tab>> &openedTabs();

    Q_INVOKABLE
    void closeTab(unsigned short id);

    unsigned short addTabAndGetId(Tab* tab);
    unsigned short getNextId();

    Q_INVOKABLE
    void saveAll(bool force = false);

private:
    TabManager();
    void addTab(unsigned short id, Tab* tab);

    void tabSavedContent(Tab* tab);

    std::atomic<unsigned short> lastIssuedId{0};
    QHash<unsigned short, QSharedPointer<Tab>> m_openedTabs{};
    std::binary_semaphore s_openedTabs{1};
    std::binary_semaphore s_lastSaveContentHash{1};
    QHash<unsigned short, QByteArray> lastSaveContentHash;

signals:
    void openedTabsChanged();
    void focusOnTab(int id);

    Q_SIGNAL
    void tabOpened(unsigned short tabId);
    Q_SIGNAL
    void tabClosed(unsigned short tabId);
};

#endif // TABMANAGER_H
