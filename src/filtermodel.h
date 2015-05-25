#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QObject>
#include "src/employeemodel.h"
class FilterModel : public EmployeeModel
{
    Q_OBJECT
public:
    FilterModel(QObject* parent =0);
    FilterModel(const QString &m_name, const QString &m_color, QObject* parent=0);
public slots:
signals:
};
#endif // FILTERMODEL_H
