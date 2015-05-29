#include <QApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QSortFilterProxyModel>
#include "src/employeeModelList.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QString modelName = "baseModel";
    EmployeeModelList vm(modelName);
    QUrl portrait = QUrl(QStringLiteral("file:///home/james/Documents/Code/ShyftWrkQT/assets/sampleportrait.jpg"));
    QString name = "Johnny";
    QString position = "Chef";
    QVariant score = 10.24;

    vm.addPerson(new EmployeeData(portrait, name, position, score));
    vm.addPerson(new EmployeeData(portrait, position, name, score));

    QSortFilterProxyModel* filter = new QSortFilterProxyModel();
    filter->setSourceModel(&vm);
    filter->setFilterRole(EmployeeModelList::nameRole);
    filter->setFilterCaseSensitivity(Qt::CaseInsensitive);

    engine.rootContext()->setContextProperty("baseModel", &vm);

    engine.rootContext()->setContextProperty("searchFilteredModel", filter);

    engine.load(QUrl(QStringLiteral("qrc:///ShyftWrk.qml")));

    QObject *win = engine.rootObjects()[0];
    QObject *search = win->findChild<QObject*>("search");
    QObject::connect(search, SIGNAL(hasText(QString)), filter, SLOT(setFilterRegExp(QString)));
    return app.exec();
}
