#include "Arrow.h"

void Arrow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QStyleOption opt;
  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

  int iSize = GlobalParam::ArrowSizeA[m_sizeIndex];

  switch (m_status) {
    case Status::Fixed:
      painter.drawPixmap(0, 0, iSize, iSize, m_fixedImage);
      break;
    case Status::Actived:
      painter.drawPixmap(0, 0, iSize, iSize, m_activedImage);
      break;
  }
}

Arrow::Arrow(QWidget *parent) : QWidget(parent) {
  m_status = Status::Actived;

  int iSize = GlobalParam::ArrowSizeA[m_sizeIndex];
  setFixedSize(iSize, iSize);
  setArrowStatusImage();
}

Arrow::~Arrow() {}

void Arrow::setArrowStatusImage() {
  m_fixedImage.load(QString("%1/A%2/%3_%4.png").arg(ARROW_RES_PATH).arg(m_fixedColorIndex).arg(m_isSolid).arg(m_angle));
  m_activedImage.load(QString("%1/A/%2_%3.png").arg(ARROW_RES_PATH).arg(m_isSolid).arg(m_angle));
}
