#include "cbmodel.h"

CBModel::CBModel()
{

}

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
		return  QVariant(m_items[row].description);
	}

	return QVariant();
}

void CBModel::addItems(QVector<DBManager::Item> items)
{
	beginResetModel();
	m_items = items;
	endResetModel();
}

void CBModel::updateData(QVector<DBManager::Item> items)
{
	beginResetModel();
	m_items.clear();
	addItems(items);
	endResetModel();
}

size_t CBModel::count()
{
	return m_items.size();
}

void CBModel::clear()
{
	beginResetModel();
	m_items.clear();
	endResetModel();
}

DBManager::Item CBModel::getItem(int index) const
{
	return m_items[index];
}
