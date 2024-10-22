#include "pbmousehover.h"

PBMouseHover::PBMouseHover(QObject *parent) : QObject(parent)
{
}

void PBMouseHover::setButtonIcons(QIcon normalIcon,QIcon activeIcon)
{
	m_normalIcon = normalIcon;
	m_activeIcon = activeIcon;
}

bool PBMouseHover::eventFilter(QObject *watched, QEvent *event)
{
	QPushButton *button = qobject_cast<QPushButton*>(watched);
	if (!button || !button->isEnabled()) {
		return false;
	}

	if (event->type() == QEvent::Enter) {
		button->setIcon(m_activeIcon);
		return true;
	}
	else if (event->type() == QEvent::Leave){
		button->setIcon(m_normalIcon);
		return true;
	}
	return false;
}
