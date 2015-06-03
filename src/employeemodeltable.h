#ifndef EMPLOYEEMODELTABLE_H
#define EMPLOYEEMODELTABLE_H


#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include "employeedata.h"
#include <QSortFilterProxyModel>

class EmployeeModelTable : public QAbstractTableModel
{

    Q_OBJECT

public:


    explicit EmployeeModelTable(QObject *parent=0);

    explicit EmployeeModelTable(const QString &name,  QObject *parent =0);


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

    int rowCount(int column) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;

    bool setData(const QModelIndex &index,  QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;


public:

    void addPerson(EmployeeData *person, int column);

    bool addPersonFromSql(QString &hostname, QString &database, QString &username, QString &password);


    void removePerson(QModelIndex &index);

    EmployeeData* getPerson(QModelIndex &index);

    QString name() const;

signals:

    void rowChanged(int newRowCount);

    void columnChanged(int newColumnCount);

    void signalEmit(int irow, int icolumn);

protected:

    QHash<int, QByteArray> roleNames() const;

public:

    QList < QList < EmployeeData* > > m_data;

    QString m_name;

};

#endif // EMPLOYEEMODELTABLE_H
