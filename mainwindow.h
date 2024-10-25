#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "diastatusdescription.h"
#include "cbstatusmodel.h"

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
	void setUpCbSex();
	void setUpLeYear();
	void setUpButtons();
	void setUpCbStatus();
	void setUpConnects();
	void setUpInfDiscipline();

private slots:
	void slotDiaStatusExec();
	void slotSetEnabledCbDiscilpine(int index);

private:
	Ui::MainWindow			*ui;
	DiaStatusDescription	*m_diastatus;
	CBStatusModel			*m_statusmodel;

};
#endif // MAINWINDOW_H
