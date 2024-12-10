#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>

#include "../Manager/dbmanager.h"
#include "../Model/cbmodel.h"
#include "../Manager/resultmanager.h"

class CustomComboBox : public QComboBox
{
	Q_OBJECT
public:
	CustomComboBox(QWidget *parent);
	~CustomComboBox();

	void fillCB();

//	void setDependents(QVector<CustomComboBox *> ccb);
//	void setEnables(QVector<CustomComboBox *> ccb);
	void setFilters(QVector<CustomComboBox *> filters);
	void setModel(QAbstractItemModel *model);
	void setOptionalId(int64_t optionalId);
	void setInfo(ResultManager::info info);
	void setRequest(QString request);
	void setPK(QString pk);

	DBManager::Item getCurrentItem() const;
	ResultManager::info getInfo();
	int64_t getOptionalId();
	QString getPK() const;

	size_t count();

	void clear();

private:
	bool checkFilter(DBManager::Item curItem);

private:
	QVector<CustomComboBox *>	m_filters;
	QString						m_request;
	CBModel						*m_model;
	QString						m_pk;
	ResultManager::info			m_info;
	int64_t						m_optionalId = -1;

};

#endif // CUSTOMCOMBOBOX_H
