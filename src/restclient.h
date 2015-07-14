#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
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
    QJsonObject requestDataRefresh();

    bool requestLogin(QString& username, QString& password, QString& organization);

    void logout();

    bool requestShiftChange(SchedulerData*,QString UID, restModify = restAdd);

    bool requestStaffChange(EmployeeData*, restModify = restAdd);

signals:
    void responseCompleted();


private slots: // standard response handler for signal information
    void genericResponse(QNetworkReply *reply);

    void errorResponse(QNetworkReply::NetworkError);


private:

    QJsonObject thisDataStream;

    QString thisOrganisation;

    QByteArray baseUrl;

    QNetworkAccessManager *thisRestful;

    QNetworkCookieJar *thisSession;


};

#endif // RESTCLIENT_H
