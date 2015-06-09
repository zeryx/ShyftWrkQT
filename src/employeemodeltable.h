#ifndef EMPLOYEEMODELTABLE_H
#define EMPLOYEEMODELTABLE_H


#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include "employeedata.h"
#include "employeeModelMaster.h"
#include <QSqlDatabase>
#include <QSortFilterProxyModel>

class EmployeeModelTable : public QAbstractTableModel
{

    Q_OBJECT

public:


    explicit EmployeeModelTable(QObject *parent=0);


public:

    enum EmployeeModelListDataRole
    {
        nameRole=Qt::UserRole+1,
        positionRole,
        portraitRole,
        scoreRole
    };

public:     //virtual inherited members from QAbstractTableModel

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;

    bool setData(const QModelIndex &index,  QVariant &value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::DisplayRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;


public: //new members specifically for our implementation

    bool newHeader(const QVariant &value);

    QString name() const;

signals:

    void rowChanged(int newRowCount);

    void columnChanged(int newColumnCount); //both of these are dummies since proxyModel will be doing all the work on top

    void headerDataChanged(int first, int last); //the only important signal from the tableModel

    void dataChanged();

public slots:

    void masterDataChanged(int rows, EmployeeModelMaster* master); //tells employeeModelTable to update, pulls from employeeModelMaster.


protected:

    QHash<int, QByteArray> roleNames() const;

public:

    QList < QList < EmployeeData* > > m_data;

    QList < EmployeeData* > str_data;

    QList < QString > m_headerData;

};

#endif // EMPLOYEEMODELTABLE_H
