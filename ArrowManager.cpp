#include "ArrowManager.h"

ArrowManager::ArrowManager(QWidget* parent) : QObject(parent) { m_parent = parent; }

ArrowManager::~ArrowManager() {}

void ArrowManager::addArrow() {
  int pointX = m_parent->width() / 2;
  int pointY = m_parent->height() / 2;

  GlobalParam::Global_X = pointX;
  GlobalParam::Global_Y = pointY;

  m_curArrow = new Arrow(m_parent);
  connect(m_curArrow, &Arrow::sigPressArrow, this, &ArrowManager::onPressArrow);
  m_curArrow->move(pointX - m_curArrow->rect().width() / 2, pointY - m_curArrow->rect().height() / 2);
  m_curArrow->show();
}

void ArrowManager::changeWorkStatus() {
  if (!m_workStatus) {
    addArrow();

    m_workStatus = true;
  } else {
    delete m_curArrow;
    m_curArrow = nullptr;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    m_workStatus = false;
  }
}

void ArrowManager::setArrowAngle(const int& value) {
  if (m_curArrow != nullptr) {
    m_curArrow->setAngleIdx(value);
  }
}

void ArrowManager::setArrowSolid(const int& value) {
  if (m_curArrow != nullptr) {
    m_curArrow->setSolidIdx(value);
  }
}

void ArrowManager::setArrowFixedColor(const int& value) {
  if (m_curArrow != nullptr) {
    m_curArrow->setFixedColorIdx(value);
  }
}

void ArrowManager::setArrowSize(const int& value) {
  if (m_curArrow != nullptr) {
    m_curArrow->setSizeIdx(value);
  }
}

void ArrowManager::mouseMove(const QPoint& wdgPt) {
  GlobalParam::Global_X = wdgPt.x();
  GlobalParam::Global_Y = wdgPt.y();

  if (m_curArrow != nullptr) {
    QApplication::setOverrideCursor(Qt::BlankCursor);
    m_curArrow->move(wdgPt.x() - m_curArrow->rect().width() / 2, wdgPt.y() - m_curArrow->rect().height() / 2);
  }
}

void ArrowManager::onPressArrow(Arrow* curArrow) {
  if (m_curArrow == curArrow) {
    if (m_curArrowList.size() < m_arrowMaxCount) {
      m_curArrow->setStatus(1);
      m_curArrowList.append(m_curArrow);
      addArrow();
    }
  }
}
