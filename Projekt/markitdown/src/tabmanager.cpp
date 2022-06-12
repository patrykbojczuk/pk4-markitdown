#include "tabmanager.h"
#include "src/tab.h"
#include <QtConcurrent>
#include <QCryptographicHash>

TabManager &TabManager::GetInstance()
{
    static TabManager tabManager;
    return tabManager;
}

void TabManager::createTab(const QString &filename)
{
    Tab *newTab = new Tab(filename, this);
    emit tabOpened(newTab->id());
    connect(newTab, &Tab::contentSaved, this, &TabManager::tabSavedContent);
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
    s_lastSaveContentHash.acquire();
    lastSaveContentHash.remove(id);
    s_lastSaveContentHash.release();
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

void TabManager::saveAll(bool force)
{
    /*
    QtConcurrent::run([this, force](){
        if(force){
            for (auto tab : openedTabs()) {
                tab->save();
            }
            return;
        }
        bool valueToSave;
        for (auto tab : openedTabs()) {
            s_lastSaveContentHash.acquire();
            valueToSave = !lastSaveContentHash.contains(tab->id()) ||
                                                  QCryptographicHash::hash(tab->content().toUtf8(), QCryptographicHash::Md4)
                                                      != lastSaveContentHash.value(tab->id());
            s_lastSaveContentHash.release();
            if (valueToSave) {
                tab->save();
            }
        }
    });
    */
}

TabManager::TabManager() { }

void TabManager::addTab(unsigned short id, Tab *tab)
{
    s_openedTabs.acquire();
    m_openedTabs.insert(id, QSharedPointer<Tab>(tab));
    s_openedTabs.release();
    emit openedTabsChanged();
}

void TabManager::tabSavedContent(Tab *tab)
{
    QtConcurrent::run([this, tab]() {
        s_lastSaveContentHash.acquire();
        lastSaveContentHash.insert(tab->id(), QCryptographicHash::hash(tab->content().toUtf8(), QCryptographicHash::Md4));
        s_lastSaveContentHash.release();
    });
}
