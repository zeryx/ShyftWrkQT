#ifndef QMLNEGOTIATOR_H
#define QMLNEGOTIATOR_H

#include <QObject>
#include <QJsonObject>

class QmlNegotiator : public QObject //communicates to and from QML using json data streams.
{
    Q_OBJECT
public:
    explicit QmlNegotiator(QObject *parent = 0);

    void sendToStream(QString column, QString value);

    void clearStream();

    QString getFromStream(QString column);

    QJsonObject* getStream();


private:
    QJsonObject *_stream;

};

#endif // QMLNEGOTIATOR_H
