#ifndef EMPLOYEEMODELTABLE_H
#define EMPLOYEEMODELTABLE_H


#include <QObject>
#include <QList>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include "employeedata.h"
#include "employeeModelMaster.h"

class EmployeeModelTable : public QAbstractTableModel
{

    Q_OBJECT
    Q_PROPERTY(QStringList headerList READ headerList)

public:

    typedef QList<QList<EmployeeData*> >::const_iterator const_iterator;


    explicit EmployeeModelTable(QObject *parent=0);


public:

    enum EmployeeModelTableDataRole
    {
        nameRole=Qt::UserRole+1,
        positionRole,
        portraitRole,
        scoreRole
    };

public:     //virtual inherited members from QAbstractTableModel

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index,  QVariant &value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::DisplayRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;


public: //new members specifically for our implementation

    bool newHeader(const QVariant &value);

    QString name() const;

    QStringList headerList();

    const_iterator begin()const{return m_data.begin();}

    const_iterator end()const{return m_data.end();}

signals:

    void headerDataChanged(int first, int last); //the only important signal from the tableModel

    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
public slots:

    void masterDataChanged(int rows, EmployeeModelMaster* master); //tells employeeModelTable to update, pulls from employeeModelMaster.


protected:

    QHash<int, QByteArray> roleNames() const;

    QList < EmployeeData* > str_data;

    QMap < int, QString > m_headerData;

public:

    QList < QList < EmployeeData* > > m_data;

    int headerItr;

};

#endif // EMPLOYEEMODELTABLE_H
