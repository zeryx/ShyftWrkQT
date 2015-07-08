#include "restclient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

RestClient::RestClient(QObject *parent) :
    QObject(parent){
    thisSession = new QNetworkCookieJar;
}

void RestClient::requestLogin(QString &username, QString &password, QString &organization){
    thisRestful = new QNetworkAccessManager(this);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginResponse(QNetworkReply*));
    thisRestful->setCookieJar(thisSession);
    thisOrganization = organization;

    QNetworkRequest request(QUrl("www.shyftwrk.com:5000"+thisOrganization+"/accounts/login"));
    QUrlQuery params;
    params.addQueryItem("username", username);
    params.addQueryItem("password", password);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *reply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);
}

void RestClient::requestLogout(){
//    thisRestful = new QNetworkAccessManager(this);
//    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(GenericResponse(QNetworkReply*)));
//    thisRestful->setCookieJar(thisSession);

//    QNetworkRequest request(QUrl("http://www.shyftwrk.com:5000"+thisOrganization+"/accounts/logoff"));
//    QNetworkReply *reply = thisRestful->post(request);
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
// don't need any of the above, this one line below will do the exact same thing.
    thisSession = new QNetworkCookieJar;
}
void RestClient::requestDataPull(){
    thisRestful = new QNetworkAccessManager(this);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(pullResponse(QNetworkReply*)));
    thisRestful->setCookieJar(thisSession);

    thisRestful->setParent(reply);
}

void RestClient::requestShiftChange(SchedulerData* newSchedulerData, QString* UID , restModify enumerator){
    thisRestful = new QNetworkAccessManager(this);
    connect(thisRestful, SIGNAL(finished(QNetworkReply*)), this, SLOT(genericResponse(QNetworkReply*)));
    thisRestful->setCookieJar(thisSession);
    QNetworkRequest request;
    QUrlQuery params;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    switch (enumerator) {
    case restAdd:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/shift=new"));
        params.addQueryItem("shift scheduled", newSchedulerData->shift());
        params.addQueryItem("position scheduled", newSchedulerData->positionScheduled());
        params.addQueryItem("date", newSchedulerData->date());
        params.addQueryItem("uid", UID);
        break;
    case restEdit:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/shift=edit"));
        params.addQueryItem("shift scheduled", newSchedulerData->shift());
        params.addQueryItem("position scheduled", newSchedulerData->positionScheduled());
        params.addQueryItem("date", newSchedulerData->date());
        params.addQueryItem("uid", UID);
        params.addQueryItem("shift id", newSchedulerData->shiftID());
        break;
    case restRemove:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/shift=delete"));   //not implemented yet
        params.addQueryItem("shift id", newSchedulerData->shiftID());
        break;
    }
    QNetworkReply *reply = thisRestful->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);
}


void RestClient::requestStaffChange(EmployeeData * newEmployeeData, restModify enumerator){
    thisRestful = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrlQuery params;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    switch (enumerator) {
    case restAdd: //if this person isn't aleady in the database, an empty string is passed for "UID"
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/staff=new"));
        params.addQueryItem("name", newEmployeeData->name());
        params.addQueryItem("UID", newEmployeeData->uid());
        params.addQueryItem("positions", newEmployeeData->positions());
        params.addQueryItem("portrait", newEmployeeData->portrait());
        break;
    case restEdit:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/staff=edit"));
        params.addQueryItem("name", newEmployeeData->name());
        params.addQueryItem("UID", newEmployeeData->uid());
        params.addQueryItem("positions", newEmployeeData->positions());
        params.addQueryItem("portrait", newEmployeeData->portrait());
        break;
    case restRemove: // doesn't actually delete the person, just removes this organisation from it's organisations column
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/staff=delete"));
        params.addQueryItem("UID", newEmployeeData->uid());
        break;
    }
    QNetworkReply *reply = thisRestful->post(request, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorResponse(QNetworkReply::NetworkError)));
    thisRestful->setParent(reply);
}

void RestClient::connectionsPostLogin(){
    QObject *search = m_win->findChild<QObject*>("search");
    QObject::connect(search, SIGNAL(hasText(QString)), m_proxy, SLOT(setFilterRegExp(QString)));
}

