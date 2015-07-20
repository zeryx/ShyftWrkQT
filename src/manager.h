#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QList>
#include <QSortFilterProxyModel>
#include "staffmodel.h"
#include "RESTful/staffrest.h"
#include"Files/configurationmanager.h"
#include "qmlnegotiator.h"
#include "staffmodel.h"
#include "menuconstructor.h"
#include "shyftmenu.h"
class Manager : public QObject // manages QML objects and instantation, also contains a CppManager object.
{
    Q_OBJECT
public:
    explicit Manager(QQmlApplicationEngine *newEngine, QObject *parent = 0);


    void alterStaff(QJsonObject&);

    void finishSetup();

   Q_INVOKABLE QString retrieve(QString column);

   Q_INVOKABLE void store(QString column, QString value);



    void getFromConfig();

    void putInConfig();

signals:
   void genericSignal(bool, QString);

public slots:

    void authorizationRequested();

private: // component objects

    QQmlApplicationEngine *_engine;
    QObject* _qMLBinding;
    StaffREST _rest;
    QmlNegotiator _negotiator;
    StaffModel _staffModel;
    QSortFilterProxyModel _proxyFilterModel;
    ConfigurationManager _files;
};

#endif // MANAGER_H
