#ifndef EMPLOYEEDATA_H
#define EMPLOYEEDATA_H
#include <QObject>
#include <QUrl>
#include <QVariant>
class EmployeeData : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QUrl portrait READ portrait WRITE setPortrait NOTIFY portraitChanged)
//    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
//    Q_PROPERTY(QString position READ position WRITE setPosition NOTIFY positionChanged)
//    Q_PROPERTY(QVariant score READ score WRITE setScore NOTIFY scoreChanged)

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
