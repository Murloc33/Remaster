#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QComboBox>
#include <QDebug>
#include <QVariant>


#include "Delegate/pbiconswitcher.h"
#include "Dialog/diadescription.h"
#include "../Model/cbmodel.h"
#include "../Manager/dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setUpCb(AGE_GROUP_REQUEST, &m_models.ageGroupModel, ui->cb_age_group);
	setUpCb(COMPETITION_STATUSES_REQUEST, &m_models.competitionStatusesModel, ui->cb_statuses);
	setUpCb(SEX, &m_models.sexModel, ui->cb_sex);

	setUpButtons();

	m_diaDescriptionAgeGroup = new DiaDescription(this);
	m_diaDescriptionAgeGroup->setUpModel(&m_models.ageGroupModel);



	setUpConnects();
}

void MainWindow::setUpCb(QString request, CBModel *model, QComboBox *cb)
{
	QVector<DBManager::itemInfo> itemVecor = DBManager::instance()->getData(request);
	model->addItems(itemVecor);
	cb->setModel(model);
	cb->setCurrentIndex(-1);
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

	connect(ui->cb_sex, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotSetEnabledCbDiscilpine(int)));
	connect(ui->cb_type, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotSetEnabledCbDiscilpine(int)));
}


void MainWindow::slotDiaAgeGroupExec()
{
	m_diaDescriptionAgeGroup->updateModel(ui->cb_age_group->currentIndex());
	m_diaDescriptionAgeGroup->exec();
}



void MainWindow::slotSetEnabledCbDiscilpine(int index)
{
	Q_UNUSED(index)
	if (ui->cb_type->currentIndex() != -1 && ui->cb_sex->currentIndex() != -1)
	{
		ui->cb_discipline->setEnabled(true);
	} else {
		ui->cb_discipline->setEnabled(false);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

