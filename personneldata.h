#ifndef PERSONNELDATA_H
#define PERSONNELDATA_H

#include <QObject>
#include <QQuickItem>
#include "qimage.h"
class personnelData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage portrait READ portrait WRITE setPortrait NOTIFY portraitChanged)
    Q_PROPERTY(QString pname READ pname WRITE setPName NOTIFY pNameChanged)
    Q_PROPERTY(float score READ score WRITE setScore NOTIFY scoreChanged)
public:
    explicit personnelData(QObject *parent = 0);
    personnelData(const QImage &portrait, const QString &name, const float &score, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QImage portrait() const;
    void setPortrait(const QImage &portrait);

    float score() const;
    void setScore(const float &score);

signals:
    void nameChanged();
    void portraitChanged();
    void scoreChanged();
private:
    QString m_name;
    QImage *m_portrait = new QImage();
    float m_score;
};

#endif // PERSONNELDATA_H
