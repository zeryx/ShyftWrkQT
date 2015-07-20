#include "abstract_FileManager.h"

abstract_FileManager::abstract_FileManager(QObject *parent) :
    QObject(parent)
{
}

bool abstract_FileManager::WriteToFile(){
return false;
}

bool abstract_FileManager::readFromFile(){
return false;
}
