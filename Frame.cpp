#include "Frame.h"

void Frame::mouseMoveEvent(QMouseEvent* event) {
  QPoint wdgPt = mapFromGlobal(event->globalPos());
  m_arrowManager->mouseMove(wdgPt);
  QWidget::mouseMoveEvent(event);
}

Frame::Frame(QWidget* parent) : QFrame(parent) {
  this->move(20, 20);
  this->resize(900, 600);
  this->setFrameShape(QFrame::StyledPanel);
  this->setFrameShadow(QFrame::Raised);
  this->setMouseTracking(true);

  m_arrowManager = new ArrowManager(this);
}

Frame::~Frame() {}
