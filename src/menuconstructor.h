#ifndef MENUCONSTRUCTOR_H
#define MENUCONSTRUCTOR_H

#include <QObject>
#include <QMenu>
#include <QList>
class MenuConstructor : public QObject
{
    Q_OBJECT
public:
    explicit MenuConstructor(QObject *parent = 0);
    QMenu* createSubMenu(const QString title, QMap<QString, QVariant> *menuItemData, const QIcon = QIcon());
    void createMenu(const QString title, QList<QMenu*> menus);
    void addAction(const QString title, QVariant menuItemData, QMenu* menu);

    QMenu* getConstructedMenu();

private:
    QMenu *_menu;

};

#endif // MENUCONSTRUCTOR_H
