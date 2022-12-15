#include "ArrowManager.h"

ArrowManager::ArrowManager(QWidget* parent) : QObject(parent) { m_parent = parent; }

ArrowManager::~ArrowManager() {}

void ArrowManager::start() {
  int pointX = m_parent->width() / 2;
  int pointY = m_parent->height() / 2;

  GlobalParam::Global_X = pointX;
  GlobalParam::Global_Y = pointY;

  m_curArrow = new Arrow(m_parent);
  m_curArrow->move(pointX - m_curArrow->rect().width() / 2, pointY - m_curArrow->rect().height() / 2);
  m_curArrow->show();
}
