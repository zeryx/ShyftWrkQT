#include <QApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <src/manager.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   
    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("../ShyftWrkQT/qml"));
    Manager *management = new Manager(&engine);


    return app.exec();
}
