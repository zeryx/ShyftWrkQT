#include "employeemodeltable.h"
#include "employeeModelMaster.h"
#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
EmployeeModelTable::EmployeeModelTable(QObject *parent)
    :QAbstractTableModel(parent)
{
    QList<EmployeeData*> null;
    m_data.append(null);
}

int EmployeeModelTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(m_data[0].isEmpty())
        return 0;
    qDebug() <<"row counts value is: ";
    return m_data[0].count(); // since each column is identical, get the count from column 0
}

int EmployeeModelTable::columnCount(const QModelIndex &parent) const     //all columns are identical
{
    Q_UNUSED(parent);

    return m_data.count();

}

QVariant EmployeeModelTable::data(const QModelIndex &index, int role) const
{
    if(index.row() <0 || index.row()>= this->rowCount(index))
        return QVariant();

    if(index.column() <0 || index.column()>= this->columnCount())
        return QVariant();

    const EmployeeData *data = m_data[index.column()][index.row()];

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

bool EmployeeModelTable::setData(const QModelIndex &index, QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole && !(index.row() >= this->rowCount(index) || index.row() < 0)
            && !(index.column() >=this->columnCount() || index.column() <0))
    {
        switch(role)
        {
        case nameRole:
            m_data[index.column()][index.row()]->setName(value.toString());
            break;
        case portraitRole:
            m_data[index.column()][index.row()]->setPortrait(value.toString());
            break;
        case positionRole:
            m_data[index.column()][index.row()]->setPosition(value.toString());
            break;
        case scoreRole:
            m_data[index.column()][index.row()]->setScore(value.toString());
            break;
        default:
            return false;
        }
        emit dataChanged();
        return true;
    }
    return false;
}

bool EmployeeModelTable::setHeaderData(int section, Qt::Orientation orientation,  const QVariant &value, int role)
{
    Q_UNUSED(orientation); //orientation will always be horizontal

    if(role != Qt::DisplayRole)
        return false;

    for(int i=0; i <= m_headerData.count(); i++) //if the header already exists, don't make another one
    {
        if(m_headerData.at(i) == value)
            return false;
    }

    m_headerData[section] = value.toString();
    headerDataChanged(section, m_headerData.size());

    return true;
}

bool EmployeeModelTable::newHeader(const QVariant &value)
{

    for(int i=0; i<=columnCount(); i++) //if the header already exists, don't make another one
    {
        qDebug()<<"header adding begun";

        if(m_headerData[i] == value)
        {
            qDebug()<<"found duplicate";
            return false;
        }
    }
    m_headerData.append(value.toString());
    beginInsertColumns(QModelIndex(), 0, this->columnCount());
    m_data.append(str_data);
    qDebug() <<"Direct Columns: "<<m_data.count();
    endInsertColumns();
    return true;
}

QVariant EmployeeModelTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation); //orientation will always be horizontal
    if(role != Qt::DisplayRole)
        return QVariant();
    return m_headerData.at(section);
}


Qt::ItemFlags EmployeeModelTable::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}


QHash<int, QByteArray> EmployeeModelTable::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nameRole] = "name";
    roles[portraitRole] = "portrait";
    roles[positionRole] = "position";
    roles[scoreRole] = "score";
    return roles;
}

void EmployeeModelTable::masterDataChanged(int rows, EmployeeModelMaster* master)
{
    qDebug()<< "rows: "<<rows;
    for(int k=0; k<=this->columnCount(); k++)
    {
//        int ctr =0;
//        while(rows >= this->m_data[k].count()) // if the new row is bigger than the current, append with dummies
//        {
//            EmployeeData* nullperson = new EmployeeData();
//            this->m_data[k].append(nullperson);
//            this->str_data.append(nullperson);
//        }
//        qDebug()<<rowCount();
//        for(int i=0; i <= rows; i++)
//        {
//            beginInsertRows(QModelIndex(), 0, rowCount()+1);
//            if(i > m_data[k].count())
//            {
//                qDebug() <<"appended column "<< k <<"at row: "<< i;
//                this->m_data[k].append(master->m_data[i]);
//            }
//            if(i > str_data.count())
//                this->str_data.append(master->m_data[i]);
//            this->m_data[k][i] = master->m_data[i]; //replace existing data in table with new data from master
//            this->str_data[i] = master->m_data[i];

//            qDebug() << this->m_data[k][i]->portrait().toString();
//            endInsertRows();
//            newHeader(master->m_data[i]->position());
//        }
    }
}
