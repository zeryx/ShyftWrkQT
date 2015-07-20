#ifndef STAFFREST_H
#define STAFFREST_H
#include "rest.h"
#include "src/modelClassComponents/employeedata.h"
#include "src/modelClassComponents/shiftdata.h"
class StaffREST : public Rest //concrete class of Rest, specialized in staff model management
{
    Q_OBJECT
public:
    enum restModify{
        restAdd = 1,
        restEdit,
        restRemove
    };
public:

    explicit StaffREST(QObject *parent = 0);

    QJsonObject requestDataRefresh();

    bool requestLogin(QString& username, QString& password, QString& organization);

    void logout();

    bool requestShiftChange(ShiftData*, QString UID, restModify = restAdd);

    bool requestStaffChange(EmployeeData*, restModify = restAdd);

private:
    QString _organisation;

    QByteArray _baseUrl;

    QNetworkAccessManager *_manager;

    QNetworkCookieJar *_cookieJar;
};

#endif // STAFFREST_H
