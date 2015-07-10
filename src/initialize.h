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
    Q_PROPERTY(READ notused NOTIFY loggedInSuccess)
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


signals:
   void loggedInAuth(bool);

public slots:

    void authorize(QString, QString, QString);

private:
    QObject* thisQMLBinding;

    QSortFilterProxyModel* thisProxy;

    StaffModel* thisStaff;

    QList<QObject*> thisTable;

    QQmlApplicationEngine* thisEngine;
};

#endif // INITIALIZE_H
