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
          QApplication::setOverrideCursor(Qt::SizeAllCursor);
        } else {
          m_curArrow->show();
          QApplication::setOverrideCursor(Qt::BlankCursor);
        }
      } else {
        QApplication::setOverrideCursor(Qt::BlankCursor);
      }

      m_curArrow->move(wdgPt.x() - m_curArrow->rect().width() / 2, wdgPt.y() - m_curArrow->rect().height() / 2);
    }
  }
}

void ArrowManager::onPressArrow() {
  if (m_workStatus) {
    if (m_curArrow->getFirstCreationFlag() == false) {
      m_curArrow->setStatus(1);
      addArrow();

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
        QApplication::setOverrideCursor(Qt::BlankCursor);
      } else {
        if (m_curArrowList.size() < m_arrowMaxCount && m_curArrow->getFirstCreationFlag()) {
          m_curArrow->setFirstCreationFlag(false);
          m_curArrow->setStatus(1);
          m_curArrowList.append(m_curArrow);
          addArrow();
        }
      }
    }
  }
}
