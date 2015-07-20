#include "employeedata.h"

EmployeeData::EmployeeData()
{
}

EmployeeData::EmployeeData(const QString &firstName,const QString &lastName, const QString &uid,
                           const QString &position, const QUrl &portrait,  QList<ShiftData*> *shiftData,
                           QObject *parent):
    QObject(parent){
    this->setPortrait(portrait);
    this->setFirstName(firstName);
    this->setLastName(lastName);
    this->setPositions(position);
    this->setUID(uid);
    this->setShiftData(*shiftData);
}

//==-- gets
QUrl EmployeeData::portrait() const{
    return _portrait;
}

QString EmployeeData::firstName() const{
    return _firstName;
}

QString EmployeeData::lastName() const{
    return _lastName;
}

QString EmployeeData::positions() const{
    return _positions;
}


QString EmployeeData::uid() const{
    return _uID;
}

QMap<QDate, int> EmployeeData::getShiftScheduled() const{
    QMap<QDate, int> map;
    for(int i=0; i<_shiftData.size(); i++)
    {
        map[_shiftData[i]->date()] = _shiftData[i]->shiftScheduled();
    }
    return map;
}

QMap<QDate, double> EmployeeData::getPerformance() const{
    QMap<QDate, double> map;
    for(int i=0; i<_shiftData.size(); i++)
    {
        map[_shiftData[i]->date()] = _shiftData[i]->performance();
    }
    return map;
}

QMap<QDate, QString> EmployeeData::getPositionScheduled() const{
    QMap<QDate, QString> map;
    for(int i=0; i<_shiftData.size(); i++)
    {
        map[_shiftData[i]->date()] = _shiftData[i]->positionScheduled();
    }
    return map;
}

QMap<QDate, QMap<QString, float> > EmployeeData::getSynergy() const{
    QMap<QDate, QMap<QString, float> > map;
    for(int i=0; i<_shiftData.size(); i++){
        map[_shiftData[i]->date()] = _shiftData[i]->synergy();
    }
    return map;
}

ShiftData* EmployeeData::getScheduleFor(QDate &date) const{
    for(int i=0; i<_shiftData.size(); i++)
    {
        if(_shiftData[i]->date() == date)
        {
            return _shiftData[i];
        }
    }
    qDebug()<<"the date was out of scope";
    ShiftData* null = new ShiftData;
    null->deleteLater();
    return null;
}

//==-- sets
void EmployeeData::setPortrait(QUrl portrait){
    if(_portrait != portrait){
        _portrait = portrait;
        emit portraitChanged();
    }
}

void EmployeeData::setFirstName(QString name){
    if(_firstName != name){
        _firstName = name;
        emit firstNameChanged();
    }
}

void EmployeeData::setLastName(QString name){
    if(_lastName != name){
        _lastName = name;
        emit lastNameChanged();
    }
}

void EmployeeData::setPositions(QString positions){
    if(_positions != positions){
        _positions = positions;
        emit positionsChanged();
    }
}

void EmployeeData::setUID(QString newUID){
    if(_uID != newUID){
        _uID = newUID;
        emit uidChanged();
    }
}

void EmployeeData::setShiftScheduled(int &newShiftScheduled, QDate &date){
    for(int i=0; i<_shiftData.size(); i++)
    {
        if(_shiftData[i]->date() == date)
        {
            _shiftData[i]->setShiftScheduled(newShiftScheduled);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setPerformance(double &newPerformance, QDate &date){
    for(int i=0; i<_shiftData.size(); i++)
    {
        if(_shiftData[i]->date() == date)
        {
            _shiftData[i]->setPerformance(newPerformance);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setPositionScheduled(QString &newPositionScheduled, QDate &date){
    for(int i=0; i<_shiftData.size(); i++)
    {
        if(_shiftData[i]->date() == date)
        {
            _shiftData[i]->setPositionScheduled(newPositionScheduled);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setSynergy(QMap<QString, float> &newSynergy, QDate &date){
    for(int i=0; i<_shiftData.size(); i++)
    {
        if(_shiftData[i]->date() == date)
        {
            _shiftData[i]->setSynergy(newSynergy);
        }
    }
    qDebug()<<"the date was out of scope";
}

void EmployeeData::setShiftData(QDate &date, int &shiftScheduled, int &shiftID, QString &positionScheduled, double &performance, QMap<QString, float> &synergy){
    for(int i=0; i<_shiftData.size(); i++)
    {
        if(_shiftData[i]->date() == date)
        {
            _shiftData[i] = (new ShiftData(date, shiftScheduled, shiftID, positionScheduled, performance, synergy));
            break;
        }

    }
    _shiftData.append(new ShiftData(date, shiftScheduled, shiftID, positionScheduled, performance, synergy));
    emit schedulerDataChanged();
}

void EmployeeData::setShiftData(QList<ShiftData *> &list){
    if(_shiftData != list)
    {
        _shiftData = list;
        emit schedulerDataChanged();
    }
}

QMap<QString, QVariant> EmployeeData::convertSynergyMap(QDate &beginDate, QDate &endDate){ // converts a date organized QMap to a name organised QMap
    QMap<QDate, QMap<QString, float> > original =this->getSynergy();
    QMap<QString, float>tmp = original.value(endDate);
    QList<QString> stringTemp = tmp.keys();// since this is for 1 employee, this is constant for all dates
    QMap<QString, QVariant > converted;
    for(int i=0; i<stringTemp.count(); i++){
        QMap<QString, QVariant> newLowerMap;
        for(QDate d=beginDate; d!= endDate; d.addDays(1)){
            newLowerMap[d.toString(Qt::ISODate)] = tmp.value(stringTemp.at(i));
        }
        QVariant varTemp(newLowerMap);
        converted[stringTemp.at(i)] = varTemp;
    }
    return converted;
}

QVariant EmployeeData::avgPerformance(QDate &beginDate, QDate &endDate){// converts date & float to QString & QVariant for menu work
    QMap<QString, QVariant> retVal;
    for(QDate i=beginDate; i != endDate; i.addDays(1)){
        retVal[i.toString(Qt::ISODate)] = getScheduleFor(i)->performance();
    }
    return QVariant::fromValue(retVal);
}

