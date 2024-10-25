#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

#include "cbstatusmodel.h"

class DBManager
{
private:
	DBManager();

public:
	static DBManager *instance();
	QMap<int, CBStatusModel::statusInfo> getStatus();
	QList<QString> getDisciplines();

private:
	QSqlDatabase m_db;
};

#endif // DBMANAGER_H
