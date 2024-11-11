#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

class FileManager
{
public:
    FileManager() = delete;

    static void createFile(const QString& fileName);
    static bool checkIfExists(const QString& fileName);
    static QString getSalt(const QString& fileName);

    static QString filename;
};

#endif // FILEMANAGER_H
