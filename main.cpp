#include <QApplication>
#include <QObject>
#include <src/qmlmanager.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   
    QmlManager shyftinit;
    shyftinit.start();

    return app.exec();
}
