#include "qmlnegotiator.h"
#include <QJsonObject>
QmlNegotiator::QmlNegotiator(QObject *parent) :
    QObject(parent)
{
    _stream = new QJsonObject;
}

void QmlNegotiator::sendToStream(QString column, QString value){
    _stream->insert(column, value);
}

QString QmlNegotiator::getFromStream(QString column){
    return _stream->value(column).toString();
}

void QmlNegotiator::clearStream(){
    _stream = new QJsonObject; // is this safe?
}

QJsonObject* QmlNegotiator::getStream(){
    return _stream;
}
