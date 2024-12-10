#include "stage.h"

Stage::Stage(int64_t stageNumber,
			 QVector<CustomCheckBox *> chbVector,
			 QVector<CustomComboBox *> cbVector,
			 QVector<QLineEdit *> leVector)
: m_stageNumber(stageNumber)
, m_chbVector(chbVector)
, m_cbVector(cbVector)
, m_leVector(leVector)
{

	setUpConnection();

}

void Stage::setUpConnection()
{
	for (auto cb : m_cbVector) {
		connect(cb, &CustomComboBox::activated,
				[this, cb] {
					emit sigSendInfo(cb);
					slotIsStageFinish();
		});
	}
}

void Stage::slotActivateStage()
{
	for (auto cb : m_cbVector) {
		cb->fillCB();
	}

	for (auto le : m_leVector) {
		le->setEnabled(true);
	}

	for (auto chb : m_chbVector) {
		chb->setUp();
	}
}

void Stage::slotClearStage()
{
	for (auto cb : m_cbVector) {
		cb->clear();
		cb->setEnabled(false);
	}

	for (auto le : m_leVector) {
		le->setEnabled(false);
		le->clear();
	}

	for (auto chb : m_chbVector) {
		chb->setEnabled(false);
		chb->setCheckState(Qt::CheckState::Unchecked);
	}
}

void Stage::slotIsStageFinish()
{
	for (auto cb : m_cbVector) {
		if (cb->count() == 0 || cb->currentIndex() == -1) {
			return;
		}
	}

	emit sigClearAllNextStages(m_stageNumber);

	emit sigActivateNextStage(m_stageNumber + 1);
}
