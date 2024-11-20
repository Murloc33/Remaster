#ifndef PBICONSWITCHER_H
#define PBICONSWITCHER_H

#include <QPushButton>
#include <QObject>
#include <QEvent>

class PBIconSwitcher : public QObject
{
	Q_OBJECT
public:
	explicit PBIconSwitcher(QObject *parent = nullptr);

	virtual bool eventFilter(QObject * object, QEvent * event);
	void setUpButtonIcons(QIcon disable,QIcon active);
private:
	QIcon m_disable;
	QIcon m_active;
};

#endif // PUSHBUTTONMOUSEHOVER_H
