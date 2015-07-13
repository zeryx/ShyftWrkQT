#include "initialize.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QFile>
#include <QList>
#include <QDir>
#include <QSortFilterProxyModel>
#include <src/staffmodel.h>
#include <QQmlApplicationEngine>
Initialize::Initialize(QObject *parent){
    Q_UNUSED(parent);
}

void Initialize::setJsonConfig(QString name, QVariant value){
    if(value.type() == QVariant::String)
        confMap[name] = value.toString();
    else if(value.type() == QVariant::Int)
        confMap[name] = value.toInt();
    else if(value.type() == QVariant::Bool)
        confMap[name] = value.toBool();
}

QString Initialize::getJsonConfig(QString name)const{
    return confMap[name].toString();
}

bool Initialize::updateCfgFile(QJsonObject newObj){
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

bool Initialize::readCfgFile(){
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
            confMap = jsonDoc.object();
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

void Initialize::authorize(){
    QString username = confMap["username"].toString();
    QString password = confMap["password"].toString();
    QString organisation = confMap["organisation"].toString();
    bool check = thisStaff.loginAndPull(username, password, organisation);
    if(check){
        this->updateCfgFile(confMap);
        this->configure();
    }
    else
        emit loggedInAuth(check);
}
void Initialize::configure(){
    thisProxy.setSourceModel(&thisStaff);
    thisProxy.setFilterRole(thisStaff.nameRole);
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
    thisEngine.rootContext()->setContextProperty("masterModel", &thisStaff);
    thisEngine.rootContext()->setContextProperty("searchFilteredModel", &thisProxy);
    thisEngine.rootContext()->setContextProperty("headerList", thisStaff.headerList());
    emit loggedInAuth(true);

    QObject *search= thisQMLBinding->findChild<QObject*>("searchColumnContext");
    QObject::connect(search, SIGNAL(hasText(QString)), &thisProxy, SLOT(setFilterRegExp(QString)));
}

void Initialize::start(){
    if(this->readCfgFile())
        qDebug()<<"no cfg file exists, will make later!";
    thisEngine.addImportPath(QStringLiteral("../ShyftWrkQT/qml"));
    thisEngine.rootContext()->setContextProperty("initialize", this);
    thisEngine.load(QUrl(QStringLiteral("qrc:///qml/ShyftWrk.qml")));
    thisQMLBinding= thisEngine.rootObjects()[0];
    QObject *mainAppStart = thisQMLBinding->findChild<QObject*>("mainWindowContext");

    connect(mainAppStart, SIGNAL(authRequested()),
            this, SLOT(authorize()));
}
