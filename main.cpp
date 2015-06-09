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
#include "src/employeeModelMaster.h"
#include "src/employeemodeltable.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    EmployeeModelMaster* employeeList = new EmployeeModelMaster();
    EmployeeModelTable* table = new EmployeeModelTable();

    QObject::connect(employeeList, SIGNAL(rowChanged(int,EmployeeModelMaster*)), table, SLOT(masterDataChanged(int,EmployeeModelMaster*)));

    qDebug()<<"info successfully pulled from database? " << employeeList->pullFromSQL();
    QSortFilterProxyModel* filter = new QSortFilterProxyModel();

    filter->setSourceModel(employeeList);
    filter->setFilterRole(EmployeeModelMaster::nameRole);
    filter->setFilterCaseSensitivity(Qt::CaseInsensitive);

    engine.rootContext()->setContextProperty("baseModel", employeeList);

    engine.rootContext()->setContextProperty("searchFilteredModel", filter);

    engine.load(QUrl(QStringLiteral("qrc:///ShyftWrk.qml")));

    QObject *win = engine.rootObjects()[0];
    QObject *search = win->findChild<QObject*>("search");
    QObject::connect(search, SIGNAL(hasText(QString)), filter, SLOT(setFilterRegExp(QString)));
    return app.exec();
}
