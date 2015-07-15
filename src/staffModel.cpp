#include "src/staffmodel.h"

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

bool StaffModel::setData(const QModelIndex &index, QVariant &value, int role)
{
    if(index.isValid() && index.row() <= this->rowCount() && index.row() >= 0)
        return false;

    switch(role)
    {
    case firstNameRole:
        m_data[index.row()]->setFirstName(value.toString());
        break;
    case lastNameRole:
        m_data[index.row()]->setLastName(value.toString());
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
    roles[firstNameRole] = "firstName";
    roles[lastNameRole] = "lastName";
    roles[portraitRole] = "portrait";
    roles[positionRole] = "position";
    roles[uidRole] = "uid";
    return roles;
}
EmployeeData* StaffModel::getPerson(size_t index){
    return m_data[index];
}
void StaffModel::setJson(QString column, QVariant value){
    if(value.type() == QVariant::String)
        storeStream[column] = value.toString();
    else if(value.type() == QVariant::Int)
        storeStream[column] = value.toInt();
    else if(value.type() == QVariant::Bool)
        storeStream[column] = value.toBool();
}

void StaffModel::alterStaff(){
    if(this->storeStream["mode"].toString() == "new"){
        this->requestStaffChange(new EmployeeData(
                this->storeStream["first name"].toString(),
                this->storeStream["last name"].toString(),
                this->storeStream["uid"].toString(),
                this->storeStream["positions"].toString(),
                this->storeStream["portrait"].toString()), this->restAdd);
    }
    else if(this->storeStream["mode"].toString() == "edit"){
        this->requestStaffChange(new EmployeeData(
                this->storeStream["first name"].toString(),
                this->storeStream["last name"].toString(),
                this->storeStream["uid"].toString(),
                this->storeStream["positions"].toString(),
                this->storeStream["portrait"].toString()), this->restEdit);
    }
    else if(this->storeStream["mode"] == this->restRemove){
        EmployeeData tmp;
        tmp.setUID(this->storeStream["uid"].toString());
        this->requestStaffChange(&tmp, this->restRemove);
    }
    bool chk = this->populate(this->requestDataRefresh()); // this works, I feel like I have way too many methods for this god class
    emit triggerMain(chk);
}
bool StaffModel::populate(QJsonObject stream){
    if(stream["queryCode"] == "failed")
        return false;
    QList<EmployeeData*> employTmp;
    for(int i=0; stream["staff"].toObject().contains("employee" +QString::number(i)); i++){
        QList<SchedulerData*> schedTmp;

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
            schedTmp.append(new SchedulerData(
                    date.toDate(),
                    shiftItr["shift scheduled"].toInt(),
                    shiftItr["shift id"].toInt(),
                    shiftItr["position scheduled"].toString(),
                    shiftItr["performance"].toDouble(),
                    synergy, this));
        }
        //append employeeData
        employTmp.append(new EmployeeData(
                employeeItr["first name"].toString(),
                employeeItr["last name"].toString(),
                employeeItr["uid"].toString(),
                employeeItr["positions"].toString(),
                partial.resolved((QUrl)employeeItr["portrait"].toString()),
                &schedTmp));

        QStringList positions = employeeItr["positions"].toString().split(",", QString::SkipEmptyParts);//split positions
        for(int k=0; k<positions.length(); k++){
            positions[k] = positions[k].simplified();
            this->setHeaderData(positions[k]);
        }
    }

    this->beginRemoveRows(QModelIndex(), 0, this->rowCount()); // delete everything first
    this->m_data.clear();
    this->endRemoveRows();

    for(int i=0; i<employTmp.count(); i++){
        beginInsertRows(QModelIndex(), 0, 0);
        this->m_data.prepend(employTmp.at(i));
        endInsertRows();
    }
    return true;
}

bool StaffModel::loginAndPull(QString username, QString password, QString organisation){ // this class can move somewhere else
    if(this->requestLogin(username, password, organisation)){
        if(this->populate(this->requestDataRefresh()))
            return true;
    }
    return false;
}

