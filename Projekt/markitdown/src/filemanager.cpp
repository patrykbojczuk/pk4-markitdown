#include "filemanager.h"
#include <QFile>
#include <filesystem>

FileManager::FileManager() {}

QString FileManager::openTextFile(const QString &filename)
{
    QFile file(filename);
    return FileManager::openTextFile(file);
}

QString FileManager::openTextFileOrCreate(const QString &filename, const QString &defaultValue)
{
    QFile file(filename);
    try {
        return FileManager::openTextFile(file);
    } catch (...) {
        saveTextFile(file, defaultValue);
        file.close();
        return defaultValue;
    }
}

void FileManager::saveTextFile(const QString &filename, const QString &content)
{
    QFile file(filename);
    saveTextFile(file, content);
    file.close();
}

QString FileManager::openTextFile(QFile &file)
{
    if (fileExists(file.fileName())) {
        if (file.open(QIODevice::ReadOnly)) {
            auto configData = QString::fromUtf8(file.readAll());
            file.close();
            return configData;
        }
    }
    file.close();
    throw std::bad_exception();
}

void FileManager::saveTextFile(QFile &file, const QString &content)
{
    checkAndCreateParentPath(file.fileName());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(content.toUtf8());
        return;
    }
    file.close();
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

