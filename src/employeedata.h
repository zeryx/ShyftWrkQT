#ifndef EMPLOYEEDATA_H
#define EMPLOYEEDATA_H
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QVariant>
#include "schedulerdata.h"
class EmployeeData : public QObject
{
    Q_OBJECT
public: //-- gets

    EmployeeData();

    EmployeeData(const QUrl &portrait, const QString &name, const QString &positions);

    QUrl portrait()const;

    QString name()const;

    QString positions()const;

    QString uid()const;

    int getShiftScheduled(QDate &date)const;

    float getPerformance(QDate &date)const;

    QString getPositionScheduled(QDate &date)const;

    QMap<QString, float> getSynergy(QDate &date)const;

    float getSynergyWith(QDate &date, QString name)const;

    QList<SchedulerData*> getSchedulerDataList()const;

    SchedulerData* getScheduleFor(QDate &date)const;

public: //-- sets

    void setPortrait(QUrl newPortrait);

    void setName(QString newName);

    void setPositions(QString newPositions);

    void setUID(QString newUID);

    void setShiftScheduled(int& newShiftScheduled, QDate& date);

    void setPerformance(float& newPerformance, QDate& date);

    void setPositionScheduled(QString& newPositionScheduled, QDate& date);

    void setSynergy(QMap<QString, float>& newSynergy, QDate& date);

    void setSchedulerData(QList<SchedulerData*> list);

    void setSchedulerData(QDate& date, int& shiftScheduled, QString& positionScheduled, float& performance, QMap<QString, float> Synergy);

signals:

    void portraitChanged();

    void nameChanged();

    void positionsChanged();

    void schedulerDataChanged();

    void uidChanged();


protected:

    QUrl thisPortrait;
    QString thisUID;
    QString thisName;
    QString thisPositions;
    QList<SchedulerData*> thisSchedulerData;
};

#endif // EMPLOYEEDATA_H
