#include "employeedata.h"

EmployeeData::EmployeeData()
{
}

EmployeeData::EmployeeData(const QUrl &portrait, const QString &name, const QString &position)
{
    this->setPortrait(portrait);
    this->setName(name);
    this->setPositions(position);
}

//==-- gets
QUrl EmployeeData::portrait() const
{
    return thisPortrait;
}

QString EmployeeData::name() const
{
    return thisName;
}

QString EmployeeData::positions() const
{
    return thisPositions;
}

int EmployeeData::getShift(QDate &date) const
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i]->shift();
        }
    }
    qDebug()<<"the date was out of scope";
    return -1;
}

float EmployeeData::getPerformance(QDate &date) const
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i]->performance();
        }
    }
    qDebug()<<"the date was out of scope";
    return -1;
}

QString EmployeeData::getPositionScheduled(QDate &date) const
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i]->positionScheduled();
        }
    }
    qDebug()<<"the date was out of scope";
    QString null;
    return null;
}

QMap<QString, float> EmployeeData::getSynergy(QDate &date) const
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i]->synergy();
        }
    }
    qDebug()<<"the date was out of scope";
    QMap<QString, float> null;
    return null;
}

float EmployeeData::getSynergyWith(QDate &date, QString name) const
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i]->synergyWith(name);
        }
    }
    qDebug()<<"the date was out of scope";
    return -1;
}

QList<SchedulerData*> EmployeeData::getSchedulerDataList() const
{
    return thisSchedulerData;
}

SchedulerData* EmployeeData::getScheduleFor(QDate &date) const
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i];
        }
    }
    qDebug()<<"the date was out of scope";
    SchedulerData* null;
    return null;
}

//==-- sets
void EmployeeData::setPortrait(QUrl portrait)
{
    if(thisPortrait != portrait){
        thisPortrait = portrait;
        emit portraitChanged();
    }
}

void EmployeeData::setName(QString name)
{
    if(thisName != name){
        thisName = name;
        emit nameChanged();
    }
}

void EmployeeData::setPositions(QString positions)
{
    if(thisPositions != positions){
        thisPositions = positions;
        emit positionsChanged();
    }
}

void EmployeeData::setShift(int &newShift, QDate &date)
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setShift(newShift);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setPerformance(float &newPerformance, QDate &date)
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setPerformance(newPerformance);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setPositionScheduled(QString &newPositionScheduled, QDate &date)
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setPositionScheduled(newPositionScheduled);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setSynergy(QMap<QString, float> &newSynergy, QDate &date)
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setSynergy(newSynergy);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setSchedulerData(QDate &date, int &shift, QString &positionScheduled, float &performance, QMap<QString, float> synergy)
{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i] = (new SchedulerData(date, shift, positionScheduled, performance, synergy));
            break;
        }

    }
    thisSchedulerData.append(new SchedulerData(date, shift, positionScheduled, performance, synergy));
}

