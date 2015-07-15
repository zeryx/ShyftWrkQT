#ifndef EMPLOYEEDATA_H
#define EMPLOYEEDATA_H
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QVariant>
#include "schedulerdata.h"
class EmployeeData : public QObject // the staff data object class, contains all info about a staff member, contains
        // a subclass of scheduler data in a QList.
{
    Q_OBJECT
public: //-- gets

    EmployeeData();

    EmployeeData( const QString &first_name, const QString &last_name, const QString &uid, const QString &positions,
                  const QUrl &portrait, const QList<SchedulerData*> *schedulerData =  new QList<SchedulerData*>, QObject* parent =0);

    QUrl portrait()const;

    QString firstName()const;

    QString lastName()const;

    QString positions()const;

    QString uid()const;

    QMap<QDate, int> getShiftScheduled()const;

    QMap<QDate, double> getPerformance()const;

    QMap<QDate,QString> getPositionScheduled()const;

    QMap<QDate, QMap<QString, float> > getSynergy()const;

    SchedulerData* getScheduleFor(QDate &date)const;

public: //-- sets

    void setPortrait(QUrl newPortrait);

    void setFirstName(QString newName);

    void setLastName(QString newName);

    void setPositions(QString newPositions);

    void setUID(QString newUID);

    void setShiftScheduled(int& newShiftScheduled, QDate& date);

    void setPerformance(double& newPerformance, QDate& date);

    void setPositionScheduled(QString& newPositionScheduled, QDate& date);

    void setSynergy(QMap<QString, float>& newSynergy, QDate& date);

    void setSchedulerData(QList<SchedulerData*> list);

    void setSchedulerData(QDate& date, int& shiftScheduled, int& shiftID,
                          QString& positionScheduled, double& performance, QMap<QString, float>& Synergy);

signals:

    void portraitChanged();

    void firstNameChanged();

    void lastNameChanged();

    void positionsChanged();

    void schedulerDataChanged();

    void uidChanged();


protected:

    QUrl thisPortrait;
    QString thisUID;
    QString thisFirstName;
    QString thisLastName;
    QString thisPositions;
    QList<SchedulerData*> thisSchedulerData;
};

#endif // EMPLOYEEDATA_H
