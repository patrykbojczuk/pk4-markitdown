#include "configmanager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "tabmanager.h"

ConfigManager &ConfigManager::GetInstance()
{
    static ConfigManager manager;
    return manager;
}

unsigned short ConfigManager::fontSize() const
{
    return m_fontSize;
}

const QFont &ConfigManager::fontFamily() const
{
    return m_fontFamily;
}

const QStringList &ConfigManager::recentFiles() const
{
    return m_recentFiles;
}

bool ConfigManager::isAutosaveEnabled() const
{
    return m_autosave;
}

size_t ConfigManager::autosaveTimeout() const
{
    return m_autosaveTimeout;
}


void ConfigManager::setFontSize(unsigned short newFontSize, bool save)
{
    m_fontSize = newFontSize;
    if (save) {
        saveConfig();
    }
    emit fontSizeChanged();
}

void ConfigManager::setFontFamily(const QFont &newFontFamily, bool save)
{
    m_fontFamily = newFontFamily;
    if (save) {
        saveConfig();
    }
    emit fontFamilyChanged();
}

void ConfigManager::addRecentFile(const QString &newRecentFile, bool save)
{
    QString file(newRecentFile.startsWith("file://") 
                    ? newRecentFile.sliced(7) 
                        : newRecentFile);

    m_recentFiles.removeIf([file](const QString& elem){
        return elem == file;
    });
    m_recentFiles.push_back(file);
    if (save) {
        saveConfig();
    }
    emit recentFilesChanged();
}

void ConfigManager::setAutosave(bool newAutosave, bool save)
{
    if (!m_autosave && newAutosave){
        QMetaObject::invokeMethod(&autosaveTimer, [this](){
            autosaveTimer.start(m_autosave);
        }, Qt::QueuedConnection);
    }
    if (!newAutosave){
        QMetaObject::invokeMethod(&autosaveTimer, [this](){
            autosaveTimer.stop();
        }, Qt::QueuedConnection);
    }
    m_autosave = newAutosave;
    if (save) {
        saveConfig();
    }
    emit autosaveChanged();
}

void ConfigManager::setAutosaveTimeout(size_t newAutosaveTimeout, bool save)
{
    if (m_autosave){
        autosaveTimer.setInterval(newAutosaveTimeout);
    }
    m_autosaveTimeout = newAutosaveTimeout;
    if (save) {
        saveConfig();
    }
    emit autosaveTimeoutChanged();
}

void ConfigManager::saveConfig()
{
    QJsonObject obj;
    obj.insert("fontSize", m_fontSize);
    obj.insert("fontName", m_fontFamily.family());
    obj.insert("autosave", m_autosave);
    obj.insert("autosaveInterval_ms", QJsonValue((int)m_autosaveTimeout));
    obj.insert("recentFiles", QJsonValue(QJsonArray::fromStringList(m_recentFiles)));
    QJsonDocument doc;
    doc.setObject(obj);
    configFileManager.saveConfig(doc.toJson(QJsonDocument::JsonFormat::Compact));
}

const QString defaultConfig = "{\n"
                              "    \"fontSize\":12,\n"
                              "    \"fontName\":\"Poppins\",\n"
                              "    \"autosave\":true,\n"
                              "    \"autosaveInterval_ms\":5000,\n"
                              "    \"recentFiles\":[]\n"
                              "}";

void ConfigManager::loadConfig()
{
    configFileManager.openConfig(defaultConfig)
        .then([this](const QString& config){
            auto document = QJsonDocument::fromJson(config.toUtf8());

            setFontSize(document["fontSize"].toInteger(12), false);
            QString fontName = document["fontName"].toString("Poppins");
            QFont fontFamily;
            fontFamily.setFamily(fontName);
            setFontFamily(fontFamily, false);
            setAutosave(document["autosave"].toBool(true), false);
            setAutosaveTimeout(document["autosaveInterval_ms"].toInteger(5000), false);
            if (document["recentFiles"].isArray()) {
                auto recentFilesArray = document["recentFiles"].toArray();
                for (const auto& file: recentFilesArray) {
                    if (file.isString() && FileManager::fileExists(file.toString())) {
                        addRecentFile(file.toString(), false);
                    }
                }
            }

            finishedLoading = true;
    });
}

void ConfigManager::autosaveElapsed()
{
    TabManager::GetInstance().saveAll();
}

bool ConfigManager::getFinishedLoading() const
{
    return finishedLoading;
}

QString ConfigManager::getFilenameStem(const QString &filename)
{
    return FileManager::getFilenameStem(filename);
}

QString ConfigManager::getFilenameName(const QString &filename)
{
    return FileManager::getFilenameName(filename);
}

QString ConfigManager::getFilenameParent(const QString &filename)
{
    return FileManager::getFilenameParent(filename);
}

ConfigManager::ConfigManager(QObject *parent): QObject(parent), autosaveTimer(this)
{
    loadConfig();
    connect(&autosaveTimer, &QTimer::timeout, this, QOverload<>::of(&ConfigManager::autosaveElapsed));
}
