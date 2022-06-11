#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFile>

class FileManager
{
public:
    FileManager();

    static QString openTextFile(const QString &filename);
    static QString openTextFileOrCreate(const QString &filename, const QString &defaultValue = "");
    static void saveTextFile(const QString &filename, const QString &content);

    static bool fileExists(const QString &filename);

    static void checkAndCreateParentPath(const QString &filename);

    static QString getFilenameStem(const QString &filename);

private:
    static QString openTextFile(QFile &file);
    static void saveTextFile(QFile &file, const QString &content);
};

#endif // FILEMANAGER_H
