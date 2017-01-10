#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>

class FileManager
{
private:

public:
    static QString error;
    static QString filePath;
    static bool saved;
    static bool save(QString filePath);
    static bool load(QString filePath);
};

#endif // FILEMANAGER_H
