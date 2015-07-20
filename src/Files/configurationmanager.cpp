#include "configurationmanager.h"
#include <QFile>
#include <QJsonDocument>
#include<QJsonObject>
#include <QString>
#include <QDir>
#include <QMessageBox>
ConfigurationManager::ConfigurationManager(QObject *parent) :
    abstract_FileManager(parent)
{
}

bool ConfigurationManager::WriteToFile(QJsonObject *newObj, QString filename){
    QDir path = QDir::homePath();
    QFile cfgHelper;
    path.cd("ShyftWrk");
    cfgHelper.setFileName(path.absoluteFilePath(filename));
    if(cfgHelper.open(QFile::WriteOnly)){
        QJsonDocument update(*newObj);
        cfgHelper.write(update.toJson());
        cfgHelper.close();
        return true;
    }
    if(!cfgHelper.open(QFile::Append)){ // if you can't append, you need write permissions
        QMessageBox errorMessage;
        errorMessage.setText("cannot create config file, check permissions.");
        errorMessage.exec();
        return false;
    }
    QJsonDocument update(*newObj);
    cfgHelper.write(update.toJson());
    cfgHelper.close();
    return true;
}

bool ConfigurationManager::readFromFile(QJsonObject *stream, QString filename){
QString path = QDir::homePath()+"/ShyftWrk/" + filename;
QFile cfgHelper(path);
if(cfgHelper.exists()){
    cfgHelper.open(QFile::ReadOnly);
    QJsonDocument jsonDoc;
    QJsonParseError *jErr = new QJsonParseError;
    jsonDoc = QJsonDocument::fromJson(cfgHelper.readAll(),jErr);
    cfgHelper.close();
    if(jErr->error == QJsonParseError::NoError)
    {
        *stream = jsonDoc.object();
        return true;
    }
    else{
        QMessageBox errorMessage;
        errorMessage.setText("cannot read from config file: " + jErr->errorString());
        return false;
    }
}
else
    return false; // if the file can't be opened, return failed

}
