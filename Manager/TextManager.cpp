#include "TextManager.h"

TextManager::TextManager(QWidget* parent) : QObject(parent) { m_parent = parent; }

TextManager::~TextManager() {}

void TextManager::addText(const int& x, const int& y) {
  m_curLabel = new QLabel();
  m_curLabel->setFixedHeight(16);
  m_curLabel->setFixedWidth(54);

  int pointX = 0;
  int pointY = 0;

  if (x < BORDER_PIX) {
    pointX = BORDER_PIX;
  } else if (x > m_parent->width() - 64) {
    pointX = m_parent->width() - 64;
  } else {
    pointX = x;
  }

  if (y < BORDER_PIX) {
    pointY = BORDER_PIX;
  } else if (y > m_parent->height() - m_curLabel->height()) {
    pointY = m_parent->height() - m_curLabel->height();
  } else {
    pointY = y;
  }

  m_curText = new Text(m_parent, m_curLabel);

  int iWidth = m_parent->width() - pointX - 2 * BORDER_PIX;
  m_curText->move(pointX, pointY);
  m_curText->setFocus();
  m_curText->show();
}

void TextManager::changeWorkStatus() {
  if (!m_workStatus) {
    addText(m_parent->width() / 2, m_parent->height() / 2);
    m_parent->setCursor(QCursor(Qt::BlankCursor));
    m_workStatus = true;
  } else {
    m_parent->setCursor(QCursor(Qt::ArrowCursor));
    m_workStatus = false;
  }
}

void TextManager::mouseMove(const QPoint& wdgPt) {
  if (m_workStatus) {
    GlobalParam::Global_X = wdgPt.x();
    GlobalParam::Global_Y = wdgPt.y();

    m_curText->moveText(wdgPt);
  }
}
