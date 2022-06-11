#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QObject>
#include <QtQml/qqml.h>
#include <atomic>
#include <semaphore>
#include <unordered_map>
#include <memory>

class Tab;

class TabManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(std::unordered_map<unsigned short, std::shared_ptr<Tab>> openedTabs READ openedTabs NOTIFY openedTabsChanged)
public:
    static TabManager &GetInstance();

    Q_INVOKABLE
    void createTab(const QString &filename);

    Q_INVOKABLE
    const std::shared_ptr<Tab> &getTabById(unsigned short id);

    Q_INVOKABLE
    const std::unordered_map<unsigned short, std::shared_ptr<Tab>> &openedTabs();

    Q_INVOKABLE
    void closeTab(unsigned short id);

    void addTabAndAssignId(Tab* tab);
    void assignTabId(Tab* tab);

private:
    TabManager();
    void addTab(Tab* tab);

    std::atomic<unsigned short> lastIssuedId{0};
    std::unordered_map<unsigned short, std::shared_ptr<Tab>> m_openedTabs{};
    std::binary_semaphore s_openedTabs{1};

signals:
    void openedTabsChanged();
};

#endif // TABMANAGER_H
