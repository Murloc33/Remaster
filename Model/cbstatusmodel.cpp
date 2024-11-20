#include "cbstatusmodel.h"

#include "../Manager/dbmanager.h"

CBStatusModel::CBStatusModel()
{
	m_status = DBManager::instance()->getStatus();
}

int CBStatusModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return m_status.count();
}

QVariant CBStatusModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	int row = index.row();

	if (role == Qt::DisplayRole) {
		return QVariant(m_status[row].name);
	}

	return QVariant();
}
