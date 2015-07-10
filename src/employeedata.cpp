#include "employeedata.h"

EmployeeData::EmployeeData()
{
}

EmployeeData::EmployeeData(const QString &name, const QString &uid, const QString &position, const QUrl &portrait){
    this->setPortrait(portrait);
    this->setName(name);
    this->setPositions(position);
    this->setUID(uid);
}

//==-- gets
QUrl EmployeeData::portrait() const{
    return thisPortrait;
}

QString EmployeeData::name() const{
    return thisName;
}

QString EmployeeData::positions() const{
    return thisPositions;
}


QString EmployeeData::uid() const{
    return thisUID;
}

int EmployeeData::getShiftScheduled(QDate &date) const{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i]->shiftScheduled();
        }
    }
    qDebug()<<"the date was out of scope";
    return -1;
}

float EmployeeData::getPerformance(QDate &date) const{
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

QString EmployeeData::getPositionScheduled(QDate &date) const{
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

QMap<QString, float> EmployeeData::getSynergy(QDate &date) const{
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

float EmployeeData::getSynergyWith(QDate &date, QString name) const{
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

QList<SchedulerData*> EmployeeData::getSchedulerDataList() const{
    return thisSchedulerData;
}

SchedulerData* EmployeeData::getScheduleFor(QDate &date) const{
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            return thisSchedulerData[i];
        }
    }
    qDebug()<<"the date was out of scope";
    SchedulerData* null = new SchedulerData;
    null->deleteLater();
    return null;
}

//==-- sets
void EmployeeData::setPortrait(QUrl portrait){
    if(thisPortrait != portrait){
        thisPortrait = portrait;
        emit portraitChanged();
    }
}

void EmployeeData::setName(QString name){
    if(thisName != name){
        thisName = name;
        emit nameChanged();
    }
}

void EmployeeData::setPositions(QString positions){
    if(thisPositions != positions){
        thisPositions = positions;
        emit positionsChanged();
    }
}

void EmployeeData::setUID(QString newUID){
    if(thisUID != newUID){
        thisUID = newUID;
        emit uidChanged();
    }
}

void EmployeeData::setShiftScheduled(int &newShiftScheduled, QDate &date){
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setShiftScheduled(newShiftScheduled);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setPerformance(float &newPerformance, QDate &date){
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setPerformance(newPerformance);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setPositionScheduled(QString &newPositionScheduled, QDate &date){
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setPositionScheduled(newPositionScheduled);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setSynergy(QMap<QString, float> &newSynergy, QDate &date){
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i]->setSynergy(newSynergy);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setSchedulerData(QDate &date, int &shiftScheduled, int &shiftID, QString &positionScheduled, float &performance, QMap<QString, float> &synergy){
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i] = (new SchedulerData(date, shiftScheduled, shiftID, positionScheduled, performance, synergy));
            break;
        }

    }
    thisSchedulerData.append(new SchedulerData(date, shiftScheduled, shiftID, positionScheduled, performance, synergy));
}

