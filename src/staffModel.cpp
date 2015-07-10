﻿#include "src/staffmodel.h"

#include <QObject>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QPluginLoader>
StaffModel::StaffModel(QObject *parent)
    :RestClient(parent)
{
}

int StaffModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(m_data.isEmpty())
        return 0;

    return m_data.count();
}

QVariant StaffModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    const EmployeeData *data = m_data[index.row()];
    switch(role)
    {
    case nameRole:
        return data->name();
    case portraitRole:
        return data->portrait();
    case positionRole:
        return data->positions();
    default:
        return QVariant();
    }
}

bool StaffModel::setData(const QModelIndex &index, QVariant &value, int role)
{
    if(index.isValid() && index.row() <= this->rowCount() && index.row() >= 0)
        return false;

        switch(role)
        {
        case nameRole:
            m_data[index.row()]->setName(value.toString());
            break;
        case portraitRole:
            m_data[index.row()]->setPortrait(value.toString());
            break;
        case positionRole:
            m_data[index.row()]->setPositions(value.toString());
            break;
        default:
            return false;
        }

        emit dataChanged(index, index);

        return true;
}

Qt::ItemFlags StaffModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return StaffModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}


bool StaffModel::addPerson(EmployeeData* person)
{
    for(int i = rowCount()-1; i>=0; i--)
    {
        if(m_data[i] == person)
        {
            qDebug()<<"this person already exists in the database.";
            return 0;
        }
    }


    beginInsertRows(QModelIndex(), this->rowCount()-1, this->rowCount());

    m_data << person;

    endInsertRows();

    return this->requestStaffChange(person, restAdd);
}



bool StaffModel::removePerson(int col)
{
    QList<EmployeeData*>::iterator itr;

    itr = m_data.begin();

    beginRemoveRows(QModelIndex(), col, col);

   std::advance(itr, col);

    m_data.erase(itr);

    endRemoveRows();

    return this->requestStaffChange(m_data[col],restRemove); // remove this staff from this organisation
}

QVariant StaffModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);  // orientation and role are unused as this is strictly header data storage, and all headers are from position
    Q_UNUSED(role);

    if(section > headers.size())
        return QVariant();
    return headers.value(section);
}


void StaffModel::setHeaderData(const QString &value)
{
    for(int i=0; i<=headers.size()-1; i++)
    {
        if(headers.value(i) == value)
            return;
    }
    headers[headers.size()] = value; // this should "append" headers
}

int StaffModel::headerSize()
{
    return headers.size();
}

void StaffModel::setHeaderDataSlot(const QString &value)
{
    setHeaderData(value);
}

QStringList StaffModel::headerList()
{
    QStringList temp;
    for(int i=0; i<headers.size(); i++)
    {
        temp.append(headers.value(i));
    }
    return temp;
}

QHash<int, QByteArray> StaffModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nameRole] = "name";
    roles[portraitRole] = "portrait";
    roles[positionRole] = "position";
    roles[avgPerformanceRole] = "avgPerformance";
    roles[synergyRole] = "synergy";
    roles[avgShiftsRole] = "avgShifts";
    return roles;
}
EmployeeData* StaffModel::getPerson(size_t index)
{
    return m_data[index];
}


bool StaffModel::loginAndPull(QString username, QString password, QString organisation){
    if(this->requestLogin(username, password, organisation)){
        QJsonObject fullIter = this->requestDataRefresh();
        QList<EmployeeData*> tmp;
        qDebug()<<fullIter["staff"].toObject().contains("employee" +QString::number(0));
        for(int i=0; fullIter["staff"].toObject().contains("employee" +QString::number(i)); i++){

            QUrl partial("http://www.shyftwrk.com");
            QJsonObject currentItr = fullIter["staff"].toObject()["employee" +QString::number(i)].toObject(); //for readability
            tmp.append(new EmployeeData(
                           currentItr["name"].toString(),
                       currentItr["uid"].toString(),
                    currentItr["positions"].toString(),
                    partial.resolved((QUrl)currentItr["portrait"].toString())));
            QStringList positions = currentItr["positions"].toString().split(",", QString::SkipEmptyParts);//split positions
            for(int k=0; k<positions.length(); k++){
                positions[k] = positions[k].simplified();
                this->setHeaderData(positions[k]);
            }
        }
        this->beginInsertRows(QModelIndex(), 0, this->rowCount());
        this->m_data = tmp;
        this->endInsertRows();
        return true;
    }
    else
        return false;
}