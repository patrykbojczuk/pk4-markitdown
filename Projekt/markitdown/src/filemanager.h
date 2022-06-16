#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFuture>
#include <QString>
#include <QFile>

class FileManager
{
public:
    FileManager();

    static QFuture<QString> openTextFile(const QString &filename);
    static QFuture<QString> openTextFileOrCreate(const QString &filename, const QString &defaultValue = "");
    static void saveTextFile(const QString &filename, QString content);

    static bool fileExists(const QString &filename);

    static void checkAndCreateParentPath(const QString &filename);

    static QString getFilenameStem(const QString &filename);
    static QString getFilenameName(const QString &filename);
    static QString getFilenameParent(const QString &filename);

private:
    static QFuture<QString> openTextFile(QFile *file, bool handleFileOnThrow = true);
    static void saveTextFile(QFile *file, const QString &content);
};

#endif // FILEMANAGER_H
