#include <QApplication>
#include "personneldata.h"
#include <QQmlApplicationEngine>
#include "qimage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = new QQmlContext(engine.rootContext());
    QImage *samplePortrait = new QImage();
    samplePortrait->load("portrait.jpg", NULL);

    QList<QObject*> dataList;
    dataList.append(new personnelData(*samplePortrait, "James Sutton", float(std::rand()/std::rand())));
    dataList.append(new personnelData(*samplePortrait, "James Sutton", float(std::rand()/std::rand())));
    context->setContextProperty("personnelModel", &dataList);
    QQmlComponent component(&engine);
    component.setData("");

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));


    return app.exec();
}
