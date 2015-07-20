#ifndef SHYFTMENU_H
#define SHYFTMENU_H

#include <QObject>
#include <QDate>
#include "menuconstructor.h"
#include "staffmodel.h"
class ShyftMenu : public QObject
{
    Q_OBJECT
public:
    explicit ShyftMenu(QObject *parent = 0);

    Q_INVOKABLE void createShyftPivotMenu(StaffModel*);

    Q_INVOKABLE void setBeginDate(QDate begin);

    Q_INVOKABLE void setEndDate(QDate end);
private:
    MenuConstructor _menuConstructor;
    QList<QMenu*> _staffMenus;
    StaffModel *_staffModel;
    QDate _begin;
    QDate _end;
};

#endif // SHYFTMENU_H
