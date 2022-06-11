#ifndef CONFIGFILEMANAGER_H
#define CONFIGFILEMANAGER_H

#include <QFile>
#include "filemanager.h"

class ConfigFileManager
{
public:
    ConfigFileManager();

    const QString openConfig(const QString &defaultConfig) const;
    void saveConfig(const QString &content);

private:
    static QString getConfigDirectoryPath();
    static QString getConfigFilePath();

    static void saveConfig(const QString &content, QFile &file);
};

#endif // CONFIGFILEMANAGER_H
