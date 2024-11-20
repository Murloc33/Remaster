#include "cbgroupmodel.h"

#include "../Manager/dbmanager.h"

CBGroupModel::CBGroupModel()
{
	m_groups = DBManager::instance()->getAgeGroup();
}

int CBGroupModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return m_groups.size();
}

QVariant CBGroupModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	int row = index.row();

	if (role == Qt::DisplayRole) {
		return QVariant(m_groups[row].name);
	}

	if (role == Qt::WhatsThisRole) {
		return QVariant(m_groups[row].description);
	}

	if (role == Qt::StatusTipRole) {
		return QVariant(m_groups[row]);
	}

	return QVariant();
}
