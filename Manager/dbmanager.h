#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QMap>

#define AGE_GROUP_REQUEST "SELECT * FROM age_groups"
#define COMPETITION_STATUSES_REQUEST "SELECT * FROM competition_statuses"
#define SEX "SELECT * FROM sex"

class DBManager
{
private:
	DBManager();

public:

	struct itemInfo
	{
		QString name;
		QString description = "";
		QMap<QString, int> otherInfo;
	};

public:
	static DBManager *instance();

	QVector<itemInfo> getData(QString request);

	bool checkDescription(QSqlRecord &rec);

private:
	template<typename data>
	QVariant fillStruct(QSqlQuery &query);

private:
	QSqlDatabase m_db;
};

#endif // DBMANAGER_H
