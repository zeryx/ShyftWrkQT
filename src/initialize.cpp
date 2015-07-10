#include "initialize.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QList>
#include <QSortFilterProxyModel>
#include <src/staffmodel.h>
#include <QQmlApplicationEngine>
Initialize::Initialize(QObject *parent) :
    QObject(parent){
    this->setStaff(new StaffModel);
    this->setProxy(new QSortFilterProxyModel);
    QList<QObject*> tmp;
    this->setTable(tmp);
    this->setEngine(new QQmlApplicationEngine);
}


void Initialize::setStaff(StaffModel *newStaff){
    if(thisStaff != newStaff){
        thisStaff = newStaff;
    }
}

void Initialize::setProxy(QSortFilterProxyModel *newProxy){
    if(thisProxy != newProxy){
        thisProxy = newProxy;
    }
}

void Initialize::setEngine(QQmlApplicationEngine *newEngine){
    if(thisEngine != newEngine){
        thisEngine = newEngine;
    }
}

void Initialize::setTable(QList<QObject *>newTable){
    if(thisTable != newTable){
        thisTable = newTable;
    }
}

void Initialize::authorize(QString username, QString password, QString organisation){

    bool check = thisStaff->loginAndPull(username, password, organisation);
    if(check)
        this->configure();
    else
        emit loggedInAuth(check);
}
void Initialize::configure(){
    thisProxy = new QSortFilterProxyModel(this);
    thisProxy->setSourceModel(thisStaff);
    thisProxy->setFilterRole(thisStaff->nameRole);
    thisProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);

    for(int i=0; i<thisStaff->headerSize(); i++)
    {
        QSortFilterProxyModel* newColumn = new QSortFilterProxyModel();
        //        pattern.setPattern(thisStaff->headerData(i).toString());
        newColumn->setSourceModel(thisStaff);
        newColumn->setFilterRole(thisStaff->positionRole);
        newColumn->setFilterCaseSensitivity(Qt::CaseInsensitive);
        newColumn->setDynamicSortFilter(true);
        newColumn->setFilterRegExp(thisStaff->headerData(i).toString());
        thisTable.append(newColumn);
    }

    thisEngine->rootContext()->setContextProperty("tableModel", QVariant::fromValue(thisTable));
    thisEngine->rootContext()->setContextProperty("masterModel", thisStaff);
    thisEngine->rootContext()->setContextProperty("searchFilteredModel", thisProxy);
    thisEngine->rootContext()->setContextProperty("headerList", thisStaff->headerList());
    emit loggedInAuth(true);

    QObject *search= thisQMLBinding->findChild<QObject*>("searchColumnContext");
    QObject::connect(search, SIGNAL(hasText(QString)), thisProxy, SLOT(setFilterRegExp(QString)));
}

void Initialize::start(){
    thisEngine = new QQmlApplicationEngine(this);
    thisEngine->addImportPath(QStringLiteral("../ShyftWrkQT/qml"));
    thisEngine->rootContext()->setContextProperty("initialize", this);
    thisEngine->load(QUrl(QStringLiteral("qrc:///qml/ShyftWrk.qml")));
    thisQMLBinding= thisEngine->rootObjects()[0];
    QObject *mainAppStart = thisQMLBinding->findChild<QObject*>("mainWindowContext");

    connect(mainAppStart, SIGNAL(authRequested(QString,QString ,QString)),
            this, SLOT(authorize(QString,QString,QString )));
}
