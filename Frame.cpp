#include "Frame.h"

void Frame::mouseMoveEvent(QMouseEvent* event) {
  QPoint wdgPt = mapFromGlobal(QCursor::pos());
  m_arrowManager->mouseMove(wdgPt);
  m_textManager->mouseMove(wdgPt);
  QWidget::mouseMoveEvent(event);
}

Frame::Frame(QWidget* parent) : QFrame(parent) {
  this->move(20, 20);
  this->resize(900, 600);
  this->setFrameShape(QFrame::StyledPanel);
  this->setFrameShadow(QFrame::Raised);
  this->setMouseTracking(true);

  m_arrowManager = new ArrowManager(this);
  m_textManager = new TextManager(this);
}

Frame::~Frame() {}

void Frame::arrowSwitchWorkStatus() { m_arrowManager->changeWorkStatus(); }

void Frame::apiSetArrowAngle(const int& value) { m_arrowManager->setArrowAngle(value); }

void Frame::apiSetArrowSolid(const int& value) { m_arrowManager->setArrowSolid(value); }

void Frame::apiSetArrowFixedColor(const int& value) { m_arrowManager->setArrowFixedColor(value); }

void Frame::apiSetArrowSize(const int& value) { m_arrowManager->setArrowSize(value); }

void Frame::apiDeleteArrow() { m_arrowManager->deleteArrow(); }

void Frame::apiUndoArrow() { m_arrowManager->undoArrow(); }

void Frame::textSwitchWorkStatus() { m_arrowManager->changeWorkStatus(); }
