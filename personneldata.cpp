#include "personneldata.h"

personnelData::personnelData(QObject *parent) : QObject(parent)
{
}

personnelData::personnelData(const QImage &portrait, const QString &name, const float &score, QObject *parent)
    :QObject(parent), m_portrait(portrait), m_score(score), m_name(name)
{
}

QImage personnelData::portrait() const
{
    return m_portrait;
}

void personnelData::setPortrait(const QImage &portrait)
{
    if(portrait != m_portrait){
        m_portrait = portrait;
        emit portraitChanged();
    }
}

QString personnelData::name() const
{
    return m_name;
}

void personnelData::setName(const QString &name)
{
    if(name != m_name){
        m_name = name;
        emit nameChanged();
    }
}

float personnelData::score() const
{
    return m_score;
}

void personnelData::setScore(const float &score)
{
    if(score != m_score){
        m_score = score;
        emit scoreChanged();
    }
}
