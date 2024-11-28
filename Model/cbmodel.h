#ifndef CBMODEL_H
#define CBMODEL_H

#include <QAbstractListModel>

#include "../Manager/dbmanager.h"

class CBModel : public QAbstractListModel
{
public:
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	void addItems(QVector<DBManager::itemInfo> items);
	void updateData(QVector<DBManager::itemInfo> items);
	QMap<QString, int> getItem(int index);

private:
	QVector<DBManager::itemInfo> m_items;
};

#endif // CBMODEL_H
