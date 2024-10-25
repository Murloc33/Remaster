#include "dbmanager.h"

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

QMap<int, CBStatusModel::statusInfo> DBManager::getStatus()
{
	QMap<int, CBStatusModel::statusInfo> result;
	QSqlQuery query("SELECT * FROM competition_statuses ORDER BY id");
	query.exec();
	while (query.next()) {
		int id = query.value("id").toInt();
		QString name = query.value("name").toString();
		QString status = query.value("description").toString();
		result.insert(id, {name, status});
	}

	return result;
}

QList<QString> DBManager::getDisciplines()
{
	QMap<int, QString> result;
	QSqlQuery query("SELECT * FROM disciplines");
	query.exec();
	while(query.next()) {
		int id = query.value("id").toInt();
		QString name = query.value("name").toString();
		result.insert(id, name);
	}
}
