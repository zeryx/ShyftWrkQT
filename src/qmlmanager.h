#ifndef QMLMANAGER_H
#define QMLMANAGER_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "staffmodel.h"
#include <QSortFilterProxyModel>
#include <QList>
class QmlManager : public QObject // this is essentially a namespace that runs everything at startup and controls everything related to qml
{
    Q_OBJECT
public:
    explicit QmlManager(QObject *parent = 0);
public:
    QSortFilterProxyModel& proxy();

    StaffModel& staff();

    QList<QObject*>& table();

    QQmlApplicationEngine& engine();

    void setProxy(QSortFilterProxyModel*);

    void setStaff(StaffModel*);

    void setTable(QList<QObject*>);

    void setEngine(QQmlApplicationEngine*);

    void configure();

    void start(); // master method, everything else is called from here

    bool updateCfgFile(QJsonObject);

    bool readCfgFile();

    Q_INVOKABLE void setJsonConfig(QString, QVariant);

    Q_INVOKABLE QString getJsonConfig(QString)const;

    Q_INVOKABLE void windowChange();


signals:
   void loginAuth(bool);

public slots:

    void authorize();

private:
    QObject* thisQMLBinding;

    QJsonObject thisConf;

    QSortFilterProxyModel thisProxy;

    StaffModel thisStaff;

    QList<QObject*> thisTable;

    QQmlApplicationEngine thisEngine;
};

#endif // QMLMANAGER_H
