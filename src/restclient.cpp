#include "restclient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>
#include <QUrl>
#include <QDebug>

RestClient::RestClient(QObject *parent) :
    QObject(parent)
{    
}

void RestClient::requestLogin(QString &username, QString &password, QString &organization)
{
    thisRestful = new QNetworkAccessManager(this);
    QNetworkRequest request;
    thisOrganization = organization;
    request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/accounts/login"));
    request.setRawHeader("username", username);
    request.setRawHeader("password", password);
    QNetworkReply *reply = thisRestful->post(request);
    connect(reply, SIGNAL(finished(QNetworkReply*)), this, SLOT(GenericResponse(QNetworkReply*)));
}

void RestClient::requestLogout()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shyftwrk.com:5000"+thisOrganization+"/accounts/logoff"));
    QNetworkReply *reply = thisRestful->post(request);
    connect(reply, SIGNAL(finished(QNetworkReply*)), this, SLOT(GenericResponse(QNetworkReply*));
}

void RestClient::requestShiftChange(SchedulerData* newSchedulerData, QString* UID , restModify enumerator)
{
    thisRestful = new QNetworkAccessManager(this);
    QNetworkRequest request;
    switch (enumerator) {
    case restAdd:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/newshift"));
        request.setRawHeader("shift scheduled", newSchedulerData->shift());
        request.setRawHeader("position scheduled", newSchedulerData->positionScheduled());
        request.setRawHeader("date", newSchedulerData->date());
        request.setRawHeader("uid", UID);
        break;
    case restEdit:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/editshift"));
        request.setRawHeader("shift scheduled", newSchedulerData->shift());
        request.setRawHeader("position scheduled", newSchedulerData->positionScheduled());
        request.setRawHeader("date", newSchedulerData->date());
        request.setRawHeader("uid", UID);
        request.setRawHeader("shift id", newSchedulerData->shiftID());
        break;
    case restRemove:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/shift"));   //not implemented yet
        request.setRawHeader("shift id", newSchedulerData->shiftID());
        break;
    }
    QNetworkReply *reply = thisRestful->post(request);
    connect(reply, SIGNAL(finished(QNetworkReply*)), this, SLOT(shiftChanged(QNetworkReply*));
}


void RestClient::requestStaffChange(EmployeeData * newEmployeeData, restModify enumerator)
{
    thisRestful = new QNetworkAccessManager(this);
    QNetworkRequest request;
    switch (enumerator) {
    case restAdd:
        request.setUrl(QUrl("http://www.shyftwrk.com:5000/"+thisOrganization+"/data/newstaff"));
        request.setRawHeader("name", newEmployeeData->name());
        request.setRawHeader("positions", newEmployeeData->positions());
        request.setRawHeader("portrait", newEmployeeData->portrait());
        break;
    case restEdit:

        break;
    case restRemove:

        break;
    }
}

void RestClient::connectionsPostLogin()
{
    QObject *search = m_win->findChild<QObject*>("search");
    QObject::connect(search, SIGNAL(hasText(QString)), m_proxy, SLOT(setFilterRegExp(QString)));
}
