#include "configmanager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

ConfigManager &ConfigManager::GetInstance()
{
    static ConfigManager manager;
    return manager;
}

unsigned short ConfigManager::getFontSize() const
{
    return fontSize;
}

void ConfigManager::setFontSize(unsigned short newFontSize)
{
    fontSize = newFontSize;
    save();
}

void ConfigManager::updateFontFamily(const QFont &newFontFamily)
{
    fontFamily = newFontFamily;
    save();
}

const QStringList &ConfigManager::getRecentFiles() const
{
    return recentFiles;
}

void ConfigManager::addRecentFile(const QString &newRecentFile)
{
    recentFiles.push_back(newRecentFile);
    save();
}

void ConfigManager::setAutosave(bool newAutosave)
{
    autosave = newAutosave;
    save();
}

void ConfigManager::save()
{
    QJsonObject obj;
    obj.insert("fontSize", fontSize);
    obj.insert("fontName", fontFamily.family());
    obj.insert("autosave", autosave);
    obj.insert("recentFiles", QJsonValue(QJsonArray::fromStringList(recentFiles)));
    QJsonDocument doc;
    doc.setObject(obj);
    configFileManager.saveConfig(doc.toJson(QJsonDocument::JsonFormat::Compact));
}

bool ConfigManager::isAutosaveEnabled() const
{
    return autosave;
}

const QString defaultConfig = "{\n"
                              "    \"fontSize\":12,\n"
                              "    \"fontName\":\"Poppins\",\n"
                              "    \"autosave\":true,\n"
                              "    \"recentFiles\":[]\n"
                              "}";

void ConfigManager::loadConfig()
{
    QString config = configFileManager.openConfig(defaultConfig);
    auto document = QJsonDocument::fromJson(config.toUtf8());

    fontSize = document["fontSize"].toInteger(12);
    QString fontName = document["fontName"].toString("Poppins");
    QFont font;
    font.setFamily(fontName);
    autosave = document["autosave"].toBool(true);
    if (document["recentFiles"].isArray()) {
        auto recentFilesArray = document["recentFiles"].toArray();
        for (const auto& file: recentFilesArray) {
            if (file.isString() && FileManager::fileExists(file.toString())) {
                recentFiles.push_back(file.toString());
            }
        }
    }
}

ConfigManager::ConfigManager(QObject *parent): QObject(parent)
{
    loadConfig();
}
