#include "employeemodel.h"
#include <QObject>
#include <QDebug>
EmployeeModel::EmployeeModel(QObject *){

}

EmployeeModel::EmployeeModel(const QString &nme, const QString &clr, QObject*){
    setName(nme);
    setColor(clr);
}

void EmployeeModel::setName(const QString &n){
    if(n != m_name){
        m_name = n;
        emit nameChanged();
    }
}

QString EmployeeModel::myName(){
    return m_name;
}

void EmployeeModel::setColor(const QString &color){
    if(color != m_color){
        m_color = color;
        emit colorChanged();
    }
}

QString EmployeeModel::myColor(){
    return m_color;
}

void EmployeeModel::setData(QString m_name, QString m_color){

    setColor(m_color);
    setName(m_name);

}


//slots

void EmployeeModel::searchTextChanged(QString m_searchText){
    qDebug() <<"recieved signal! \nText is: "<<m_searchText;
}

//virtual EmployeeModel::roleNames(){
//    QHash<int, QByteArray> roles;
//    roles[MyViewModel_Roles_Display] = "role_display";
//    roles[MyViewModel_Roles_Details] = "role_details";
//    roles[MyViewModel_Roles_KeyId] = "role_keyid";
//    roles[MyViewModel_Roles_Value] = "role_value";
//    return roles;
//}
