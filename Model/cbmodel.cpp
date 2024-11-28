#include "cbmodel.h"

int CBModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return m_items.size();
}

QVariant CBModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	int row = index.row();

	if (role == Qt::DisplayRole) {
		return QVariant(m_items[row].name);
	}

	if (role == Qt::WhatsThisRole) {
		return QVariant(m_items[row].description);
	}

	return QVariant();
}

void CBModel::addItems(QVector<DBManager::itemInfo> items)
{
	beginResetModel();
	m_items = items;
	endResetModel();
}

void CBModel::updateData(QVector<DBManager::itemInfo> items)
{
	beginResetModel();
	m_items.clear();
	addItems(items);
	endResetModel();
}

QMap<QString, int> CBModel::getItem(int index)
{
	return m_items[index].otherInfo;
}
