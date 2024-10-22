#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QComboBox>
#include <QDebug>

#include "pbmousehover.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setUpCbSex();
	setUpLeYear();
	setUpButtons();
	setUpCbStatus();

	m_diastatus = new DiaStatusDescription(this);
	m_diastatus->setUpModel(ui->cb_status->model());

	setUpConnects();
}

void MainWindow::setUpCbSex()
{
	ui->cb_sex->addItem("Мужской");
	ui->cb_sex->addItem("Женский");
	ui->cb_sex->setCurrentIndex(0);
}

void MainWindow::setUpLeYear()
{
	QRegExpValidator *validator = new QRegExpValidator(QRegExp("\\d{4}"), this);
	ui->le_year->setValidator(validator);
}

void MainWindow::setUpButtons()
{
	ui->pb_description->setIcon(QIcon(":/icons/question_mark.svg"));

	PBMouseHover *watcher_tb_description = new PBMouseHover(this);
	watcher_tb_description->setButtonIcons(QIcon(":/icons/question_mark.svg"),
									QIcon(":/icons/question_mark_active.svg"));
	ui->pb_description->installEventFilter(watcher_tb_description);
}

void MainWindow::setUpCbStatus()
{
	ui->cb_status->addItem("Соревнования спортивных организаций");
	ui->cb_status->addItem("Всероссийские соревнования");
	ui->cb_status->addItem("Всероссийс123ования");
	ui->cb_status->addItem("Всеросси13нования");
	ui->cb_status->addItem("Всерос123ревнования");

	ui->cb_status->setItemData(0, "asfasgasgjnl;ABEJKR.GRGQEBJLOU;bG;WAEJOQUOGI;BEH"
								  "JLUWuohbraegpw;ourghaeipwohuipaegrwohipae"
								  "grwjdjdhfjdkfl", Qt::WhatsThisRole);

	ui->cb_status->setItemData(1, "huipaegrwohipae"
								  "grwjdjdhfjdkfl", Qt::WhatsThisRole);

	ui->cb_status->setItemData(2, "a", Qt::WhatsThisRole);

	ui->cb_status->setItemData(3, "b", Qt::WhatsThisRole);


	ui->cb_status->model();
}

void MainWindow::setUpConnects()
{
	connect(ui->pb_description, &QPushButton::clicked,
			this, &MainWindow::slotDiaStatusExec);
;
}

void MainWindow::slotDiaStatusExec()
{
	m_diastatus->updateModel(ui->cb_status->currentIndex());
	m_diastatus->exec();
}

MainWindow::~MainWindow()
{
	delete ui;
}

