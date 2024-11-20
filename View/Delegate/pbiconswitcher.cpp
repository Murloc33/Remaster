#include "pbiconswitcher.h"

PBIconSwitcher::PBIconSwitcher(QObject *parent) : QObject(parent)
{
}

void PBIconSwitcher::setUpButtonIcons(QIcon disable,QIcon active)
{
	m_disable = disable;
	m_active = active;
}

bool PBIconSwitcher::eventFilter(QObject *object, QEvent *event)
{
	QPushButton *pb = qobject_cast<QPushButton*>(object);
	if (!pb || !pb->isEnabled()) {
		return false;
	}

	if (event->type() == QEvent::Enter) {
		pb->setIcon(m_active);
		return true;
	}

	else if (event->type() == QEvent::Leave){
		pb->setIcon(m_disable);
		return true;
	}

	return false;
}
