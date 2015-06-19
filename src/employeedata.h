#ifndef EMPLOYEEDATA_H
#define EMPLOYEEDATA_H
#include <QObject>
#include <QUrl>
#include <QVariant>
class EmployeeData : public QObject
{
    Q_OBJECT
public:

    EmployeeData();

    EmployeeData(const QUrl &portrait, const QString &name, const QString &position, const QVariant &score);

    QUrl portrait()const;

    QString name()const;

    QString position()const;

    QVariant score()const;

    void setPortrait(QUrl portrait);

    void setName(QString name);

    void setPosition(QString position);

    void setScore(QVariant score);

signals:

    void portraitChanged();

    void nameChanged();

    void positionChanged();

    void scoreChanged();

protected:

    QUrl m_portrait;
    QString m_name;
    QString m_position;
    QVariant m_score;
};

#endif // EMPLOYEEDATA_H
