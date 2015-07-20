#ifndef EMPLOYEEDATA_H
#define EMPLOYEEDATA_H
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QVariant>
#include "shiftdata.h"
class EmployeeData : public QObject // the staff data object class, contains all info about a staff member, contains
        // a subclass of scheduler data in a QList.
{
    Q_OBJECT
public: //-- gets

    EmployeeData();

    EmployeeData( const QString &first_name, const QString &last_name, const QString &uid, const QString &positions,
                  const QUrl &portrait, QList<ShiftData*> *shiftData =  new QList<ShiftData*>, QObject* parent =0);

    QUrl portrait()const;

    QString firstName()const;

    QString lastName()const;

    QString positions()const;

    QString uid()const;

    QMap<QDate, int> getShiftScheduled()const;

    QMap<QDate, double> getPerformance()const;

    QMap<QDate,QString> getPositionScheduled()const;

    QMap<QDate, QMap<QString, float> > getSynergy()const;

    ShiftData* getScheduleFor(QDate &date)const;

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

    void setShiftData(QList<ShiftData*> &list);

    void setShiftData(QDate& date, int& shiftScheduled, int& shiftID,
                          QString& positionScheduled, double& performance, QMap<QString, float>& Synergy);

public: // menu request methods
    QMap<QString, QVariant> convertSynergyMap(QDate &beginDate, QDate &endDate); // the QVariants contains a QMap<QString, QMap<QString, QVariant>> combo

    QVariant avgPerformance(QDate &beginDate, QDate &endDate);

signals:

    void portraitChanged();

    void firstNameChanged();

    void lastNameChanged();

    void positionsChanged();

    void schedulerDataChanged();

    void uidChanged();


protected:

    QUrl _portrait;
    QString _uID;
    QString _firstName;
    QString _lastName;
    QString _positions;
    QList<ShiftData*> _shiftData;
};

#endif // EMPLOYEEDATA_H
