#include "cardlistviewsqlquerymodel.h"

QVariant CardListViewSqlQueryModel::data(const QModelIndex &index, int role) const
{
    if (role == 150)
    {
        QModelIndex indexRighter = index.siblingAtColumn(index.column()+1);
        return QSqlQueryModel::data(indexRighter, Qt::DisplayRole);
    }
    else return QSqlQueryModel::data(index, role);
}

QHash<int, QByteArray> CardListViewSqlQueryModel::roleNames() const
{
  //  QHash<int, QByteArray> mappings = QSqlQueryModel::roleNames();
  //  mappings.insert(150, "description");


    static QHash<int, QByteArray> map{
        {Qt::DisplayRole, "display"},
        {150, "description"}
    };

    return map;
}
