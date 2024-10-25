#include "cbstatusmodel.h"

#include <dbmanager.h>

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

	int row = index.row() + 1;

	if (role == Qt::DisplayRole) {
		return QVariant(m_status[row].name);
	}

	if (role == Qt::WhatsThisRole) {
		return QVariant(m_status[row].description);
	}

	return QVariant();
}
