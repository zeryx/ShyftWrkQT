#include "employeeModelList.h"
#include <QObject>
#include <QDebug>
#include <assert.h>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

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
    if(index.isValid() && index.row() <= this->rowCount() && index.row() >= 0)
    {

        switch(role)
        {
        case nameRole:
            m_data[index.row()]->setName(value.toString());
            break;
        case portraitRole:
            m_data[index.row()]->setPortrait(value.toString());
            break;
        case positionRole:
            m_data[index.row()]->setPosition(value.toString());
            break;
        case scoreRole:
            m_data[index.row()]->setScore(value.toString());
            break;
        default:
            return false;
        }

        emit dataChanged(index, index);

        return true;
    }
    qDebug() << "data wasn't set!";

    return false;
}

Qt::ItemFlags EmployeeModelList::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return EmployeeModelList::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}

//no slots yay! will have data manipulation slots later

void EmployeeModelList::addPerson(EmployeeData* person)
{
    if(std::find(m_data.begin(),m_data.end(), person) != m_data.end()) //This doesn't do anything
    {
        qDebug() << "name already exists";
        return;
    }

    beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());

    m_data << person;

    endInsertRows();
}


bool EmployeeModelList::addPersonFromSql(QSqlDatabase &db)
{
        QSqlQuery query("SELECT * FROM Employees", db);
        int nameField = query.record().indexOf("Name");
        int positionField = query.record().indexOf("Position");
        int portraitField = query.record().indexOf("Portrait");
        int scoreField = query.record().indexOf("Individual_Performance");
        while(query.next()){
            QString Name = query.value(nameField).toString();
            QString Position = query.value(positionField).toString();
            QUrl Portrait = QUrl(query.value(portraitField).toString());
            int Score = query.value(scoreField).toInt();
            this->addPerson(new EmployeeData(Portrait, Name, Position, Score));
        }
        return true;
}

bool EmployeeModelList::addPersonToSql(QSqlDatabase &db, EmployeeData * Person)
{
        QSqlQuery query(db);
        query.prepare("INSERT INTO `Employees` (id, Name, Position, Portrait, Individual_Performance, Interpersonal_Performance)"
                        "Values (:id, :Name, :Position, :Portrait, :Individual_Performance, :Interpersonal_Performance)");

        query.bindValue(":id", QVariant()); //QVariant() == NULL, which tells mysql to auto_inc
        query.bindValue(":Name", Person->name());
        query.bindValue(":Position", Person->position());
        query.bindValue(":Portrait", Person->portrait());
        query.bindValue(":Individual_Performance", Person->score()); // dummy values for now
        query.bindValue(":Interpersonal_Performance", ""); //unsused for now
        qDebug()<<"person added to database? "<<query.exec();
        if(!query.isValid())
        {
            return false;
        }
        return true;
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
