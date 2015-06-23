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

    engine.addImportPath(QStringLiteral("../ShyftWrkQT/qml"));

    EmployeeModelMaster* masterModel = new EmployeeModelMaster();
    QSortFilterProxyModel *searchFilteredModel = new QSortFilterProxyModel();
    searchFilteredModel->setSourceModel(masterModel);
    searchFilteredModel->setFilterRole(masterModel->nameRole);
    searchFilteredModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    masterModel->configSQL();
    qDebug()<<"info successfully pulled from database? " << masterModel->pullFromSQL();

    QList<QObject*> tableFilteredModel;
    for(int i=0; i<masterModel->headerSize(); i++)
    {
        QSortFilterProxyModel* newColumn = new QSortFilterProxyModel();
        newColumn->setSourceModel(masterModel);
        newColumn->setFilterRole(masterModel->positionRole);
        newColumn->setFilterCaseSensitivity(Qt::CaseInsensitive);
        newColumn->setDynamicSortFilter(true);
        newColumn->setFilterRegExp("^"+masterModel->headerData(i).toString());
        tableFilteredModel.append(newColumn);
    }
    engine.rootContext()->setContextProperty(QStringLiteral("tableModel"), QVariant::fromValue(tableFilteredModel));
    engine.rootContext()->setContextProperty(QStringLiteral("masterModel"), masterModel);
    engine.rootContext()->setContextProperty(QStringLiteral("searchFilteredModel"), searchFilteredModel);
    engine.rootContext()->setContextProperty(QStringLiteral("headerList"), masterModel->headerList());
    engine.load(QUrl(QStringLiteral("qrc:///qml/ShyftWrk.qml")));

    QObject *win = engine.rootObjects()[0];
    masterModel->m_win = win;
    masterModel->m_proxy = searchFilteredModel;
    QObject *mainAppStart = win->findChild<QObject*>("mainWindowContext");
    QObject::connect(mainAppStart, SIGNAL(mainAppStarted()), masterModel, SLOT(connectionsPostLogin()));

    return app.exec();
}
