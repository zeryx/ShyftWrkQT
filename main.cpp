#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <src/initialize.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Initialize shyftinit;
    shyftinit.start();

    return app.exec();
}
