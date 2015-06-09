#ifndef EMPLOYEEMODELMASTER_H
#define EMPLOYEEMODELMASTER_H
#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include "employeedata.h"
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
class EmployeeModelMaster : public QAbstractListModel
{

    Q_OBJECT

public:

    typedef QList<EmployeeData*>::const_iterator const_iterator;

    explicit EmployeeModelMaster(QObject *parent=0);

public:

    enum EmployeeModelMasterDataRole
    {
        nameRole=Qt::UserRole+1,
        positionRole,
        portraitRole,
        scoreRole
    };
    //virtual inherited members from QAbstractTableModel
public:

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;

    bool setData(const QModelIndex &index,  QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &parent = QModelIndex()) const;


public:

    void addPerson(EmployeeData *person);

    bool pullFromSQL();

    bool addPersonToSql (QSqlDatabase &db, EmployeeData *Person);

    void removePerson(int index);

    EmployeeData* getPerson(size_t index);

    const_iterator begin()const{return m_data.begin();}

    const_iterator end()const{return m_data.end();}

signals:

    void nameChanged(QString& newname);

    void rowChanged(int newRowCount, EmployeeModelMaster* master);

protected:

    QHash<int, QByteArray> roleNames() const;

public:

    QList<EmployeeData*> m_data;



};

#endif // EMLOYEEMODELMASTER_H
