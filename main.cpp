#include <QApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include "src/filtermodel.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QList<FilterModel*> vm;
    QVector<QString> name;
    QVector<QString> color;
    name.append("apple");
    color.append("red");
    name.append("banana");
    color.append("yellow");
    name.append("apricot");
    color.append("orange");
    name.append("duran");
    color.append("brown");
    for(int i=0; i<name.size(); i++){
        vm.append(new FilterModel(name.at(i), color.at(i)));
    }
    FilterModel* filter = new FilterModel(name.at(0),color.at(0));
    engine.rootContext()->setContextProperty("MyModel", filter);
    engine.load(QUrl(QStringLiteral("qrc:///ShyftWrk.qml")));
    QObject *win = engine.rootObjects()[0];
    QObject *search = win->findChild<QObject*>("search");
    QObject::connect(search, SIGNAL(hasText(QString)), &vm, SLOT(searchTextChanged(QString)));
    return app.exec();
}
