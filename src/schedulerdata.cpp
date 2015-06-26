#include "schedulerdata.h"

SchedulerData::SchedulerData(QObject *parent)
    :QObject(parent)
{
}

SchedulerData::SchedulerData(QDate &newDate, int& newshift, QString& newPositionScheduled, float& newPerformance, QMap<QString, float> newSynergy, QObject *parent)
    :QObject(parent)
{
    this->setDate(newDate);
    this->setShift(newshift);
    this->setPositionScheduled(newPositionScheduled);
    this->setPerformance(newPerformance);
    this->setSynergy(newSynergy);
}

//-- gets
int SchedulerData::shift() const
{
    return thisShift;
}

float SchedulerData::performance() const
{
    return thisPerformance;
}

QDate SchedulerData::date() const
{
    return thisDate;
}

QString SchedulerData::positionScheduled() const
{
    return thisPositionScheduled;
}

QMap<QString, float> SchedulerData::synergy() const
{
    return thisSynergy;
}

float SchedulerData::synergyWith(QString& person) const
{
    return thisSynergy.value(person);
}

float SchedulerData::synergyWith(int& index) const
{
    QList<float> temp;
    temp = synergy().values();
    return temp.at(index);
}


//-- sets
void SchedulerData::setShift(int& newShift)
{
    if(newShift != thisShift)
    {
        thisShift = newShift;
        emit shiftChanged();
    }
}

void SchedulerData::setPerformance(float& newPerformance)
{
    if(newPerformance != thisPerformance)
    {
        thisPerformance = newPerformance;
        emit performanceChanged();
    }
}

void SchedulerData::setDate(QDate& newDate)
{
    if(newDate != thisDate)
    {
        thisDate = newDate;
        emit dateChanged();
    }
}

void SchedulerData::setPositionScheduled(QString& newPositionScheduled)
{
    if(newPositionScheduled != thisPositionScheduled)
    {
        thisPositionScheduled = newPositionScheduled;
        emit positionScheduledChanged();
    }
}


void SchedulerData::setSynergy(QMap<QString, float>& newSynergy)
{
    if(newSynergy != thisSynergy)
    {
        thisSynergy = newSynergy;
        emit synergyChanged();
    }
}
