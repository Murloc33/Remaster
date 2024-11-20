#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include "Dialog/diadescription.h"
#include "../Model/cbmodel.h"

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
	void setUpCb(QString request, CBModel *model, QComboBox *cb);
	void setUpButtons();
	void setUpConnects();

private slots:
	void slotDiaAgeGroupExec();
	void slotSetEnabledCbDiscilpine(int index);

private:
	Ui::MainWindow			*ui;

	struct {
		bool cb_age_group_enable;
		bool cb_sex_enable;
		bool cb_competition_statuses_enable;
	} m_cb_enable;

	struct {
		CBModel ageGroupModel;
		CBModel competitionStatusesModel;
		CBModel sexModel;
	} m_models;

	DiaDescription			*m_diaDescriptionAgeGroup;

};
#endif // MAINWINDOW_H
