#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include "Dialog/diadescription.h"
#include "../Model/cbmodel.h"
#include "customcombobox.h"

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
	void setUpCb(QString request, CBModel *model, CustomComboBox *cb, bool *cb_state);
	void updateCb(QString request, CBModel *model, QMap<QString, QVector<int>> args);
	void setUpButtons();
	void setUpConnects();
	QString getDisciplineRequest();


private slots:
	void slotDiaAgeGroupExec();
	void slotEnableCb();
	void slotUpdateModelCb();

private:
	Ui::MainWindow			*ui;

	struct {
		bool cb_age_group_enable = false;
		bool cb_competition_statuses_enable = false;
		bool cb_sex_enable = false;
		bool cb_discipline_types_enable = false;
		bool cb_discipline_enable = false;
	} m_cb_enable;

	struct {
		CBModel ageGroupModel;
		CBModel competitionStatusesModel;
		CBModel sexModel;
		CBModel disciplineTypesModel;
		CBModel disciplinesModel;
	} m_models;

	DiaDescription			*m_diaDescriptionAgeGroup;

};
#endif // MAINWINDOW_H
