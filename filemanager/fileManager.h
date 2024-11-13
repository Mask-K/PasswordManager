#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

class FileManager
{
public:
    FileManager() = delete;

    static QString getSalt();
    static auto getPasswords();

    static QString filename;
};

#endif // FILEMANAGER_H
