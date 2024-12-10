#include "stagemanager.h"

StageManager::StageManager()
{

}

void StageManager::setSatges(QVector<Stage *> stages)
{
	m_stages = stages;
	setUpConnection();
}

void StageManager::setUpConnection()
{
	for (int i = 0; i < m_stages.size(); ++i) {
		connect(m_stages[i], &Stage::sigActivateNextStage,
				this, &StageManager::slotActivateStage);
	}

	for (int i = 0; i < m_stages.size(); ++i) {
		connect(m_stages[i], &Stage::sigClearAllNextStages,
				this, &StageManager::slotClearAllNextStages);
	}
}

void StageManager::slotActivateStage(int64_t stageNumber)
{
	if (stageNumber == m_stages.size()) {
		return;
	}
	m_stages[stageNumber]->slotActivateStage();
}

void StageManager::slotClearAllNextStages(int64_t stageNumber)
{
	for (int i = m_stages.size() - 1; i > stageNumber; --i) {
		m_stages[i]->slotClearStage();
	}
}
