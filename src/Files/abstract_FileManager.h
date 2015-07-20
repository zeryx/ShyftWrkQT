#ifndef ABSTRACT_FILEMANAGER_H
#define ABSTRACT_FILEMANAGER_H

#include <QObject>

class abstract_FileManager : public QObject //abstract base class for all file management utilities
{
    Q_OBJECT
public:
    virtual bool readFromFile();

    virtual bool WriteToFile();

protected:
    explicit abstract_FileManager(QObject *parent = 0);


};

#endif // ABSTRACT_FILEMANAGER_H
