#include "shiftdata.h"

ShiftData::ShiftData(QObject *parent)
    :QObject(parent){
}

ShiftData::ShiftData(QDate newDate, int newShiftScheduled, int newShiftID, QString newPositionScheduled, double newPerformance, QMap<QString, float> newSynergy, QObject *parent)
    :QObject(parent){
    this->setDate(newDate);
    this->setShiftScheduled(newShiftScheduled);
    this->setShiftID(newShiftID);
    this->setPositionScheduled(newPositionScheduled);
    this->setPerformance(newPerformance);
    this->setSynergy(newSynergy);
}

//-- gets
int ShiftData::shiftScheduled() const{
    return _shiftScheduled;
}

double ShiftData::performance() const{
    return _performance;
}

QDate ShiftData::date() const{
    return _date;
}

int ShiftData::shiftID() const{
    return _shiftID;
}
QString ShiftData::positionScheduled() const{
    return _positionScheduled;
}

QMap<QString, float> ShiftData::synergy() const{
    return _synergy;
}

float ShiftData::synergyWith(QString& person) const{
    return _synergy.value(person);
}

float ShiftData::synergyWith(int& index) const{
    QList<float> temp;
    temp = synergy().values();
    return temp.at(index);
}


//-- sets
void ShiftData::setShiftScheduled(int newShiftScheduled){
    if(newShiftScheduled != _shiftScheduled){
        _shiftScheduled = newShiftScheduled;
        emit shiftScheduledChanged();
    }
}

void ShiftData::setShiftID(int newShiftID){
    if(newShiftID != _shiftID){
        _shiftID = newShiftID;
        emit shiftIDChanged();
    }
}

void ShiftData::setPerformance(double newPerformance){
    if(newPerformance != _performance){
        _performance = newPerformance;
        emit performanceChanged();
    }
}

void ShiftData::setDate(QDate newDate){
    if(newDate != _date){
        _date = newDate;
        emit dateChanged();
    }
}

void ShiftData::setPositionScheduled(QString newPositionScheduled){
    if(newPositionScheduled != _positionScheduled){
        _positionScheduled = newPositionScheduled;
        emit positionScheduledChanged();
    }
}


void ShiftData::setSynergy(QMap<QString, float> newSynergy){
    if(newSynergy != _synergy){
        _synergy = newSynergy;
        emit synergyChanged();
    }
}
