#include "staffrest.h"

#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QJsonParseError>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkCookieJar>
#include <QMessageBox>

StaffREST::StaffREST(QObject *parent) :
    Rest(parent){
    _cookieJar = new QNetworkCookieJar; // this could be moved to the members declaration
}

bool StaffREST::requestLogin(QString &username, QString &password, QString &organisation){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));

    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    _manager->setCookieJar(_cookieJar);
    _organisation = organisation;
    _baseUrl = "http://127.0.0.1:5000/"+_organisation.toUtf8();

    QNetworkRequest request(QUrl(_baseUrl+"/accounts/login"));
    QUrlQuery params;
    params.addQueryItem("username", username);
    params.addQueryItem("password", password);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *reply = _manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    _manager->setParent(reply); // set all QNAM's to destroy when reply is destroyed
    pause.exec();
    //functions after the eventloop wait
    return checkQueryCode();
}

void StaffREST::logout(){

    _cookieJar = new QNetworkCookieJar; // make a new cookie jar, destroying all previously held cookies
}

QJsonObject StaffREST::requestDataRefresh(){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));

    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    _manager->setCookieJar(_cookieJar);
    QNetworkRequest request(QUrl(_baseUrl+"/data/pull"));
    QNetworkReply *reply = _manager->get(request);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    _manager->setParent(reply);
    pause.exec();
    //after data is recieved to _responseStream
    if(checkQueryCode()){
        QJsonObject tmp = *_responseStream;
        return tmp;
    }
    else
        return QJsonObject();
}

bool StaffREST::requestShiftChange(ShiftData* newSchedulerData, QString UID , restModify enumerator){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));

    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    _manager->setCookieJar(_cookieJar);
    QNetworkRequest request;
    QUrlQuery params;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    switch (enumerator) {
    case restAdd:
        request.setUrl(QUrl(_baseUrl + "/data/shift=new"));
        params.addQueryItem("shift scheduled", QString(newSchedulerData->shiftScheduled()));
        params.addQueryItem("position scheduled", newSchedulerData->positionScheduled());
        params.addQueryItem("date", newSchedulerData->date().toString(Qt::SystemLocaleShortDate));
        params.addQueryItem("uid", UID);
        break;
    case restEdit:
        request.setUrl(QUrl(_baseUrl + "/data/shift=edit"));
        params.addQueryItem("shift scheduled", QString(newSchedulerData->shiftScheduled()));
        params.addQueryItem("position scheduled", newSchedulerData->positionScheduled());
        params.addQueryItem("date", newSchedulerData->date().toString(Qt::SystemLocaleShortDate));
        params.addQueryItem("uid", UID);
        params.addQueryItem("shift id", QString(newSchedulerData->shiftID()));
        break;
    case restRemove:
        request.setUrl(QUrl(_baseUrl + "/data/shift=delete"));
        params.addQueryItem("shift id", QString(newSchedulerData->shiftID()));
        break;
    }
    QNetworkReply *reply = _manager->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    _manager->setParent(reply);
    pause.exec();
    return checkQueryCode();
}


bool StaffREST::requestStaffChange(EmployeeData * newEmployeeData, restModify enumerator){
    QEventLoop pause;
    connect(this, SIGNAL(responseCompleted()), &pause, SLOT(quit()));
    _manager = new QNetworkAccessManager(this);
    _manager->setCookieJar(_cookieJar);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    QNetworkRequest request;
    QUrlQuery params;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    switch (enumerator) {
    case restAdd: //if this person isn't aleady in the database, an empty string is passed for "UID"
        request.setUrl(QUrl(_baseUrl + "/data/staff=new"));
        params.addQueryItem("first_name", newEmployeeData->firstName());
        params.addQueryItem("last_name", newEmployeeData->lastName());
        params.addQueryItem("uid", newEmployeeData->uid());
        params.addQueryItem("portrait", newEmployeeData->portrait().toString());
        break;
    case restEdit:
        request.setUrl(QUrl(_baseUrl + "/data/staff=edit"));
        params.addQueryItem("first_name", newEmployeeData->firstName());
        params.addQueryItem("last_name", newEmployeeData->lastName());
        if(newEmployeeData->uid()!="")
            params.addQueryItem("uid", newEmployeeData->uid());
        params.addQueryItem("portrait", newEmployeeData->portrait().toString());
        break;
    case restRemove: // doesn't actually delete the person, just removes this organisation from this organisation
        request.setUrl(QUrl(_baseUrl + "/data/staff=delete"));
        params.addQueryItem("uid", newEmployeeData->uid());
        break;
    }
    QNetworkReply *reply = _manager->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    _manager->setParent(reply);
    pause.exec();
    return checkQueryCode();
}
