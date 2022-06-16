#include "filemanager.h"
#include <QFile>
#include <filesystem>
#include <QtConcurrent>

FileManager::FileManager() {}

QFuture<QString> FileManager::openTextFile(const QString &filename)
{
    QFile* file = new QFile(filename);
    return FileManager::openTextFile(file);
}

QFuture<QString> FileManager::openTextFileOrCreate(const QString &filename, const QString &defaultValue)
{
    QFile *file = new QFile(filename);

    try{
        return openTextFile(file, false);
    } catch(...){
        saveTextFile(file, defaultValue);
        return QtConcurrent::run([&defaultValue](){
            return defaultValue;
        });
    }
}

void FileManager::saveTextFile(const QString &filename, QString content)
{
    QFile *file = new QFile(filename);
    saveTextFile(file, content);
}

QFuture<QString> FileManager::openTextFile(QFile *file, bool handleFileOnThrow)
{
    if (fileExists(file->fileName())) {
        if (file->open(QIODevice::ReadOnly)) {
            return QtConcurrent::run([file](){
                auto configData = QString::fromUtf8(file->readAll());
                file->close();
                delete file;
                return configData;
            });
        }
    }
    if (handleFileOnThrow){
        file->close();
        delete file;
    }
    throw std::bad_exception();
}

void FileManager::saveTextFile(QFile *file, const QString &content)
{
    checkAndCreateParentPath(file->fileName());
    if (file->open(QIODevice::WriteOnly)) {
        static_cast<void>(QtConcurrent::run([file, &content](){
            file->write(content.toUtf8());
            file->close();
            delete file;
        }));
        return;
    }
    file->close();
    delete file;
    throw std::bad_exception();
}

bool FileManager::fileExists(const QString &filename) {
    return std::filesystem::exists(filename.toStdWString());
}

void FileManager::checkAndCreateParentPath(const QString &filename) {
    auto parentPath = std::filesystem::path(filename.toStdWString()).parent_path();
    if (!std::filesystem::exists(parentPath)) {
        std::filesystem::create_directories(parentPath);
    }
}

QString FileManager::getFilenameStem(const QString &filename)
{
    return QString::fromStdWString(std::filesystem::path(filename.toStdWString()).stem().generic_wstring());
}

QString FileManager::getFilenameName(const QString &filename)
{
    return QString::fromStdWString(std::filesystem::path(filename.toStdWString()).filename().generic_wstring());
}

QString FileManager::getFilenameParent(const QString &filename)
{
    return QString::fromStdWString(std::filesystem::path(filename.toStdWString()).parent_path().generic_wstring());
}

