#include "ArrowManager.h"

ArrowManager::ArrowManager(QWidget* parent) : QObject(parent) { m_parent = parent; }

ArrowManager::~ArrowManager() {}

void ArrowManager::addArrow(const int& x, const int& y) {
  int pointX = 0;
  int pointY = 0;

  if (x < 0 || x > m_parent->width())
    pointX = m_parent->width() / 2;
  else
    pointX = x;

  if (y < 0 || y > m_parent->height())
    pointY = m_parent->height() / 2;
  else
    pointY = y;

  QCursor::setPos(m_parent->screen(), m_parent->mapToGlobal(QPoint(pointX, pointY)));

  GlobalParam::Global_X = pointX;
  GlobalParam::Global_Y = pointY;

  m_curArrow = new Arrow(m_angleIdxF, m_fixedColorIdxF, m_solidIdxF, m_sizeIdxF, m_parent);
  connect(m_curArrow, &Arrow::sigPressArrow, this, &ArrowManager::onPressArrow);
  m_curArrow->move(pointX - m_curArrow->rect().width() / 2, pointY - m_curArrow->rect().height() / 2);
  m_curArrow->show();
}

void ArrowManager::deleteArrow() {
  if (m_curArrowList.size() > 0) {
    if (m_curArrow->getFirstCreationFlag()) {
      Arrow* tempArrow = m_curArrowList.last();
      tempArrow->hide();
      m_curArrowList.pop_back();
      m_undoArrowList.append(tempArrow);
    } else {
      m_curArrow->hide();
      m_curArrow->setStatus(1);
      m_curArrowList.removeOne(m_curArrow);
      m_undoArrowList.append(m_curArrow);
      addArrow(m_curArrow->x() + m_curArrow->width() + 6, m_curArrow->y() + m_curArrow->height() + 6);
    }
  }
}

void ArrowManager::undoArrow() {
  if (m_undoArrowList.size() > 0) {
    Arrow* tempArrow = m_undoArrowList.last();
    tempArrow->show();
    m_undoArrowList.pop_back();
    m_curArrowList.append(tempArrow);
  }
}

void ArrowManager::changeWorkStatus() {
  if (!m_workStatus) {
    addArrow(-1, -1);
    m_parent->setCursor(QCursor(Qt::BlankCursor));
    m_workStatus = true;
  } else {
    if (m_curArrow->getFirstCreationFlag()) {
      delete m_curArrow;
      m_curArrow = nullptr;
    } else {
      m_curArrowList.removeOne(m_curArrow);
      delete m_curArrow;
      m_curArrow = nullptr;
    }

    m_parent->setCursor(QCursor(Qt::ArrowCursor));
    m_workStatus = false;
  }
}

void ArrowManager::changeCurArrow(Arrow* arrow) {
  if (m_curArrow == arrow) {
    return;
  }

  delete m_curArrow;
  m_curArrow = arrow;
  if (m_curArrow != nullptr) {
    m_curArrow->setStatus(0);
  }
}

void ArrowManager::setArrowAngle(const int& value) {
  if (m_curArrow != nullptr) {
    m_angleIdxF = value % 8;
    m_curArrow->setAngleIdx(m_angleIdxF);
  }
}

void ArrowManager::setArrowFixedColor(const int& value) {
  if (m_curArrow != nullptr) {
    m_fixedColorIdxF = value % 6;
    m_curArrow->setFixedColorIdx(m_fixedColorIdxF);
  }
}

void ArrowManager::setArrowSolid(const int& value) {
  if (m_curArrow != nullptr) {
    m_solidIdxF = value % 2;
    m_curArrow->setSolidIdx(m_solidIdxF);
  }
}

void ArrowManager::setArrowSize(const int& value) {
  if (m_curArrow != nullptr) {
    m_sizeIdxF = value;
    m_curArrow->setSizeIdx(m_sizeIdxF);
  }
}

void ArrowManager::mouseMove(const QPoint& wdgPt) {
  if (m_workStatus) {
    GlobalParam::Global_X = wdgPt.x();
    GlobalParam::Global_Y = wdgPt.y();

    if (m_curArrow != nullptr) {
      if (m_curArrow->getFirstCreationFlag()) {
        bool tempFlag = false;

        for (Arrow* item : m_curArrowList) {
          if (item->arrowAreaFlag(wdgPt.x(), wdgPt.y())) {
            tempFlag = true;
            break;
          }
        }

        if (tempFlag) {
          m_curArrow->hide();
          m_parent->setCursor(QCursor(Qt::ClosedHandCursor));
        } else {
          m_curArrow->show();
          m_parent->setCursor(QCursor(Qt::BlankCursor));
        }
      } else {
        m_parent->setCursor(QCursor(Qt::ClosedHandCursor));
      }

      m_curArrow->move(wdgPt.x() - m_curArrow->rect().width() / 2, wdgPt.y() - m_curArrow->rect().height() / 2);
    }
  }
}

void ArrowManager::onPressArrow() {
  if (m_workStatus) {
    if (m_curArrow->getFirstCreationFlag() == false) {
      m_curArrow->setStatus(1);
      addArrow(m_curArrow->x() + m_curArrow->width() + 6, m_curArrow->y() + m_curArrow->height() + 6);
    } else {
      QPoint pt = m_parent->mapFromGlobal(QCursor::pos());
      bool tempFlag = false;
      Arrow* arrow = nullptr;
      for (Arrow* item : m_curArrowList) {
        if (item->arrowAreaFlag(pt.x(), pt.y())) {
          tempFlag = true;
          arrow = item;
          break;
        }
      }

      if (tempFlag) {
        changeCurArrow(arrow);
        m_parent->setCursor(QCursor(Qt::ClosedHandCursor));
      } else {
        if (m_curArrowList.size() < m_arrowMaxCount && m_curArrow->getFirstCreationFlag()) {
          m_curArrow->setFirstCreationFlag(false);
          m_curArrow->setStatus(1);
          m_curArrowList.append(m_curArrow);
          addArrow(m_curArrow->x() + m_curArrow->width() + 6, m_curArrow->y() + m_curArrow->height() + 6);
          m_parent->setCursor(QCursor(Qt::BlankCursor));
        }
      }
    }
  }
}
