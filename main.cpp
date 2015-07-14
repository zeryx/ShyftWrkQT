#include <QApplication>
#include <QObject>
#include <src/initialize.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   
    Initialize shyftinit;
    shyftinit.start();

    return app.exec();
}
