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

private:
    TabManager();
    void addTab(unsigned short id, Tab* tab);

    std::atomic<unsigned short> lastIssuedId{0};
    QHash<unsigned short, QSharedPointer<Tab>> m_openedTabs{};
    std::binary_semaphore s_openedTabs{1};

signals:
    void openedTabsChanged();

    Q_SIGNAL
    void tabOpened(unsigned short tabId);
    Q_SIGNAL
    void tabClosed(unsigned short tabId);
};

#endif // TABMANAGER_H
