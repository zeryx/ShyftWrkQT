#include "employeeModelList.h"
#include <QObject>
#include <QDebug>
#include <assert.h>
#include <iostream>

EmployeeModelList::EmployeeModelList(QObject *parent)
    :QAbstractListModel(parent)
{
}

EmployeeModelList::EmployeeModelList(const QString &name, QObject *parent)
    :m_name(name)
    ,QAbstractListModel(parent)
{
}


int EmployeeModelList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(m_data.isEmpty())
        return 0;

    return m_data.count();
}

QVariant EmployeeModelList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    const EmployeeData *data = m_data[index.row()];
    if (role == nameRole)
        return data->name();
    else if (role == portraitRole)
        return data->portrait();
    else if(role == positionRole)
        return data->position();
    else if(role == scoreRole)
        return data->score();
    else
        return QVariant();
}

bool EmployeeModelList::setData(const QModelIndex &index, QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole && !(index.row()>= m_data.size() || index.row() < 0)){
        int col = index.row();

        switch(index.row()){
        case nameRole:
            m_data[col]->setName(value.toString());
            break;
        case portraitRole:
            m_data[col]->setPortrait(value.toString());
            break;
        case positionRole:
            m_data[col]->setPosition(value.toString());
            break;
        case scoreRole:
            m_data[col]->setScore(value.toString());
            break;
        default:
            return false;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}



//no slots yay! will have data manipulation slots later

void EmployeeModelList::addPerson(EmployeeData* person)
{
    if(std::find(m_data.begin(),m_data.end(), person) != m_data.end())
        return;
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << person;
    endInsertRows();
}

void EmployeeModelList::removePerson(int col)
{
    QList<EmployeeData*>::iterator itr;
    itr = m_data.begin();
    beginRemoveRows(QModelIndex(), col, col);
   std::advance(itr, col);
    m_data.erase(itr);
    endRemoveRows();
}


QHash<int, QByteArray> EmployeeModelList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nameRole] = "name";
    roles[portraitRole] = "portrait";
    roles[positionRole] = "position";
    roles[scoreRole] = "score";
    return roles;
}
EmployeeData* EmployeeModelList::getPerson(size_t index)
{
    return m_data[index];
}

QString EmployeeModelList::name() const
{
    return m_name;
}
