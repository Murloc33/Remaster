#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QMap>

#define AGE_GROUP_REQUEST "SELECT * FROM age_groups"
#define COMPETITION_STATUSES_REQUEST "SELECT * FROM competition_statuses"
#define SEX_REQUEST "SELECT * FROM sex WHERE id IN (1,2)"
#define DISCIPLINE_TYPES_REQUEST "SELECT * FROM discipline_types"
#define DISCIPLINE_REQUEST "SELECT * FROM disciplines"
#define DISCIPLINE_CONTENTS "SELECT discipline_contents.id, discipline_contents.name FROM based_on_result_records INNER JOIN discipline_contents ON discipline_contents.id = based_on_result_records.discipline_content_id"

class DBManager
{
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
	QVector<itemInfo> getDataWhere(QString request, QMap<QString, QVector<int>> args);
	bool checkDescription(QSqlRecord &rec);

private:
	DBManager();

private:
	template<typename data>
	QVariant fillStruct(QSqlQuery &query);

private:
	QSqlDatabase m_db;
};

#endif // DBMANAGER_H
