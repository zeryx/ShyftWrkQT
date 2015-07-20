#include "rest.h"


#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QMessageBox>

Rest::Rest(QObject *parent) :
    QObject(parent){
}

bool Rest::checkQueryCode(){ // effcient check to see if the request was acceptable from the service side
    if(_responseStream->take("queryCode").toString() == "success"){
        return 1;
    }
    else{
        return 0;
    }
}

void Rest::genericResponse(QNetworkReply *reply){ // all responses from the server are in json format, therefore this can handle all requests
    QJsonDocument tmp;
    QJsonParseError jError;
    QByteArray data = reply->readAll();
    tmp = QJsonDocument::fromJson(data, &jError);
    if(jError.error != QJsonParseError::NoError){
        QMessageBox errorMessage;
        errorMessage.setText(jError.errorString());
        errorMessage.exec();
        emit responseCompleted();
    }
    else{
        _responseStream = new QJsonObject(tmp.object());
        emit responseCompleted();
    }
}
void Rest::errorResponse(QNetworkReply::NetworkError err){
    _responseStream = new QJsonObject;
    _responseStream->insert("queryCode","failed");
    if(err==QNetworkReply::ConnectionRefusedError)
        _responseStream->insert("reason","server is offline");
    else if(err==QNetworkReply::ContentNotFoundError)
        _responseStream->insert("reason","content not found");
    else if(err==QNetworkReply::RemoteHostClosedError)
        _responseStream->insert("reason","socket closed by server.");
    else if(err==QNetworkReply::HostNotFoundError)
        _responseStream->insert("reason","invalid hostname.");
    else if(err==QNetworkReply::TimeoutError)
        _responseStream->insert("reason","connection timed out.");
    else if(err==QNetworkReply::OperationCanceledError)
        _responseStream->insert("reason","operation aborted before completion.");
    else if(err==QNetworkReply::ContentAccessDenied)
        _responseStream->insert("reason","access denied, http 401 error.");
    else if(err==QNetworkReply::ContentOperationNotPermittedError)
        _responseStream->insert("reason","invalid interaction with service.");
    else if(err==QNetworkReply::ProtocolUnknownError)
        _responseStream->insert("reason","service does not understand protocol used.");
    else if(err==QNetworkReply::UnknownNetworkError)
        _responseStream->insert("reason","unknown network error detected.");
    QMessageBox errorMessage;
    errorMessage.setText(_responseStream->value("reason").toString());
    errorMessage.exec();
    emit responseCompleted();
}
