#ifndef DIASTATUSDESCRIPTION_H
#define DIASTATUSDESCRIPTION_H

#include <QAbstractItemModel>
#include <QDialog>

namespace Ui {
	class DiaStatusDescription;
}


class DiaStatusDescription : public QDialog
{
	Q_OBJECT
public:
	DiaStatusDescription(QWidget *parent = nullptr);
	void setUpModel(QAbstractItemModel* model);
	void updateModel(int index);

private slots:
	void slotUpdateLDescription(int index);


private:
	Ui::DiaStatusDescription* ui;
	QAbstractItemModel* m_model;
};

#endif // DIASTATUSDESCRIPTION_H
