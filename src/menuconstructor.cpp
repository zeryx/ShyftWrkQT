#include "menuconstructor.h"
#include <QAction>
#include <QMenu>
MenuConstructor::MenuConstructor(QObject *parent) :
    QObject(parent)
{
}


QMenu* MenuConstructor::createSubMenu(const QString title, QMap<QString, QVariant> *menuItemData, const QIcon icon){
    QMenu *newMenu = new QMenu();
    newMenu->setTitle(title);
    newMenu->setIcon(icon);
    QList<QAction*> actions;
    QMap<QString, QVariant >::Iterator i;
    for(i = menuItemData->begin(); i != menuItemData->end(); ++i) // for each keypair + string
    {
        QAction *newAction = new QAction(newMenu);
        newAction->setText(i.key());
        newAction->setIcon(icon);
        newAction->setData(i.value());
        actions.append(newAction);
    }
    newMenu->addActions(actions);
    return newMenu;
}

void MenuConstructor::createMenu(const QString title, QList<QMenu *> menus){//factory method, doesn't care what the type of menu is
    _menu = new QMenu(title);
    for(int i=0; i<menus.count(); i++){
        menus.at(i)->setParent(_menu);
        _menu->addMenu(menus.at(i));
    }
}

void MenuConstructor::addAction(const QString title, QVariant menuItemData, QMenu* menu){
    QAction * newAction = new QAction(menu);
    newAction->setText(title);
    newAction->setData(menuItemData);
    newAction->setIcon(QIcon());
    QList<QAction*> tmp;
    tmp.append(newAction);
    menu->addActions(tmp);
}

QMenu* MenuConstructor::getConstructedMenu(){
    return _menu;
}
