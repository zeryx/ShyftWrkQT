#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H
#include "abstract_FileManager.h"
class ConfigurationManager : public abstract_FileManager
{
    Q_OBJECT
public:
    explicit ConfigurationManager(QObject *parent = 0);

    bool readFromFile(QJsonObject*, QString filename);

    bool WriteToFile(QJsonObject*, QString filename);
signals:

private:
};

#endif // CONFIGURATIONMANAGER_H
