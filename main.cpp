#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <src/employeeModelMaster.h>
#include <QSortFilterProxyModel>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    EmployeeModelMaster* masterModel = new EmployeeModelMaster();

    QSortFilterProxyModel *masterFilter = new QSortFilterProxyModel();
    masterFilter->setSourceModel(masterModel);
    masterFilter->setFilterRole(masterModel->nameRole);
    masterFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    masterModel->configSQL();
    qDebug()<<"info successfully pulled from database? " << masterModel->pullFromSQL();

    QList<QObject*> tableFilters;
    for(int i=0; i<masterModel->headerSize(); i++)
    {
        QSortFilterProxyModel* newColumn = new QSortFilterProxyModel();
        newColumn->setSourceModel(masterModel);
        newColumn->setFilterRole(masterModel->positionRole);
        newColumn->setFilterCaseSensitivity(Qt::CaseInsensitive);
        newColumn->setDynamicSortFilter(true);
        newColumn->setFilterRegExp("^"+masterModel->headerData(i).toString());
        tableFilters.append(newColumn);
    }
    engine.rootContext()->setContextProperty(QStringLiteral("tableModel"), QVariant::fromValue(tableFilters));
    engine.rootContext()->setContextProperty(QStringLiteral("masterModel"), masterModel);
    engine.rootContext()->setContextProperty(QStringLiteral("searchFilteredModel"), masterFilter);
    engine.rootContext()->setContextProperty(QStringLiteral("headerList"), masterModel->headerList());


    engine.load(QUrl(QStringLiteral("qrc:///qml/ShyftWrk.qml")));

    QObject *win = engine.rootObjects()[0];
    QObject *search = win->findChild<QObject*>("search");
    QObject *header = win->findChild<QObject*>("headerInput");

    QObject::connect(search, SIGNAL(hasText(QString)), masterFilter, SLOT(setFilterRegExp(QString)));
    QObject::connect(header, SIGNAL(newHeaderInput(QString)), masterModel, SLOT(setHeaderDataSlot(QString)));


    return app.exec();
}
