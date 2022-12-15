#include "ArrowManager.h"

ArrowManager::ArrowManager(QWidget* parent) : QObject(parent) { m_parent = parent; }

ArrowManager::~ArrowManager() {}

void ArrowManager::start() {
  m_curArrow = new Arrow(m_parent);
  m_curArrow->move(333, 333);
  m_curArrow->show();
}
