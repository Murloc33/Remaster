#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <QObject>

#include "../View/customcombobox.h"
#include "../View/stage.h"

class StageManager : public QObject
{
	Q_OBJECT
public:
	StageManager();

	void setSatges(QVector<Stage *> stages);

private:
	void setUpConnection();

public slots:
	void slotActivateStage(int64_t stageNumber);
	void slotClearAllNextStages(int64_t stageNumber);

private:
	QVector<Stage *> m_stages;
};

#endif // STAGEMANAGER_H
