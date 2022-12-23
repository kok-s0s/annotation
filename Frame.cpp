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
