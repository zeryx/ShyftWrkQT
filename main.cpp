#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <src/shyftwrkwin.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    EmployeeModelMaster* masterModel = new EmployeeModelMaster();

    QSortFilterProxyModel *masterfilter = new QSortFilterProxyModel();

    masterfilter->setSourceModel(masterModel);
    masterfilter->setFilterRole(masterModel->nameRole);
    masterfilter->setFilterCaseSensitivity(Qt::CaseInsensitive);

    EmployeeModelTable* table = new EmployeeModelTable();
    QObject::connect(masterModel, SIGNAL(updateMirrors(int,EmployeeModelMaster*)), table, SLOT(masterDataChanged(int,EmployeeModelMaster*)));
    masterModel->configSQL();
    qDebug()<<"info successfully pulled from database? " << masterModel->pullFromSQL();

    QSortFilterProxyModel *tablefilter = new QSortFilterProxyModel();
/*    tablefilter->setSourceModel(table);
    tablefilter->setFilterRole(table->positionRole);
    tablefilter->setFilterCaseSensitivity(Qt::CaseInsensitive)*/;

    engine.rootContext()->setContextProperty("searchFilteredModel", masterfilter);

    qDebug()<<"passed context property setting for masterFilter";

    engine.rootContext()->setContextProperty("baseTableModel", table);
    engine.rootContext()->setContextProperty("headers", table->headerList());

    qDebug()<<"right before loading shyftwrk.qml";

    engine.load(QUrl(QStringLiteral("qrc:///qml/ShyftWrk.qml")));
    qDebug()<<"engine loaded shyftwrk.qml";

    QObject *win = engine.rootObjects()[0];
    QObject *search = win->findChild<QObject*>("search");

    QObject::connect(search, SIGNAL(hasText(QString)), masterfilter, SLOT(setFilterRegExp(QString)));

    return app.exec();
}
