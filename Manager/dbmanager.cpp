#include "dbmanager.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QMap>

DBManager::DBManager()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("./remaster.db");
	m_db.open();
}

DBManager *DBManager::instance()
{
	static DBManager manager;
	return &manager;
}

QVector<DBManager::itemInfo> DBManager::getData(QString request)
{
	QVector<DBManager::itemInfo> result;
	QSqlQuery query(request);

	query.exec();
	QSqlRecord rec = query.record();

	bool isDescription = checkDescription(rec);

	while(query.next()) {
		DBManager::itemInfo currentStruct;

		currentStruct.name = query.value("name").toString();

		if (isDescription) {
			currentStruct.description = query.value("description").toString();
		}

		for (int i = 0; i < rec.count(); ++i) {
			QString key = rec.fieldName(i);
			if (key == "name" || key == "description") {
				continue;
			}

			int value = query.value(key).toInt();
			currentStruct.otherInfo.insert(key, value);
		}

		result.push_back(currentStruct);
	}
	return result;
}

bool DBManager::checkDescription(QSqlRecord &rec)
{
	for (int i = 0; i < rec.count(); ++i) {
		if (rec.fieldName(i) == "description") {
			return true;
		}
	}

	return false;
}
