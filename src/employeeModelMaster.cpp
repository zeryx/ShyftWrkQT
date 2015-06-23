#include "src/employeeModelMaster.h"

#include <QObject>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
#include <QSqlRecord>

EmployeeModelMaster::EmployeeModelMaster(QObject *parent)
    :QAbstractListModel(parent)
{
}


int EmployeeModelMaster::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(m_data.isEmpty())
        return 0;

    return m_data.count();
}

QVariant EmployeeModelMaster::data(const QModelIndex &index, int role) const
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
        return data->position();
    case scoreRole:
        return data->score();
    default:
        return QVariant();
    }
}

bool EmployeeModelMaster::setData(const QModelIndex &index, QVariant &value, int role)
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

Qt::ItemFlags EmployeeModelMaster::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return EmployeeModelMaster::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}


void EmployeeModelMaster::addPerson(EmployeeData* person)
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

void EmployeeModelMaster::configSQL()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "pullFromSQL");
    db.setHostName("45.33.71.118");
    db.setPort(3306);
    db.setDatabaseName("ShyftWrk");
    db.setUserName("testuser");
    db.setPassword("test");
    qDebug() << "database connection is opened? " <<db.open();
}

bool EmployeeModelMaster::pullFromSQL() //pulls from configured SQL server with parameters specified in configSQL().
{

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
    QUrl baseURL("http://shyftwrk.com:80");

    while(query.next()){
        QString Name = query.value(nameField).toString();
        QString Position = query.value(positionField).toString();
        QUrl relative = query.value(portraitField).toUrl();
        int Score = query.value(scoreField).toInt();
        this->addPerson(new EmployeeData(baseURL.resolved(relative), Name, Position, Score));
        setHeaderData(Position);
    }
    return true;
}

bool EmployeeModelMaster::addPersonToSql( EmployeeData * Person)
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

void EmployeeModelMaster::removePerson(int col)
{
    QList<EmployeeData*>::iterator itr;

    itr = m_data.begin();

    beginRemoveRows(QModelIndex(), col, col);

   std::advance(itr, col);

    m_data.erase(itr);

    endRemoveRows();

}

QVariant EmployeeModelMaster::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);  // orientation and role are unused as this is strictly header data storage, and all headers are from position
    Q_UNUSED(role);

    if(section > headers.size())
        return QVariant();
    return headers.value(section);
}


void EmployeeModelMaster::setHeaderData(const QString &value)
{
    for(int i=0; i<=headers.size()-1; i++)
    {
        if(headers.value(i) == value)
            return;
    }
    headers[headers.size()] = value; // this should "append" headers
}

int EmployeeModelMaster::headerSize()
{
    return headers.size();
}

void EmployeeModelMaster::setHeaderDataSlot(const QString &value)
{
    setHeaderData(value);
}

QStringList EmployeeModelMaster::headerList()
{
    QStringList temp;
    for(int i=0; i<headers.size(); i++)
    {
        temp.append(headers.value(i));
    }
    return temp;
}

QHash<int, QByteArray> EmployeeModelMaster::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nameRole] = "name";
    roles[portraitRole] = "portrait";
    roles[positionRole] = "position";
    roles[scoreRole] = "score";
    return roles;
}
EmployeeData* EmployeeModelMaster::getPerson(size_t index)
{
    return m_data[index];
}

void EmployeeModelMaster::connectionsPostLogin()
{
    QObject *search = m_win->findChild<QObject*>("search");
    QObject::connect(search, SIGNAL(hasText(QString)), m_proxy, SLOT(setFilterRegExp(QString)));
}
