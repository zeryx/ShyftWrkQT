#include "employeedata.h"

EmployeeData::EmployeeData()
{
}

EmployeeData::EmployeeData(const QString &name, const QString &uid,
                           const QString &position, const QUrl &portrait, const QList<SchedulerData*> &schedulerData,
                           QObject *parent):
QObject(parent){
    this->setPortrait(portrait);
    this->setName(name);
    this->setPositions(position);
    this->setUID(uid);
    this->setSchedulerData(schedulerData);
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

QMap<QDate, int> EmployeeData::getShiftScheduled() const{
    QMap<QDate, int> map;
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        map[thisSchedulerData[i]->date()] = thisSchedulerData[i]->shiftScheduled();
    }
    return map;
}

QMap<QDate, double> EmployeeData::getPerformance() const{
    QMap<QDate, double> map;
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        map[thisSchedulerData[i]->date()] = thisSchedulerData[i]->performance();
    }
    return map;
}

QMap<QDate, QString> EmployeeData::getPositionScheduled() const{
    QMap<QDate, QString> map;
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        map[thisSchedulerData[i]->date()] = thisSchedulerData[i]->positionScheduled();
    }
    return map;
}

QMap<QDate, QMap<QString, float> > EmployeeData::getSynergy() const{
    QMap<QDate, QMap<QString, float> > map;
    for(int i=0; i<thisSchedulerData.size(); i++){
        map[thisSchedulerData[i]->date()] = thisSchedulerData[i]->synergy();
    }
    return map;
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

void EmployeeData::setPerformance(double &newPerformance, QDate &date){
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

void EmployeeData::setSchedulerData(QDate &date, int &shiftScheduled, int &shiftID, QString &positionScheduled, double &performance, QMap<QString, float> &synergy){
    for(int i=0; i<thisSchedulerData.size(); i++)
    {
        if(thisSchedulerData[i]->date() == date)
        {
            thisSchedulerData[i] = (new SchedulerData(date, shiftScheduled, shiftID, positionScheduled, performance, synergy));
            break;
        }

    }
    thisSchedulerData.append(new SchedulerData(date, shiftScheduled, shiftID, positionScheduled, performance, synergy));
    emit schedulerDataChanged();
}

void EmployeeData::setSchedulerData(QList<SchedulerData *> list){
    if(thisSchedulerData != list)
    {
        thisSchedulerData = list;
        emit schedulerDataChanged();
    }
}

