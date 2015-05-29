#include "employeedata.h"

EmployeeData::EmployeeData()
{
}

EmployeeData::EmployeeData(const QUrl &portrait, const QString &name, const QString &position, const QVariant &score)
{
    this->setPortrait(portrait);
    this->setName(name);
    this->setPosition(position);
    this->setScore(score);
}


QUrl EmployeeData::portrait() const
{
return m_portrait;
}

QString EmployeeData::name() const
{
    return m_name;
}

QString EmployeeData::position() const
{
    return m_position;
}

QVariant EmployeeData::score() const
{
    return m_score;
}

void EmployeeData::setPortrait(QUrl portrait)
{
    if(m_portrait != portrait){
        m_portrait = portrait;
        emit portraitChanged();
    }
}

void EmployeeData::setName(QString name)
{
    if(m_name != name){
        m_name = name;
        emit nameChanged();
    }
}

void EmployeeData::setPosition(QString position)
{
    if(m_position != position){
        m_position = position;
        emit positionChanged();
    }
}

void EmployeeData::setScore(QVariant n_score){
    if(m_score != n_score){
        m_score = n_score;
        emit scoreChanged();
    }
}
