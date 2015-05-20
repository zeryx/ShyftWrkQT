#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "qimage.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // replace the functions below with actual arrays, they are just for testing
//    std::vector<personnelData> personnelVector(10);
//    QUrl jimmyPortrait = QStringLiteral("qrc:///portrait.jpg");
//    QString jimmyName = "James Sutton";
//    qreal jimmyScore = 4.6;
//    personnelVector[0].setPortrait(jimmyPortrait);
//    personnelVector[0].setName(jimmyName);
//    personnelVector[0].setScore(jimmyScore);


    //    QList<QObject*> dataList;
    //    for(unsigned int perItr=0; perItr < personnelVector.size(); perItr++)
    //    {
    //        dataList.append(QObject(personnelVector[perItr]));
    //   }

    //    engine.rootContext()->setContextProperty("personnelModel", QVariant::fromValue(dataList));
        engine.load(QUrl(QStringLiteral("qrc:///ShyftWrk.qml")));

    return app.exec();
}
