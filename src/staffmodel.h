#ifndef STAFFMODEL_H
#define STAFFMODEL_H
#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QMap>
#include "src/modelClassComponents/employeedata.h"
class StaffModel : public QAbstractListModel
{
/* this is the base model that interacts with the sql database, all other models mirror their data from here
 * the model is directly used for constructing the ScrollableEmployeeColumn and is masked with a
 *  QSortFilterProxyModel for adaptive search functionality*/

    Q_OBJECT
public:

    typedef QList<EmployeeData*>::const_iterator const_iterator;

    explicit StaffModel(QObject *parent=0);

public:

    enum StaffModelDataRole // will add more roles
    {
        firstNameRole=Qt::UserRole+1,
        lastNameRole,
        positionRole,
        portraitRole,
        uidRole
    };
    //virtual inherited members from QAbstractTableModel
public:

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;

    bool setData(const QModelIndex &index,  QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const;

public:
    EmployeeData* getPerson(size_t index);

    void setHeaderData( const QString &value);

    int headerSize();

    QStringList headerList();

    const_iterator begin()const{return _data.begin();}

    const_iterator end()const{return _data.end();}

    bool populate(QJsonObject);

public: // things that get called from qml


public slots:

    void setHeaderDataSlot(const QString &value);


protected:

    QHash<int, QByteArray> roleNames() const;

    QHash<qint32, QString> _Headers;
public:

    QList<EmployeeData*> _data;



};

#endif // STAFFMODEL_H
