#include "filtermodel.h"

FilterModel::FilterModel(QObject *parent){

}

FilterModel::FilterModel(const QString &m_name, const QString &m_color, QObject *parent){
    setColor(m_color);
    setName(m_name);
}
