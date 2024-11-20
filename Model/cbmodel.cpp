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

	if (role == Qt::StatusTipRole) {
		return QVariant::fromValue<QMap<QString,int>>(m_items[row].otherInfo);
	}

	return QVariant();
}

void CBModel::addItems(QVector<DBManager::itemInfo> items)
{
	m_items = items;
}
