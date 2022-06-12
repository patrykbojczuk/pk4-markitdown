#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QtQml/qqml.h>
#include <QFont>
#include <QTimer>
#include "configfilemanager.h"

class ConfigManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned short fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(QFont fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontFamilyChanged)
    Q_PROPERTY(QStringList recentFiles READ recentFiles NOTIFY recentFilesChanged)
    Q_PROPERTY(bool autosave READ isAutosaveEnabled WRITE setAutosave NOTIFY autosaveChanged)
    Q_PROPERTY(size_t autosaveTimeout READ autosaveTimeout WRITE setAutosaveTimeout NOTIFY autosaveTimeoutChanged)
public:
    static ConfigManager &GetInstance();

    unsigned short fontSize() const;
    const QFont &fontFamily() const;
    const QStringList &recentFiles() const;
    bool isAutosaveEnabled() const;

    size_t autosaveTimeout() const;

    void setFontSize(unsigned short newFontSize, bool save = true);
    void setFontFamily(const QFont &newFontFamily, bool save = true);
    Q_INVOKABLE
    void addRecentFile(const QString &newRecentFile, bool save = true);
    void setAutosave(bool newAutosave, bool save = true);
    void setAutosaveTimeout(size_t newAutosaveTimeout, bool save = true);

    bool getFinishedLoading() const;

signals:
    void fontSizeChanged();
    void fontFamilyChanged();
    void recentFilesChanged();
    void autosaveChanged();
    void autosaveTimeoutChanged();

private:
    QFont m_fontFamily;
    unsigned short m_fontSize;
    QStringList m_recentFiles;
    bool m_autosave;
    size_t m_autosaveTimeout;
    QTimer autosaveTimer;

    ConfigFileManager configFileManager;
    void saveConfig();

    ConfigManager(QObject *parent = nullptr);
    void loadConfig();

    void autosaveElapsed();

    bool finishedLoading = false;
};

#endif // CONFIGMANAGER_H
