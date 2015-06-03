#include "employeemodeltable.h"
#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
EmployeeModelTable::EmployeeModelTable(QObject *parent)
    :QAbstractTableModel(parent)
{
}

EmployeeModelTable::EmployeeModelTable(const QString &name, QObject *parent)
:m_name(name)
    ,QAbstractTableModel(parent)
{
}

int EmployeeModelTable::rowCount(const QModelIndex &parent) const
{
    if(!m_data.isEmpty())
        return 0;

    //rows are the lower QList
    return m_data[parent.column()].count();
}

int EmployeeModelTable::rowCount(const int column)const
{
    if(!m_data.isEmpty())
        return 0;

    return m_data[column].count();
}
int EmployeeModelTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(!m_data.isEmpty())
        return 0;

    //columns are the higher QList
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
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags EmployeeModelTable::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}

void EmployeeModelTable::addPerson(EmployeeData *person, int column)
{
//    for(int incr=0; incr < m_data.count(); incr++)
//    {
//        if(std::find(m_data[incr].begin(),m_data[incr].end(), person) != m_data[incr].end())
//        {
//            qDebug() <<"person already exists in records!";
//            return;
//        }
//    }
    qDebug() << "row size: " <<this->rowCount(column);
    beginInsertRows(QModelIndex(),this->rowCount(column), this->rowCount(column));
    m_data[column] << person;
    rowChanged(m_data[column].count());
    endInsertRows();
}

bool EmployeeModelTable::addPersonFromSql(QString &hostname, QString &database, QString &username, QString &password)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL", "addPersonFromSQL");
    db.setHostName(hostname);
    db.setPort(3306);
    db.setDatabaseName(database);
    db.setUserName(username);
    db.setPassword(password);
    qDebug()<<"did the socket open? " << db.open();
    if(!db.isOpen())
    {
        qDebug() << db.lastError();
        return false;
    }
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

            //need to fix addPerson before this line works
//            this->addPerson(new EmployeeData(Portrait, Name, Position, Score));
        }
        db.close();
        if(db.isOpen())
        {
            qDebug() << db.lastError();
            return false;
        }
        return true;
}

void EmployeeModelTable::removePerson(QModelIndex &index)
{
    QList<EmployeeData*>::iterator itr;
    itr = m_data[index.column()].begin();
    beginRemoveRows(QModelIndex(), this->rowCount(), this->rowCount());
    std::advance(itr, index.row());
    m_data[index.column()].erase(itr);
    endRemoveRows();
}


EmployeeData* EmployeeModelTable::getPerson(QModelIndex &index)
{
    return m_data[index.column()][index.row()];
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

QString EmployeeModelTable::name() const
{
    return m_name;
}
