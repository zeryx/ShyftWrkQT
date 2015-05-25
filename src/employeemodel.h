#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H
#include <QObject>
class EmployeeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString myName READ myName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString myColor READ myColor WRITE setColor NOTIFY colorChanged)
    //add real data objects here once tested1
public:
    EmployeeModel(QObject* =0);
    EmployeeModel(const QString &nme, const QString &clr, QObject* parent=0);

    void setName(const QString &n);
    QString myName();

    void setColor(const QString &color);
    QString myColor();

    void setData(QString m_name, QString m_color);

//    virtual QHash<int, QByteArray>roleNames ();
public slots:
    void searchTextChanged(QString m_searchText);

signals:
void nameChanged();
void colorChanged();

protected:
    QString m_name;
    QString m_color;

};

#endif // EMPLOYEEMODEL_H
