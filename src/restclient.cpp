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
    connect(this, SIGNAL(successfulRequest()), &pause, SLOT(quit()));
    connect(this, SIGNAL(errorDetected()), &pause, SLOT(quit())); // if you login or an error occurs, break the event loop

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
        qDebug()<<thisDataStream.value("reason").toString();
        return 0;
    }
}

void RestClient::logout(){

    thisSession = new QNetworkCookieJar; // make a new cookie jar, destroying all previously held cookies
}

QJsonObject RestClient::requestDataRefresh(){
    QEventLoop pause;
    connect(this, SIGNAL(successfulRequest()), &pause, SLOT(quit()));
    connect(this, SIGNAL(errorDetected()), &pause, SLOT(quit()));

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
    case restRemove://not implemented yet on the server
        request.setUrl(QUrl(baseUrl + "/data/shift=delete"));
        params.addQueryItem("shift id", QString(newSchedulerData->shiftID()));
        break;
    }
    QNetworkReply *reply = thisRestful->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);

    if(thisDataStream.value("queryCode").toString() == "success")
        return true;
    else
        return false;
}


bool RestClient::requestStaffChange(EmployeeData * newEmployeeData, restModify enumerator){
    thisRestful = new QNetworkAccessManager(this);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    QNetworkRequest request;
    QUrlQuery params;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    switch (enumerator) {
    case restAdd: //if this person isn't aleady in the database, an empty string is passed for "UID"
        request.setUrl(QUrl(baseUrl + "/data/staff=new"));
        params.addQueryItem("name", newEmployeeData->name());
        params.addQueryItem("UID", newEmployeeData->uid());
        params.addQueryItem("positions", newEmployeeData->positions());
        params.addQueryItem("portrait", newEmployeeData->portrait().toString());
        break;
    case restEdit:
        request.setUrl(QUrl(baseUrl + "/data/staff=edit"));
        params.addQueryItem("name", newEmployeeData->name());
        params.addQueryItem("UID", newEmployeeData->uid());
        params.addQueryItem("positions", newEmployeeData->positions());
        params.addQueryItem("portrait", newEmployeeData->portrait().toString());
        break;
    case restRemove: // doesn't actually delete the person, just removes this organisation from it's organisations column
        request.setUrl(QUrl(baseUrl + "/data/staff=delete"));
        params.addQueryItem("UID", newEmployeeData->uid());
        break;
    }
    QNetworkReply *reply = thisRestful->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);
    if(thisDataStream.value("queryCode").toString() == "success")
        return true;
    else
        return false;
}

void RestClient::genericResponse(QNetworkReply *reply){
    QJsonDocument tmp;
    QJsonParseError *jError = new QJsonParseError;
    tmp = QJsonDocument::fromJson(reply->readAll(), jError);
    if(jError->error != QJsonParseError::NoError){
        qDebug()<<jError->errorString();
        emit errorDetected();
    }
    else{
        thisDataStream = tmp.object();
        emit successfulRequest();
    }
}


void RestClient::errorResponse(QNetworkReply::NetworkError err){
    QVariantMap tmp;
    if(err==QNetworkReply::ConnectionRefusedError)
        tmp["error"] = "connection refused.";
    else if(err==QNetworkReply::ContentNotFoundError)
        tmp["error"] = "content not found";
    else if(err==QNetworkReply::RemoteHostClosedError)
        tmp["error"] = "socket closed by server.";
    else if(err==QNetworkReply::HostNotFoundError)
        tmp["error"] = "invalid hostname.";
    else if(err==QNetworkReply::TimeoutError)
        tmp["error"] = "connection timed out.";
    else if(err==QNetworkReply::OperationCanceledError)
        tmp["error"] = "operation aborted before completion.";
    else if(err==QNetworkReply::ContentAccessDenied)
        tmp["error"] = "access denied, http 401 error.";
    else if(err==QNetworkReply::ContentOperationNotPermittedError)
        tmp["error"] = "invalid interaction with service.";
    else if(err==QNetworkReply::ProtocolUnknownError)
        tmp["error"] = "service does not understand protocol used.";
    else if(err==QNetworkReply::UnknownNetworkError)
        tmp["error"] = "unknown network error detected.";
    qDebug()<<tmp;
    emit errorDetected();
}


