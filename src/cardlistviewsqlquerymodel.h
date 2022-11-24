#ifndef CARDLISTVIEWSQLQUERYMODEL_H
#define CARDLISTVIEWSQLQUERYMODEL_H

#include <QtSql/QSqlQueryModel>

class CardListViewSqlQueryModel: public QSqlQueryModel
{

public:

    using QSqlQueryModel::data;
    QVariant data(const QModelIndex &index, int role) const override;
    using QSqlQueryModel::roleNames;
    QHash<int, QByteArray> roleNames() const override;

};

#endif // CARDLISTVIEWSQLQUERYMODEL_H
