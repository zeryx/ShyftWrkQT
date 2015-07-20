#include "src/staffmodel.h"

#include <QObject>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QAbstractListModel>
#include <QPluginLoader>
StaffModel::StaffModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

int StaffModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(_data.isEmpty())
        return 0;

    return _data.count();
}

QVariant StaffModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= _data.count())
        return QVariant();

    const EmployeeData *data = _data[index.row()];
    switch(role)
    {
    case firstNameRole:
        return data->firstName();
    case lastNameRole:
        return data->lastName();
    case portraitRole:
        return data->portrait();
    case positionRole:
        return data->positions();
    case uidRole:
        return data->uid();
    default:
        return QVariant();
    }
}

bool StaffModel::setData(const QModelIndex &index, QVariant &value, int role){
    if(index.isValid() && index.row() <= this->rowCount() && index.row() >= 0)
        return false;

    switch(role)
    {
    case firstNameRole:
        _data[index.row()]->setFirstName(value.toString());
        break;
    case lastNameRole:
        _data[index.row()]->setLastName(value.toString());
    case portraitRole:
        _data[index.row()]->setPortrait(value.toString());
        break;
    case positionRole:
        _data[index.row()]->setPositions(value.toString());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags StaffModel::flags(const QModelIndex &index) const{
    if(index.isValid())
        return StaffModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}

QVariant StaffModel::headerData(int section, Qt::Orientation orientation, int role) const{
    Q_UNUSED(orientation);  // orientation and role are unused as this is strictly header data storage, and all headers are from position
    Q_UNUSED(role);

    if(section > _Headers.size())
        return QVariant();
    return _Headers.value(section);
}


void StaffModel::setHeaderData(const QString &value){
    for(int i=0; i<=_Headers.size()-1; i++)
    {
        if(_Headers.value(i) == value)
            return;
    }
    _Headers[_Headers.size()] = value; // this should "append" headers
}

int StaffModel::headerSize(){
    return _Headers.size();
}

void StaffModel::setHeaderDataSlot(const QString &value)
{
    setHeaderData(value);
}

QStringList StaffModel::headerList()
{
    QStringList temp;
    for(int i=0; i<_Headers.size(); i++)
    {
        temp.append(_Headers.value(i));
    }
    return temp;
}

QHash<int, QByteArray> StaffModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[firstNameRole] = "firstName";
    roles[lastNameRole] = "lastName";
    roles[portraitRole] = "portrait";
    roles[positionRole] = "position";
    roles[uidRole] = "uid";
    return roles;
}
EmployeeData* StaffModel::getPerson(size_t index){
    return _data[index];
}

bool StaffModel::populate(QJsonObject stream){
    QList<EmployeeData*> *employTmp = new QList<EmployeeData*>;
    for(int i=0; stream["staff"].toObject().contains("employee" +QString::number(i)); i++){
        QList<ShiftData*> *schedTmp = new QList<ShiftData*>;

        QUrl partial("http://www.shyftwrk.com");

        QJsonObject employeeItr = stream["staff"].toObject()["employee" +QString::number(i)].toObject(); //for readability

        //append shift data
        for(int j=0; employeeItr["shift data"].toObject().contains("shift"+QString::number(j)); j++){

            QJsonObject shiftItr = employeeItr["shift data"].toObject()["shift"+QString::number(j)].toObject(); //for readability

            QMap<QString, float> synergy;

            for(int k=0; shiftItr["synergy"].toObject().contains("synergy"+QString::number(k)); k++){
                QJsonObject synergyItr = shiftItr["synergy"].toObject()["synergy"+QString::number(k)].toObject();
                QString column = synergyItr["column"].toString();
                column = column.remove(0, 4); // remove the synergy column identifiers, no longer needed
                synergy[column] = synergyItr["data"].toDouble();
            }
            QVariant date(shiftItr["date"]);
            schedTmp->append(new ShiftData(
                                date.toDate(),
                                shiftItr["shift scheduled"].toInt(),
                            shiftItr["shift id"].toInt(),
                    shiftItr["position scheduled"].toString(),
                    shiftItr["performance"].toDouble(),
                    synergy, this));
        }
        //append employeeData
        employTmp->append(new EmployeeData(
                             employeeItr["first name"].toString(),
                         employeeItr["last name"].toString(),
                employeeItr["uid"].toString(),
                employeeItr["positions"].toString(),
                partial.resolved((QUrl)employeeItr["portrait"].toString()), schedTmp));

        QStringList positions = employeeItr["positions"].toString().split(",", QString::SkipEmptyParts);//split positions
        for(int k=0; k<positions.length(); k++){
            positions[k] = positions[k].simplified();
            this->setHeaderData(positions[k]);
        }
    }
    beginResetModel();
    this->_data.clear();
    endResetModel();
    this->_data = *employTmp;
    if(this->_data.length() <=0)
        return false;

    return true;
}


