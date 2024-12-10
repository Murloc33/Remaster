#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include "Dialog/diadescription.h"
#include "../Model/cbmodel.h"
#include "../View/stage.h"
#include "../Manager/stagemanager.h"
#include "../Manager/resultmanager.h"
#include "customcombobox.h"
#include "customcheckbox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);

	~MainWindow();

private:
	void setUpAllCB();
	void setUpCB(QString request, CustomComboBox *cb, QString pk,
				QVector<CustomComboBox *> filters, int64_t optionalId);

	void setUpAllStage();
	Stage *setUpStage(int64_t stageNumber,
					  QVector<CustomCheckBox *> chbVector,
					  QVector<CustomComboBox *> cbVector,
					  QVector<QLineEdit *> leVector);

	void setUpCHB(CustomCheckBox *chb, CustomComboBox *cb, QVector<int64_t> idVector);
	void setUpAllCHB();

	void setUpManager();
	void setUpButtons();
	void setUpConnects();

private slots:
	void slotDiaAgeGroupExec();

private:
	Ui::MainWindow			*ui;

	StageManager			m_stageManager;
	DiaDescription			*m_diaDescriptionAgeGroup;
	ResultManager			*m_resultManager;

};
#endif // MAINWINDOW_H
