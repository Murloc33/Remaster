#include "resultmanager.h"

#include "../View/customcheckbox.h"
#include "../View/customcombobox.h"

ResultManager::ResultManager(QLabel *result, QLabel *ms_icon, QLabel *cms_icon)
: m_result(result)
, m_msIcon(ms_icon)
, m_cmsIcon(cms_icon)
{
	m_placeVector = DBManager::instance()->getData(PLACE_REQUEST);
	m_resultVector = DBManager::instance()->getData(RESULT_REQUEST);
	qDebug() << m_placeVector.size();
	qDebug() << m_resultVector.size();
}

void ResultManager::setCHB(QVector<CustomCheckBox *> chbVector)
{
	m_chbVector = chbVector;
}

void ResultManager::setCB(QMap<info, CustomComboBox *> cbMap)
{
	m_cbMap = cbMap;
}

void ResultManager::setLE(QMap<info, QLineEdit *> leMap)
{
	m_leMap = leMap;
}

void ResultManager::slotAcceptInfo()
{
	ms = false;
	cms = false;
	m_cmsIcon->setPixmap(QPixmap(":/icons/remove.svg"));
	m_msIcon->setPixmap(QPixmap(":/icons/remove.svg"));
	if (!checkBaseInfo()) {
		return;
	}

	if (checkAdditionalСriteria()) {
		if (checkResult()) {
			checkResultAnswer();
			if (ms && cms) {
				return;
			}
		}
		if (checkPlace()) {
			checkPlaceAnswer();
		}
	} else {
		m_cmsIcon->setPixmap(QPixmap(":/icons/remove.svg"));
		m_msIcon->setPixmap(QPixmap(":/icons/remove.svg"));
	}

}

bool ResultManager::checkBaseInfo()
{
	return m_cbMap[ResultManager::age_group]->currentIndex() != -1
		&& m_cbMap[ResultManager::sex]->currentIndex() != -1
		&& m_cbMap[ResultManager::status]->currentIndex() != -1
		&& m_cbMap[ResultManager::discipline_type]->currentIndex() != -1
		&& m_cbMap[ResultManager::discipline]->currentIndex() != -1;
}

bool ResultManager::checkResult()
{
	return !m_leMap[ResultManager::result]->text().isEmpty()
		&& (!m_cbMap[ResultManager::discipline_content]->isEnabled()
		|| m_cbMap[ResultManager::discipline_content]->currentIndex() != -1);
}

bool ResultManager::checkPlace()
{
	return !m_leMap[ResultManager::place]->text().isEmpty()
			&& !m_leMap[ResultManager::count_place]->text().isEmpty();
}

bool ResultManager::checkAdditionalСriteria()
{
	for (int i = 0; i < m_chbVector.size(); ++i) {
		if (m_chbVector[i]->isEnabled()) {
			if (m_chbVector[i]->isChecked()) {
				continue;
			} else {
				return false;
			}
		}
	}
	return true;
}

void ResultManager::checkResultAnswer()
{
	QVector<DBManager::Item> filterVector;
	for (int i = 0; i < m_resultVector.size(); ++i) {

		if (!(m_cbMap[ResultManager::age_group]->getCurrentItem().id == m_resultVector[i].baseItemsId[m_cbMap[ResultManager::age_group]->getPK()]
		||  m_cbMap[ResultManager::age_group]->getOptionalId() == m_resultVector[i].baseItemsId[m_cbMap[ResultManager::age_group]->getPK()])) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}

		if (!(m_cbMap[ResultManager::sex]->getCurrentItem().id == m_resultVector[i].baseItemsId[m_cbMap[ResultManager::sex]->getPK()]
		||  m_cbMap[ResultManager::sex]->getOptionalId() == m_resultVector[i].baseItemsId[m_cbMap[ResultManager::sex]->getPK()])) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}


		if (m_cbMap[ResultManager::discipline]->getCurrentItem().id != m_resultVector[i].baseItemsId[m_cbMap[ResultManager::discipline]->getPK()]) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}


		if (m_cbMap[ResultManager::discipline_content]->isEnabled()) {
			if (m_cbMap[ResultManager::discipline_content]->getCurrentItem().id != m_resultVector[i].baseItemsId[m_cbMap[ResultManager::discipline_content]->getPK()]) {
				m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
				m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
				continue;
			}
		}


		if (m_leMap[ResultManager::result]->text().toInt() >= m_resultVector[i].otherInformation["min_result"]) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}
		filterVector.push_back(m_resultVector[i]);
	}



	for (auto item : filterVector) {
		if (ms) {
			break;
		}
		if (item.baseItemsId["sport_category_id"] == 1) {

			m_msIcon->setPixmap(QPixmap(":/icons/done.svg"));
			ms = true;
			break;
		}
		m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
	}

	for (auto item : filterVector) {
		if (cms) {
			break;
		}
		if (item.baseItemsId["sport_category_id"] == 2) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/done.svg"));
			cms = true;
			break;
		}
		m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
	}
}

void ResultManager::checkPlaceAnswer()
{
	QVector<DBManager::Item> filterVector;
	for (int i = 0; i < m_placeVector.size(); ++i) {

		if (!(m_cbMap[ResultManager::age_group]->getCurrentItem().id == m_placeVector[i].baseItemsId[m_cbMap[ResultManager::age_group]->getPK()]
		||  m_cbMap[ResultManager::age_group]->getOptionalId() == m_placeVector[i].baseItemsId[m_cbMap[ResultManager::age_group]->getPK()])) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}

		if (m_cbMap[ResultManager::status]->getCurrentItem().id >= m_placeVector[i].baseItemsId[m_cbMap[ResultManager::status]->getPK()]) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}
		qDebug() << m_cbMap[ResultManager::discipline]->getCurrentItem().id << m_placeVector[i].baseItemsId[m_cbMap[ResultManager::discipline]->getPK()];
		if (m_cbMap[ResultManager::discipline]->getCurrentItem().id != m_placeVector[i].baseItemsId[m_cbMap[ResultManager::discipline]->getPK()]) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}
		qDebug() << "I was here";

		if (m_leMap[ResultManager::place]->text().toInt() >= m_placeVector[i].otherInformation["place_from"]
		&&  m_leMap[ResultManager::place]->text().toInt() <= m_placeVector[i].otherInformation["place_by"]) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}

		if (m_leMap[ResultManager::count_place]->text().toInt() >= m_placeVector[i].otherInformation["min_count_participants"]) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
			m_msIcon->setPixmap(QPixmap(":/icons/close.svg"));
			continue;
		}
		filterVector.push_back(m_placeVector[i]);
	}


	qDebug() << filterVector.size();

	for (auto item : filterVector) {
		if (ms) {
			break;
		}
		if (item.baseItemsId["sport_category_id"] == 1) {
			m_msIcon->setPixmap(QPixmap(":/icons/done.svg"));
			ms = true;
			break;
		}
		m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
	}

	for (auto item : filterVector) {
		if (cms) {
			break;
		}
		if (item.baseItemsId["sport_category_id"] == 2) {
			m_cmsIcon->setPixmap(QPixmap(":/icons/done.svg"));
			cms = true;
			break;
		}
		m_cmsIcon->setPixmap(QPixmap(":/icons/close.svg"));
	}
}



