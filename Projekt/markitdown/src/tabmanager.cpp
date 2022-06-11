#include "tabmanager.h"
#include "src/tab.h"

TabManager &TabManager::GetInstance()
{
    static TabManager tabManager;
    return tabManager;
}

void TabManager::createTab(const QString &filename)
{
    Tab newTab(filename);
}

const std::shared_ptr<Tab> &TabManager::getTabById(unsigned short id) {
    return openedTabs().at(id);
}

const std::unordered_map<unsigned short, std::shared_ptr<Tab>> &TabManager::openedTabs()
{
    return m_openedTabs;
}

void TabManager::closeTab(unsigned short id)
{
    s_openedTabs.acquire();
    m_openedTabs.erase(id);
    s_openedTabs.release();
    emit openedTabsChanged();
}

void TabManager::addTabAndAssignId(Tab *tab)
{
    assignTabId(tab);
    addTab(tab);
}

void TabManager::assignTabId(Tab *tab)
{
    unsigned short nextId = ++lastIssuedId;
    tab->m_id = nextId;
    emit tab->idChanged();
}

TabManager::TabManager() { }

void TabManager::addTab(Tab *tab)
{
    s_openedTabs.acquire();
    m_openedTabs.insert(make_pair(tab->id(), std::shared_ptr<Tab>(tab)));
    s_openedTabs.release();
    emit openedTabsChanged();
}
