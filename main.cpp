#include <QApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QPluginLoader>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "src/employeeModelList.h"
#include "src/employeemodeltable.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QString sideModel = "sideModel";
    EmployeeModelList* employeeList = new EmployeeModelList(sideModel);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL", "addPersonFromSQL");
    db.setHostName("45.33.71.118");
    db.setPort(3306);
    db.setDatabaseName("ShyftWrk");
    db.setUserName("testuser");
    db.setPassword("test");
    qDebug() << db.open();
    if(!db.isOpen())
    {
        qDebug() << db.lastError();
        return false;
    }
    QString name = "SuzyQ";
    QString position = "server";
    QUrl portrait = QUrl("file:///home/james/Documents/Code/ShyftWrkQT/assets/suzyQ.jpg");
    QVariant score = 5.4;
    EmployeeData * person = new EmployeeData(portrait, name, position, score);
    qDebug()<<"successfully added person to database?" << employeeList->addPersonToSql(db, person);
    qDebug()<<"info successfully pulled from database? " << employeeList->addPersonFromSql(db);
    QSortFilterProxyModel* filter = new QSortFilterProxyModel();

    filter->setSourceModel(employeeList);
    filter->setFilterRole(EmployeeModelList::nameRole);
    filter->setFilterCaseSensitivity(Qt::CaseInsensitive);

    engine.rootContext()->setContextProperty("baseModel", employeeList);

    engine.rootContext()->setContextProperty("searchFilteredModel", filter);

    engine.load(QUrl(QStringLiteral("qrc:///ShyftWrk.qml")));

    QObject *win = engine.rootObjects()[0];
    QObject *search = win->findChild<QObject*>("search");
    QObject::connect(search, SIGNAL(hasText(QString)), filter, SLOT(setFilterRegExp(QString)));

    return app.exec();
}
