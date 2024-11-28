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
#include "../Model/cbmodel.h"
#include "../Manager/dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setUpCb(AGE_GROUP_REQUEST, &m_models.ageGroupModel,
			ui->cb_age_group, &m_cb_enable.cb_age_group_enable);
	setUpCb(COMPETITION_STATUSES_REQUEST, &m_models.competitionStatusesModel,
			ui->cb_statuses, &m_cb_enable.cb_competition_statuses_enable);
	setUpCb(SEX_REQUEST, &m_models.sexModel,
			ui->cb_sex, &m_cb_enable.cb_sex_enable);
	setUpCb(DISCIPLINE_TYPES_REQUEST, &m_models.disciplineTypesModel,
			ui->cb_discipline_types, &m_cb_enable.cb_discipline_types_enable);
	setUpCb(DISCIPLINE_REQUEST, &m_models.disciplinesModel,
			ui->cb_discipline, &m_cb_enable.cb_discipline_enable);

	setUpButtons();

	m_diaDescriptionAgeGroup = new DiaDescription(this);
	m_diaDescriptionAgeGroup->setUpModel(&m_models.ageGroupModel);



	setUpConnects();
}

void MainWindow::setUpCb(QString request, CBModel *model, CustomComboBox *cb, bool *cb_state)
{
	QVector<DBManager::itemInfo> itemVecor = DBManager::instance()->getData(request);
	cb->setCBState(cb_state);
	model->addItems(itemVecor);
	cb->setModel(model);
	cb->setCurrentIndex(-1);


	connect(cb, &CustomComboBox::sigChangedState,
			this, &MainWindow::slotEnableCb);
	connect(cb, &CustomComboBox::sigChangedState,
			this, &MainWindow::slotUpdateModelCb);
}

void MainWindow::updateCb(QString request, CBModel *model, QMap<QString, QVector<int>> args)
{
	QVector<DBManager::itemInfo> itemVecor = DBManager::instance()->getDataWhere(request, args);
	for (auto item : itemVecor) {
		qDebug() << item.name;
	}
	model->updateData(itemVecor);
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
}

void MainWindow::slotDiaAgeGroupExec()
{
	m_diaDescriptionAgeGroup->updateModel(ui->cb_age_group->currentIndex());
	m_diaDescriptionAgeGroup->exec();
}

void MainWindow::slotEnableCb()
{
	if (!ui->cb_discipline_types->isEnabled()) {
		if (m_cb_enable.cb_sex_enable
		&& m_cb_enable.cb_competition_statuses_enable
		&& m_cb_enable.cb_age_group_enable) {
			ui->cb_discipline_types->setEnabled(true);
		}
		return;
	}

	if (!ui->cb_discipline->isEnabled()) {
		if (m_cb_enable.cb_discipline_types_enable) {
			ui->cb_discipline->setEnabled(true);
		}
		return;
	}


}

void MainWindow::slotUpdateModelCb()
{
	QObject *sender = QObject::sender();
	if (ui->cb_discipline->isEnabled() && sender->objectName() != ui->cb_discipline->objectName()) {
		QMap<QString, QVector<int>> args;
		int sexIndex = ui->cb_sex->currentIndex();
		args.insert("sex_id", QVector<int> {m_models.sexModel.getItem(sexIndex)["id"], 3});

		int disciplineTypeIndex = ui->cb_discipline_types->currentIndex();
		args.insert("discipline_type_id", QVector<int> {m_models.disciplineTypesModel.getItem(disciplineTypeIndex)["id"]});

		updateCb(DISCIPLINE_REQUEST, &m_models.disciplinesModel, args);
		ui->cb_discipline->setCurrentIndex(-1);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

