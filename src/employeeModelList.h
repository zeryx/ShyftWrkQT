#ifndef EMPLOYEEMODELLIST_H
#define EMPLOYEEMODELLIST_H
#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include "employeedata.h"
#include <QSortFilterProxyModel>
class EmployeeModelList : public QAbstractListModel
{

    Q_OBJECT

public:

    typedef QList<EmployeeData*>::const_iterator const_iterator;

    explicit EmployeeModelList(QObject *parent=0);

    explicit EmployeeModelList(const QString &name, QObject *parent =0);

public:

    enum EmployeeModelListDataRole
    {
        nameRole=Qt::UserRole+1,
        positionRole,
        portraitRole,
        scoreRole
    };
    //virtual inherited members from QAbstractTableModel
public:

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

//    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;

    bool setData(const QModelIndex &index,  QVariant &value, int role);

//    Qt::ItemFlags flags(const QModelIndex &parent = QModelIndex()) const;


public:

    void addPerson(EmployeeData *person);

    void removePerson(int index);

    EmployeeData* getPerson(size_t index);

    const_iterator begin()const{return m_data.begin();}

    const_iterator end()const{return m_data.end();}

    QString name() const;

signals:

    void nameChanged(QString& newname);

    void rowChanged(int newRowCount);

    void signalEmit(int irow, int icolumn);


protected:

    QHash<int, QByteArray> roleNames() const;

public:

    QList<EmployeeData*> m_data;

    QString m_name;


};

#endif // EMPLOYEEMODELLIST_H
