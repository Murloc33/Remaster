#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QComboBox>
#include <QDebug>


#include "cbstatusmodel.h"
#include "pbiconswitcher.h"
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setUpCbSex();
	setUpLeYear();
	setUpButtons();
	setUpCbStatus();
	setUpInfDiscipline();

	m_diastatus = new DiaStatusDescription(this);
	m_diastatus->setUpModel(ui->cb_status->model());

	setUpConnects();
}

void MainWindow::setUpCbSex()
{
	ui->cb_sex->addItem("Мужской");
	ui->cb_sex->addItem("Женский");
}

void MainWindow::setUpLeYear()
{
	QRegExpValidator *validator = new QRegExpValidator(QRegExp("\\d{4}"), this);
	ui->le_year->setValidator(validator);
}

void MainWindow::setUpButtons()
{
	ui->pb_description->setIcon(QIcon(":/icons/question_mark.svg"));

	PBIconSwitcher *pb_description = new PBIconSwitcher(this);
	pb_description->setUpButtonIcons(QIcon(":/icons/question_mark.svg"),
									QIcon(":/icons/question_mark_active.svg"));
	ui->pb_description->installEventFilter(pb_description);
}

void MainWindow::setUpCbStatus()
{
	m_statusmodel = new CBStatusModel();
	ui->cb_status->setModel(m_statusmodel);
	ui->cb_status->setCurrentIndex(-1);
}

void MainWindow::setUpConnects()
{
	connect(ui->pb_description, &QPushButton::clicked,
			this, &MainWindow::slotDiaStatusExec);

	connect(ui->cb_sex, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotSetEnabledCbDiscilpine(int)));
	connect(ui->cb_type, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotSetEnabledCbDiscilpine(int)));
}

void MainWindow::setUpInfDiscipline()
{
	ui->cb_type->addItem("asfassg");
	ui->cb_type->setCurrentIndex(-1);
}

void MainWindow::slotDiaStatusExec()
{
	m_diastatus->updateModel(ui->cb_status->currentIndex());
	m_diastatus->exec();
}



void MainWindow::slotSetEnabledCbDiscilpine(int index)
{
	Q_UNUSED(index)
	if (ui->cb_type->currentIndex() != -1 && ui->cb_sex->currentIndex() != -1)
	{
		ui->l_discipline->setEnabled(true);
		ui->cb_discipline->setEnabled(true);
	} else {
		ui->l_discipline->setEnabled(false);
		ui->cb_discipline->setEnabled(false);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

