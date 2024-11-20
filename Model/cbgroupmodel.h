#ifndef CBGROUPMODEL_H
#define CBGROUPMODEL_H

#include <QAbstractListModel>
#include <QMap>

class CBGroupModel : public QAbstractListModel
{
	Q_OBJECT
public:
	struct age_group {
		int id;
		QString name;
		QString description;
	};

public:
	CBGroupModel();


public:
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;

private:
	QVector<age_group> m_groups;
};

#endif // CBSTATUSMODEL_H
