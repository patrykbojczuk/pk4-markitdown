#include "tabmanager.h"
#include "src/tab.h"

TabManager &TabManager::GetInstance()
{
    static TabManager tabManager;
    return tabManager;
}

void TabManager::createTab(const QString &filename)
{
    Tab *newTab = new Tab(filename, this);
    emit tabOpened(newTab->id());
}

Tab *TabManager::getTabById(unsigned short id) {
    return openedTabs().find(id).value().get();
}

const QHash<unsigned short, QSharedPointer<Tab>> &TabManager::openedTabs()
{
    return m_openedTabs;
}

void TabManager::closeTab(unsigned short id)
{
    s_openedTabs.acquire();
    m_openedTabs.remove(id);
    s_openedTabs.release();
    emit openedTabsChanged();
    emit tabClosed(id);
}

unsigned short TabManager::addTabAndGetId(Tab *tab)
{
    auto id = getNextId();
    addTab(id, tab);
    return id;
}

unsigned short TabManager::getNextId()
{
    return ++lastIssuedId;
}

TabManager::TabManager() { }

void TabManager::addTab(unsigned short id, Tab *tab)
{
    s_openedTabs.acquire();
    m_openedTabs.insert(id, QSharedPointer<Tab>(tab));
    s_openedTabs.release();
    emit openedTabsChanged();
}
