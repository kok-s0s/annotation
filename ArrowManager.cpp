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

void ArrowManager::setArrowAngle(const int& value) { m_curArrow->setAngleIdx(value); }

void ArrowManager::setArrowSolid(const int& value) { m_curArrow->setSolidIdx(value); }

void ArrowManager::setArrowFixedColor(const int& value) { m_curArrow->setFixedColorIdx(value); }

void ArrowManager::setArrowSize(const int& value) { m_curArrow->setSizeIdx(value); }