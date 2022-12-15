#include "Arrow.h"

void Arrow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QStyleOption opt;
  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

  int iSize = GlobalParam::ArrowSizeA[m_sizeIdx];

  switch (m_status) {
    case Status::Fixed:
      painter.drawPixmap(0, 0, iSize, iSize, m_fixedImage);
      break;
    case Status::Actived:
      painter.drawPixmap(0, 0, iSize, iSize, m_activedImage);
      break;
  }
  painter.setPen(QColor("green"));
  painter.drawRect(0, 0, width() - 1, height() - 1);
}

Arrow::Arrow(QWidget *parent) : QWidget(parent) {
  this->setMouseTracking(true);

  m_status = Status::Fixed;

  int iSize = GlobalParam::ArrowSizeA[m_sizeIdx];
  setFixedSize(iSize, iSize);
  setArrowStatusImage();
}

Arrow::~Arrow() {}

void Arrow::setArrowStatusImage() {
  m_fixedImage.load(QString("%1/A%2/%3_%4.png").arg(ARROW_RES_PATH).arg(m_fixedColorIdx).arg(m_solidIdx).arg(m_angleIdx));
  m_activedImage.load(QString("%1/A/%2_%3.png").arg(ARROW_RES_PATH).arg(m_solidIdx).arg(m_angleIdx));
}

void Arrow::setAngleIdx(const int &value) {
  m_angleIdx = value % 8;
  setArrowStatusImage();
  update();
}

int Arrow::getAngleIdx() { return m_angleIdx; }

void Arrow::setFixedColorIdx(const int &value) {
  m_fixedColorIdx = value % 6;
  setArrowStatusImage();
  update();
}

int Arrow::getFixedColorIdx() { return m_fixedColorIdx; }

void Arrow::setSolidIdx(const int &value) {
  m_solidIdx = value % 2;
  setArrowStatusImage();
  update();
}

int Arrow::getSolidIdx() { return m_solidIdx; }

void Arrow::setSizeIdx(const int &value) {
  m_sizeIdx = value % GlobalParam::ArrowSizeA.size();

  int iSize = GlobalParam::ArrowSizeA[m_sizeIdx];
  setFixedSize(iSize, iSize);
}

int Arrow::getSizeIdx() { return m_sizeIdx; }
