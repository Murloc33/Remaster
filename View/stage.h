#ifndef STAGE_H
#define STAGE_H

#include <QLabel>
#include <QVector>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

#include "customcombobox.h"
#include "customcheckbox.h"

class Stage : public QObject
{
	Q_OBJECT
public:
	Stage(int64_t stageNumber,
		  QVector<CustomCheckBox *> chbVector,
		  QVector<CustomComboBox *> cbVector,
		  QVector<QLineEdit *> leVector);

signals:
	void sigActivateNextStage(int64_t nextStageNumber);
	void sigClearAllNextStages(int64_t numberStage);
	void sigSendInfo(CustomComboBox *cb);

private:
	void setUpConnection();


public slots:
	void slotActivateStage();
	void slotClearStage();

private slots:
	void slotIsStageFinish();

private:
	int64_t						m_stageNumber;
	QVector<CustomCheckBox *>	m_chbVector;
	QVector<CustomComboBox *>	m_cbVector;
	QVector<QLineEdit *>		m_leVector;
};

#endif // STAGE_H
