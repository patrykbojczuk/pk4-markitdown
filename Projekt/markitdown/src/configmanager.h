#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QtQml/qqml.h>
#include "QtGui/qfont.h"
#include "configfilemanager.h"

class ConfigManager : public QObject
{
    Q_OBJECT

public:
    static ConfigManager &GetInstance();

    unsigned short getFontSize() const;
    QFont &getFontFamily() const;
    const QStringList &getRecentFiles() const;
    bool isAutosaveEnabled() const;

    void setFontSize(unsigned short newFontSize);
    void updateFontFamily(const QFont &newFontFamily);
    void addRecentFile(const QString &newRecentFile);
    void setAutosave(bool newAutosave);

private:
    QFont fontFamily;
    unsigned short fontSize;
    QStringList recentFiles;
    bool autosave;

    ConfigFileManager configFileManager;
    void save();

    ConfigManager(QObject *parent = nullptr);
    void loadConfig();
};

#endif // CONFIGMANAGER_H
