#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVariant>
#include <QList>
#include "employeedata.h"
#include "schedulerdata.h"
class RestClient : public QAbstractListModel // is inherited by StaffModel
{
    Q_OBJECT
public:

    explicit RestClient(QObject *parent = 0);
    enum restModify{
        restAdd = 1,
        restEdit,
        restRemove
    };
public: //  http request methods

    void requestStaffData();

    void requestLogin(QString username, QString password, QString organization);

    void requestLogout();

    void requestShiftChange(SchedulerData*, restModify = restAdd);

    void requestStaffChange(EmployeeData*, restModify = restAdd);

public:
    void connectionsPostLogin();

signals:


public slots: // standard response handler for signal information

    QVariant GenericResponse(QNetworkReply *reply);

    void addPerson(QNetworkReply *reply);

    void removePerson(QNetworkReply *reply);

    QList<EmployeeData*> getStaff (QNetworkReply *reply);

    void editPerson(QNetworkReply *reply);


private:

    QString *thisOrganization;

    QNetworkAccessManager *thisRestful;

    QNetworkCookieJar *thisSession;

    QObject* thisFrame;
};

#endif // RESTCLIENT_H
