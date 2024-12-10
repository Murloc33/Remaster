#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QStandardItemModel>
#include <QStringBuilder>
#include <QSqlDatabase>
#include <QMetaObject>
#include <QComboBox>
#include <QVariant>
#include <QDebug>

#include "Delegate/pbiconswitcher.h"
#include "Dialog/diadescription.h"
#include "../Manager/dbmanager.h"
#include "../Manager/stagemanager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setUpAllCB();
	setUpAllCHB();
	setUpAllStage();
	setUpButtons();
	setUpManager();

	m_diaDescriptionAgeGroup = new DiaDescription(this);
//	m_diaDescriptionAgeGroup->setUpModel(&m_ageGroupModel);

	setUpConnects();
}



void MainWindow::setUpButtons()
{
	ui->pb_age_group_description->setIcon(QIcon(":/icons/question_mark.svg"));

	PBIconSwitcher *pb_year_group = new PBIconSwitcher(this);
	pb_year_group->setUpButtonIcons(QIcon(":/icons/question_mark.svg"),
									QIcon(":/icons/question_mark_active.svg"));
	ui->pb_age_group_description->installEventFilter(pb_year_group);
}

void MainWindow::setUpConnects()
{
	connect(ui->pb_age_group_description, &QPushButton::clicked,
			this, &MainWindow::slotDiaAgeGroupExec);
	connect(ui->cb_discipline_types, &CustomComboBox::currentIndexChanged,
			this, [this] {
		ui->cb_discipline->model()->sort(0);
	});
}

void MainWindow::slotDiaAgeGroupExec()
{
	m_diaDescriptionAgeGroup->updateModel(ui->cb_age_group->currentIndex());
//	m_diaDescriptionAgeGroup->exec();
}


MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setUpAllCB()
{
	setUpCB(AGE_GROUP_REQUEST, ui->cb_age_group, "age_group_id", {}, 7);
	ui->cb_age_group->fillCB();
	setUpCB(COMPETITION_STATUSES_REQUEST, ui->cb_statuses, "competition_status_id", {}, -1);
	ui->cb_statuses->fillCB();
	setUpCB(SEX_REQUEST, ui->cb_sex, "sex_id", {}, 3);
	ui->cb_sex->fillCB();
	setUpCB(DISCIPLINE_TYPES_REQUEST, ui->cb_discipline_types, "discipline_type_id", {}, -1);
	setUpCB(DISCIPLINE_REQUEST, ui->cb_discipline, "discipline_id", {ui->cb_sex, ui->cb_discipline_types}, -1);
	setUpCB(DISCIPLINE_CONTENTS_REQUEST, ui->cb_discipline_content, "discipline_content_id",
			{ui->cb_discipline, ui->cb_sex,ui->cb_age_group}, -1);
}

void MainWindow::setUpCB(QString request, CustomComboBox *cb, QString pk, QVector<CustomComboBox *> filters, int64_t optionalId)
{
	cb->setRequest(request);
	CBModel *model = new CBModel();
	cb->setOptionalId(optionalId);
	cb->setModel(model);
	cb->setFilters(filters);
	cb->setPK(pk);
}

void MainWindow::setUpAllStage()
{
	QVector<Stage *> stages;
	Stage *firstStage = setUpStage(0, {}, {ui->cb_age_group, ui->cb_sex, ui->cb_statuses}, {});
	stages.push_back(firstStage);
	Stage *secondStage = setUpStage(1, {}, {ui->cb_discipline_types}, {});
	stages.push_back(secondStage);
	Stage *thirdStage = setUpStage(2, {}, {ui->cb_discipline}, {});
	stages.push_back(thirdStage);
	Stage *fourthStage = setUpStage(3, {ui->chb_windy_speed, ui->chb_years_old}, {ui->cb_discipline_content}, {ui->le_result});
	stages.push_back(fourthStage);
	m_stageManager.setSatges(stages);
}

Stage *MainWindow::setUpStage(int64_t stageNumber,
							  QVector<CustomCheckBox *> chbVector,
							  QVector<CustomComboBox *> cbVector,
							  QVector<QLineEdit *> leVector)
{
	Stage * result = new Stage(stageNumber, chbVector, cbVector, leVector);
	return result;
}

void MainWindow::setUpCHB(CustomCheckBox *chb, CustomComboBox *cb, QVector<int64_t> idVector)
{
	chb->setFilter({cb, idVector});
}

void MainWindow::setUpAllCHB()
{
	setUpCHB(ui->chb_years_old, ui->cb_age_group, {3});
	setUpCHB(ui->chb_windy_speed, ui->cb_age_group, {});
}

void MainWindow::setUpManager()
{
	m_resultManager = new ResultManager(ui->l_result, ui->pm_ms, ui->pm_cms);

	connect(ui->cb_age_group, &CustomComboBox::activated,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->cb_sex, &CustomComboBox::activated,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->cb_statuses, &CustomComboBox::activated,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->cb_discipline_types, &CustomComboBox::activated,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->cb_discipline, &CustomComboBox::activated,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->cb_discipline_content, &CustomComboBox::activated,
			m_resultManager, &ResultManager::slotAcceptInfo);

	connect(ui->chb_windy_speed, &CustomCheckBox::stateChanged,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->chb_years_old, &CustomCheckBox::stateChanged,
			m_resultManager, &ResultManager::slotAcceptInfo);

	connect(ui->le_count_place, &QLineEdit::textChanged,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->le_place, &QLineEdit::textChanged,
			m_resultManager, &ResultManager::slotAcceptInfo);
	connect(ui->le_result, &QLineEdit::textChanged,
			m_resultManager, &ResultManager::slotAcceptInfo);



	QMap<ResultManager::info, CustomComboBox *> cbMap;
	cbMap.insert(ResultManager::info::age_group, ui->cb_age_group);
	cbMap.insert(ResultManager::info::sex, ui->cb_sex);
	cbMap.insert(ResultManager::info::status, ui->cb_statuses);
	cbMap.insert(ResultManager::info::discipline_type, ui->cb_discipline_types);
	cbMap.insert(ResultManager::info::discipline, ui->cb_discipline);
	cbMap.insert(ResultManager::info::discipline_content, ui->cb_discipline_content);
	m_resultManager->setCB(cbMap);
	m_resultManager->setCHB({ui->chb_windy_speed, ui->chb_years_old});

	QMap<ResultManager::info, QLineEdit *> leMap;
	leMap.insert(ResultManager::result, ui->le_result);
	leMap.insert(ResultManager::place, ui->le_place);
	leMap.insert(ResultManager::count_place, ui->le_count_place);
	m_resultManager->setLE(leMap);
}



