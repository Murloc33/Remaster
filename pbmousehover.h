#ifndef PBMOUSEHOVER_H
#define PBMOUSEHOVER_H

#include <QPushButton>
#include <QObject>
#include <QEvent>

/****************************************************************
	Для изменения иконки при наведении курсора на QPushButton
****************************************************************/

class PBMouseHover : public QObject
{
	Q_OBJECT
public:
	explicit PBMouseHover(QObject *parent = nullptr);

	virtual bool eventFilter(QObject * watched, QEvent * event);
	void setButtonIcons(QIcon normalIcon,QIcon activeIcon);
private:
	QIcon m_normalIcon;
	QIcon m_activeIcon;
};

#endif // PUSHBUTTONMOUSEHOVER_H
