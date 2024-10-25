#ifndef CBSTATUSMODEL_H
#define CBSTATUSMODEL_H

#include <QAbstractListModel>
#include <QMap>

class CBStatusModel : public QAbstractListModel
{
	Q_OBJECT
public:
	struct statusInfo {
		QString name;
		QString description;
	};

public:
	CBStatusModel();


public:
	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;

private:
	QMap<int, statusInfo> m_status;
};

#endif // CBSTATUSMODEL_H
