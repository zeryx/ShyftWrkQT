#include "manager.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QJsonObject>
#include <QSortFilterProxyModel>
#include <src/staffmodel.h>
#include <QQmlApplicationEngine>

Manager::Manager(QQmlApplicationEngine *newEngine, QObject *parent){
    Q_UNUSED(parent);
    _engine = newEngine;
    this->getFromConfig();
    _engine->rootContext()->setContextProperty("Manager", this);
    _engine->load(QUrl(QStringLiteral("qrc:///qml/ShyftWrk.qml")));
    _qMLBinding= _engine->rootObjects()[0];
    QObject *mainAppStart = _qMLBinding->findChild<QObject*>("mainWindowContext");
    connect(mainAppStart, SIGNAL(authRequested()), this, SLOT(authorizationRequested()));

}

void Manager::authorizationRequested(){
    QString username = _negotiator.getFromStream("username");
    QString password =_negotiator.getFromStream("password");
    QString organisation = _negotiator.getFromStream("organisation");
    if(_rest.requestLogin(username, password, organisation))
        if(_staffModel.populate(_rest.requestDataRefresh())){
            finishSetup();
            emit genericSignal(true, "login");
        }
    emit genericSignal(false, "login");
}

void Manager::finishSetup(){
    qmlRegisterType<ShyftMenu>("ShyftMenu",1,0, "ShyftMenu");
    _proxyFilterModel.setSourceModel(&_staffModel);
    _proxyFilterModel.setFilterRole(_staffModel.firstNameRole | _staffModel.lastNameRole);
    _proxyFilterModel.setFilterCaseSensitivity(Qt::CaseInsensitive);
    _proxyFilterModel.setDynamicSortFilter(true);
    _engine->rootContext()->setContextProperty("headerList", _staffModel.headerList());
    _engine->rootContext()->setContextProperty("masterModel", &_staffModel);
    _engine->rootContext()->setContextProperty("searchModel", &_proxyFilterModel);
}

void Manager::alterStaff(QJsonObject& alterStream){
    if(alterStream["mode"].toString() == "new"){
        _rest.requestStaffChange(new EmployeeData(
                alterStream["first name"].toString(),
                alterStream["last name"].toString(),
                alterStream["uid"].toString(),
                alterStream["positions"].toString(),
                alterStream["portrait"].toString()), _rest.restAdd);
    }
    else if(alterStream["mode"].toString() == "edit"){
        _rest.requestStaffChange(new EmployeeData(
                alterStream["first name"].toString(),
                alterStream["last name"].toString(),
                alterStream["uid"].toString(),
                alterStream["positions"].toString(),
                alterStream["portrait"].toString()), _rest.restEdit);
    }
    else if(alterStream["mode"] == _rest.restRemove){
        EmployeeData tmp;
        tmp.setUID(alterStream["uid"].toString());
        _rest.requestStaffChange(&tmp, _rest.restRemove);
    }
    bool chk = _staffModel.populate(_rest.requestDataRefresh()); // this works, I feel like I have way too many methods for this god class
    emit genericSignal(chk, "alterStaff");
}

QString Manager::retrieve(QString column){
    return _negotiator.getFromStream(column);
}

void Manager::store(QString column, QString value){
    return _negotiator.sendToStream(column, value);
}

void Manager::getFromConfig(){ //this stores the value in the config file inside of the _negotiator object

    _files.readFromFile(_negotiator.getStream(), "shyft.cnf");
}

void Manager::putInConfig(){
    _files.WriteToFile(_negotiator.getStream(), "shyft.cnf");
}

