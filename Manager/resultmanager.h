#ifndef RESULTMANAGER_H
#define RESULTMANAGER_H

#include <QMap>
#include <QLabel>
#include <QVector>
#include <QLineEdit>

#include "../Manager/dbmanager.h"

class CustomCheckBox;
class CustomComboBox;


class ResultManager : public QObject
{
	Q_OBJECT
public:
	enum info {
		age_group,
		sex,
		status,
		discipline_type,
		discipline,
		discipline_content,
		result,
		place,
		count_place
	};

	enum typeInfo {
		baseInfo,
		dependentInfo
	};

public:
	ResultManager(QLabel *result, QLabel *ms_icon, QLabel *cms_icon);

	void setCHB(QVector<CustomCheckBox *> chbVector);
	void setCB(QMap<info, CustomComboBox *> cbMap);
	void setLE(QMap<info, QLineEdit *> leMap);

public slots:
	void slotAcceptInfo();


private:
	bool checkBaseInfo();
	bool checkResult();
	bool checkPlace();
	bool checkAdditionalСriteria();
	void checkResultAnswer();
	void checkPlaceAnswer();

private:
	QLabel *m_result;
	QLabel *m_msIcon;
	QLabel *m_cmsIcon;
	QVector<CustomCheckBox *>		m_chbVector;
	QMap<info, QLineEdit *>			m_leMap;
	QMap<info, CustomComboBox *>	m_cbMap;
	QVector<DBManager::Item>		m_resultVector;
	QVector<DBManager::Item>		m_placeVector;
	bool cms = false;
	bool ms = false;
};

#endif // RESULTMANAGER_H
