#include "configfilemanager.h"
#include <filesystem>
#include <QStandardPaths>

ConfigFileManager::ConfigFileManager() {}

const QString ConfigFileManager::openConfig(const QString &defaultConfig) const
{
    return FileManager::openTextFileOrCreate(ConfigFileManager::getConfigFilePath(), defaultConfig);
}

void ConfigFileManager::saveConfig(const QString &content)
{
    FileManager::saveTextFile(ConfigFileManager::getConfigFilePath(), content);
}

QString ConfigFileManager::getConfigDirectoryPath()
{
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);
    return locations[0];
}

QString ConfigFileManager::getConfigFilePath()
{
    return ConfigFileManager::getConfigDirectoryPath() + "/config.json";
}
