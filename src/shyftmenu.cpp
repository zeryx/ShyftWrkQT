#include "shyftmenu.h"
#include <QJsonObject>
ShyftMenu::ShyftMenu(QObject *parent) :
    QObject(parent)
{

}

void ShyftMenu::createShyftPivotMenu(StaffModel *staff){//migrate this to QML I think? Play with this tomorrow
    for(int i=0; i<staff->rowCount(); i++){
        QMap<QString, QVariant> synergy = staff->_data.at(i)->convertSynergyMap(_begin, _end);
        QVariant performance = staff->_data.at(i)->avgPerformance(_begin, _end);
       QList<QMenu *>synergySubmenu;
       synergySubmenu.append(_menuConstructor.createSubMenu(QString("Synergy"), &synergy));
       _menuConstructor.createMenu(QString("Pivot"), synergySubmenu);
       _staffMenus.append(_menuConstructor.getConstructedMenu());
        _menuConstructor.addAction(QString("Performance"), performance, _staffMenus.at(i));
    }
}

void ShyftMenu::setBeginDate(QDate begin){
    _begin = begin;
}

void ShyftMenu::setEndDate(QDate end){
    _end = end;
}
