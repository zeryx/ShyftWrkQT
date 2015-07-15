#ifndef SCHEDULERDATA_H
#define SCHEDULERDATA_H

#include <QObject>
#include <QMap>
#include <QDate>
class SchedulerData : public QObject // main shift object, contains all info that a single shift could contain, is filled with
        // json data from service via rest client
{
    Q_OBJECT
public:
    explicit SchedulerData(QObject *parent = 0);

    explicit SchedulerData(QDate newDate, int newShiftScheduled, int newShiftID, QString newPositionScheduled, double newPerformance, QMap<QString, float> newSynergy, QObject *parent=0);

public: // gets

    int shiftScheduled()const;

    int shiftID()const;

    double performance()const;

    QDate date() const;

    QString positionScheduled()const;

    QMap<QString, float> synergy()const;

    float synergyWith(QString& person)const;

    float synergyWith(int& index)const;

public: // sets

    void setShiftScheduled(int newShiftScheduled);

    void setShiftID(int newShiftID);

    void setPerformance(double newPerformance);

    void setDate(QDate newDate);

    void setPositionScheduled(QString newPositionScheduled);

    void setSynergy(QMap<QString, float> newSynergy);

signals:

    void shiftScheduledChanged();

    void shiftIDChanged();

    void positionScheduledChanged();

    void performanceChanged();

    void synergyChanged();

    void dateChanged();

protected:

    int thisShiftScheduled;
    int thisShiftID;
    double thisPerformance;
    QDate thisDate;
    QString thisPositionScheduled;
    QMap<QString, float> thisSynergy;
};

#endif // SCHEDULERDATA_H
