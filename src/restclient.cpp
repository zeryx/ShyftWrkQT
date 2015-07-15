#include "restclient.h"

#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QJsonParseError>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

RestClient::RestClient(QObject *parent) :
    QAbstractListModel(parent){
    thisSession = new QNetworkCookieJar; // this could be moved to the members declaration
}

bool RestClient::requestLogin(QString &username, QString &password, QString &organisation){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));

    thisRestful = new QNetworkAccessManager(this);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    thisRestful->setCookieJar(thisSession);
    thisOrganisation = organisation;
    baseUrl = "http://127.0.0.1:5000/"+thisOrganisation.toUtf8();

    QNetworkRequest request(QUrl(baseUrl+"/accounts/login"));
    QUrlQuery params;
    params.addQueryItem("username", username);
    params.addQueryItem("password", password);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *reply = thisRestful->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply); // set all QNAM's to destroy when reply is destroyed
    pause.exec();
    //functions after the eventloop wait
    if(thisDataStream.value("queryCode").toString() == "success"){
        thisDataStream.remove(QString("queryCode"));
        return 1;
    }
    else{
        return 0;
    }
}

void RestClient::logout(){

    thisSession = new QNetworkCookieJar; // make a new cookie jar, destroying all previously held cookies
}

QJsonObject RestClient::requestDataRefresh(){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));

    thisRestful = new QNetworkAccessManager(this);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    thisRestful->setCookieJar(thisSession);
    QNetworkRequest request(QUrl(baseUrl+"/data/pull"));
    QNetworkReply *reply = thisRestful->get(request);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);
    pause.exec();
    //after data is recieved to thisDataStream
    if(thisDataStream.value("queryCode").toString() == "success")
        return thisDataStream;
    else{
        qDebug()<<thisDataStream.value("reason").toString();
        return QJsonObject();
    }
}

bool RestClient::requestShiftChange(SchedulerData* newSchedulerData, QString UID , restModify enumerator){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));

    thisRestful = new QNetworkAccessManager(this);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    thisRestful->setCookieJar(thisSession);
    QNetworkRequest request;
    QUrlQuery params;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    switch (enumerator) {
    case restAdd:
        request.setUrl(QUrl(baseUrl + "/data/shift=new"));
        params.addQueryItem("shift scheduled", QString(newSchedulerData->shiftScheduled()));
        params.addQueryItem("position scheduled", newSchedulerData->positionScheduled());
        params.addQueryItem("date", newSchedulerData->date().toString(Qt::SystemLocaleShortDate));
        params.addQueryItem("uid", UID);
        break;
    case restEdit:
        request.setUrl(QUrl(baseUrl + "/data/shift=edit"));
        params.addQueryItem("shift scheduled", QString(newSchedulerData->shiftScheduled()));
        params.addQueryItem("position scheduled", newSchedulerData->positionScheduled());
        params.addQueryItem("date", newSchedulerData->date().toString(Qt::SystemLocaleShortDate));
        params.addQueryItem("uid", UID);
        params.addQueryItem("shift id", QString(newSchedulerData->shiftID()));
        break;
    case restRemove:
        request.setUrl(QUrl(baseUrl + "/data/shift=delete"));
        params.addQueryItem("shift id", QString(newSchedulerData->shiftID()));
        break;
    }
    QNetworkReply *reply = thisRestful->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);
    pause.exec();

    if(thisDataStream.value("queryCode").toString() == "success")
        return true;
    else{
        qDebug()<<thisDataStream.value("reason").toString();
        return false;
    }
}


bool RestClient::requestStaffChange(EmployeeData * newEmployeeData, restModify enumerator){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));
    thisRestful = new QNetworkAccessManager(this);
    thisRestful->setCookieJar(thisSession);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    QNetworkRequest request;
    QUrlQuery params;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    switch (enumerator) {
    case restAdd: //if this person isn't aleady in the database, an empty string is passed for "UID"
        request.setUrl(QUrl(baseUrl + "/data/staff=new"));
        params.addQueryItem("first_name", newEmployeeData->firstName());
        params.addQueryItem("last_name", newEmployeeData->lastName());
        params.addQueryItem("uid", newEmployeeData->uid());
        params.addQueryItem("portrait", newEmployeeData->portrait().toString());
        break;
    case restEdit:
        request.setUrl(QUrl(baseUrl + "/data/staff=edit"));
        params.addQueryItem("first_name", newEmployeeData->firstName());
        params.addQueryItem("last_name", newEmployeeData->lastName());
        if(newEmployeeData->uid()!="")
            params.addQueryItem("uid", newEmployeeData->uid());
        params.addQueryItem("portrait", newEmployeeData->portrait().toString());
        break;
    case restRemove: // doesn't actually delete the person, just removes this organisation from this organisation
        request.setUrl(QUrl(baseUrl + "/data/staff=delete"));
        params.addQueryItem("uid", newEmployeeData->uid());
        break;
    }
    QNetworkReply *reply = thisRestful->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);
    pause.exec();
    if(thisDataStream.value("queryCode").toString() == "success")
        return true;
    else{
        qDebug()<<thisDataStream.value("reason").toString();
        return false;
    }
}
void RestClient::genericResponse(QNetworkReply *reply){
    QJsonDocument tmp;
    QJsonParseError jError;
    QByteArray data = reply->readAll();
    qDebug()<<data;
    tmp = QJsonDocument::fromJson(data, &jError);
    if(jError.error != QJsonParseError::NoError){
        qDebug()<<jError.errorString();
        emit responseCompleted();
    }
    else{
        thisDataStream = tmp.object();
        emit responseCompleted();
    }
}
void RestClient::errorResponse(QNetworkReply::NetworkError err){
    if(err==QNetworkReply::ConnectionRefusedError)
        thisDataStream["reason"] = "server is offline";
    else if(err==QNetworkReply::ContentNotFoundError)
        thisDataStream["reason"] = "content not found";
    else if(err==QNetworkReply::RemoteHostClosedError)
        thisDataStream["reason"] = "socket closed by server.";
    else if(err==QNetworkReply::HostNotFoundError)
        thisDataStream["reason"] = "invalid hostname.";
    else if(err==QNetworkReply::TimeoutError)
        thisDataStream["reason"] = "connection timed out.";
    else if(err==QNetworkReply::OperationCanceledError)
        thisDataStream["reason"] = "operation aborted before completion.";
    else if(err==QNetworkReply::ContentAccessDenied)
        thisDataStream["reason"] = "access denied, http 401 error.";
    else if(err==QNetworkReply::ContentOperationNotPermittedError)
        thisDataStream["reason"] = "invalid interaction with service.";
    else if(err==QNetworkReply::ProtocolUnknownError)
        thisDataStream["reason"] = "service does not understand protocol used.";
    else if(err==QNetworkReply::UnknownNetworkError)
        thisDataStream["reason"] = "unknown network error detected.";
    emit responseCompleted();
}
