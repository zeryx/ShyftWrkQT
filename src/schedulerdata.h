#ifndef SCHEDULERDATA_H
#define SCHEDULERDATA_H

#include <QObject>
#include <QMap>
#include <QDate>
class SchedulerData : public QObject
{
    Q_OBJECT
public:
    explicit SchedulerData(QObject *parent = 0);

    explicit SchedulerData(QDate &newDate, int& newshift, QString& newPositionScheduled, float& newPerformance, QMap<QString, float> newSynergy, QObject *parent=0);

public: // gets

    int shift()const;

    float performance()const;

    QDate date() const;

    QString positionScheduled()const;

    QMap<QString, float> synergy()const;

    float synergyWith(QString& person)const;

    float synergyWith(int& index)const;

public: // sets

    void setShift(int& newShift);

    void setPerformance(float& newPerformance);

    void setDate(QDate& newDate);

    void setPositionScheduled(QString& newPositionScheduled);

    void setSynergy(QMap<QString, float>& newSynergy);

signals:

    void shiftChanged();

    void positionScheduledChanged();

    void performanceChanged();

    void synergyChanged();

    void dateChanged();

protected:

    int thisShift;
    float thisPerformance;
    QDate thisDate;
    QString thisPositionScheduled;
    QMap<QString, float> thisSynergy;
};

#endif // SCHEDULERDATA_H
