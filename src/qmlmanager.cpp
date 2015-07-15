#include "qmlmanager.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QFile>
#include <QList>
#include <QDir>
#include <QSortFilterProxyModel>
#include <src/staffmodel.h>
#include <QQmlApplicationEngine>
QmlManager::QmlManager(QObject *parent){
    Q_UNUSED(parent);
}

void QmlManager::setJsonConfig(QString name, QVariant value){ // replace this
    if(value.type() == QVariant::String)
        thisConf[name] = value.toString();
    else if(value.type() == QVariant::Int)
        thisConf[name] = value.toInt();
    else if(value.type() == QVariant::Bool)
        thisConf[name] = value.toBool();
}

QString QmlManager::getJsonConfig(QString name)const{ //replace this
        return thisConf[name].toString();
}

bool QmlManager::updateCfgFile(QJsonObject newObj){ //move this out of here, it ain't qml related
    QDir path = QDir::homePath();
    QFile cfgHelper;
    qDebug()<<path.mkpath("ShyftWrk");
    path.cd("ShyftWrk");
    cfgHelper.setFileName(path.absoluteFilePath("shyft.cnf"));
    if(cfgHelper.open(QFile::WriteOnly)){
        QJsonDocument update(newObj);
        cfgHelper.write(update.toJson());
        cfgHelper.close();
        return 0;
    }
    if(!cfgHelper.open(QFile::Append)){ // if you can't append, you need write permissions
        qDebug()<<"can't make file";
        return 1;
    }
    QJsonDocument update(newObj);
    cfgHelper.write(update.toJson());
    cfgHelper.close();
    return 0;
}

bool QmlManager::readCfgFile(){ //move this out of here, it ain't qml related
    QString path = QDir::homePath()+"/ShyftWrk/shyft.cnf";
    QFile cfgHelper(path);
    if(cfgHelper.exists()){
        cfgHelper.open(QFile::ReadOnly);
        QJsonDocument jsonDoc;
        QJsonParseError *jErr = new QJsonParseError;
        jsonDoc = QJsonDocument::fromJson(cfgHelper.readAll(),jErr);
        cfgHelper.close();
        if(jErr->error == QJsonParseError::NoError)
        {
            thisConf = jsonDoc.object();
            return 0;
        }
        else{
            qDebug()<<jErr->errorString();
            return 1;
        }
    }
    else
        return 1; // if the file can't be opened, return failed

}

void QmlManager::authorize(){
    QString username = thisConf["username"].toString();
    QString password = thisConf["password"].toString();
    QString organisation = thisConf["organisation"].toString();
    bool check = thisStaff.loginAndPull(username, password, organisation);
    if(check){
        this->updateCfgFile(thisConf);
        this->configure();
        emit loginAuth(check);
    }
    else
        emit loginAuth(check);
}
void QmlManager::configure(){ // the program is now athorized to continue as it's recieved json data from server on org
    thisProxy.setSourceModel(&thisStaff);
    thisProxy.setFilterRole(thisStaff.firstNameRole | thisStaff.lastNameRole);
    thisProxy.setFilterCaseSensitivity(Qt::CaseInsensitive);
    thisProxy.setDynamicSortFilter(true);

    for(int i=0; i<thisStaff.headerSize(); i++)
    {
        QSortFilterProxyModel* newColumn = new QSortFilterProxyModel(this);
        //        pattern.setPattern(thisStaff->headerData(i).toString());
        newColumn->setSourceModel(&thisStaff);
        newColumn->setFilterRole(thisStaff.positionRole);
        newColumn->setFilterCaseSensitivity(Qt::CaseInsensitive);
        newColumn->setDynamicSortFilter(true);
        newColumn->setFilterRegExp(thisStaff.headerData(i).toString());
        thisTable.append(newColumn);
    }
    thisEngine.rootContext()->setContextProperty("tableModel", QVariant::fromValue(thisTable));
    thisEngine.rootContext()->setContextProperty("headerList", thisStaff.headerList());

    thisEngine.rootContext()->setContextProperty("masterModel", &thisStaff);
    thisEngine.rootContext()->setContextProperty("searchModel", &thisProxy);
}


void QmlManager::start(){
    if(this->readCfgFile())
        qDebug()<<"no cfg file exists, will make later!";
    thisEngine.addImportPath(QStringLiteral("../ShyftWrkQT/qml"));
    thisEngine.rootContext()->setContextProperty("QmlManager", this);
    thisEngine.load(QUrl(QStringLiteral("qrc:///qml/ShyftWrk.qml")));
    thisQMLBinding= thisEngine.rootObjects()[0];
    QObject *mainAppStart = thisQMLBinding->findChild<QObject*>("mainWindowContext");

    connect(mainAppStart, SIGNAL(authRequested()),
            this, SLOT(authorize()));
}

void QmlManager::windowChange(){ // every time one of the windows change, run this stuff
    QObject* search= thisQMLBinding->findChild<QObject*>("searchColumnContext");
    QObject::connect(search, SIGNAL(hasText(QString)),&thisProxy, SLOT(setFilterRegExp(QString)));
}

//void QmlManager::dataNeedsRefresh(){
//    thisTable.clear();
//    this->configure();
//    for(int i=0; i<thisStaff.headerSize(); i++)
//    {
//        QSortFilterProxyModel* newColumn = new QSortFilterProxyModel(this);
//        //        pattern.setPattern(thisStaff->headerData(i).toString());
//        newColumn->setSourceModel(&thisStaff);
//        newColumn->setFilterRole(thisStaff.positionRole);
//        newColumn->setFilterCaseSensitivity(Qt::CaseInsensitive);
//        newColumn->setDynamicSortFilter(true);
//        newColumn->setFilterRegExp(thisStaff.headerData(i).toString());
//        thisTable.append(newColumn);
//    }
//    thisEngine.rootContext()->setContextProperty("tableModel", QVariant::fromValue(thisTable));
//    thisEngine.rootContext()->setContextProperty("headerList", thisStaff.headerList());
//}

