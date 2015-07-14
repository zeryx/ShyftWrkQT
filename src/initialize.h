#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "staffmodel.h"
#include <QSortFilterProxyModel>
#include <QList>
class Initialize : public QObject
{
    Q_OBJECT
public:
    explicit Initialize(QObject *parent = 0);
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

    void start();

    bool updateCfgFile(QJsonObject);

    bool readCfgFile();

    Q_INVOKABLE void setJsonConfig(QString, QVariant);

    Q_INVOKABLE QString getJsonConfig(QString)const;

    Q_INVOKABLE void windowChange();


signals:
   void loggedInAuth(bool);

public slots:

    void authorize();

private:
    QObject* thisQMLBinding;

    QJsonObject confMap;

    QSortFilterProxyModel thisProxy;

    StaffModel thisStaff;

    QList<QObject*> thisTable;

    QQmlApplicationEngine thisEngine;
};

#endif // INITIALIZE_H
