#include "Arrow.h"

void Arrow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  int iSize = GlobalParam::ArrowSizeA[m_sizeIdx];

  switch (m_status) {
    case Status::Fixed:
      painter.drawPixmap(0, 0, iSize, iSize, m_fixedImage);
      break;
    case Status::Actived:
      painter.drawPixmap(0, 0, iSize, iSize, m_activedImage);
      break;
  }
}

void Arrow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    emit sigPressArrow();
  }
  QWidget::mousePressEvent(event);
}

Arrow::Arrow(int angleIdx, int fixedColorIdx, int solidIdx, int sizeIdx, QWidget *parent) : QWidget(parent) {
  m_status = Status::Actived;

  m_angleIdx = angleIdx;
  m_fixedColorIdx = fixedColorIdx;
  m_solidIdx = solidIdx;
  m_sizeIdx = sizeIdx;

  int iSize = GlobalParam::ArrowSizeA[m_sizeIdx];
  setFixedSize(iSize, iSize);
  setMouseTracking(true);
  setArrowStatusImage();
}

Arrow::Arrow(QWidget *parent) : QWidget(parent) {
  m_status = Status::Actived;

  int iSize = GlobalParam::ArrowSizeA[m_sizeIdx];
  setFixedSize(iSize, iSize);
  setMouseTracking(true);
  setArrowStatusImage();
}

Arrow::~Arrow() {}

void Arrow::setArrowStatusImage() {
  m_fixedImage.load(QString("%1/A%2/%3_%4.png").arg(ARROW_RES_PATH).arg(m_fixedColorIdx).arg(m_solidIdx).arg(m_angleIdx));
  m_activedImage.load(QString("%1/A/%2_%3.png").arg(ARROW_RES_PATH).arg(m_solidIdx).arg(m_angleIdx));
}

void Arrow::setStatus(const int &value) {
  if (m_status != Status(value)) {
    m_status = Status(value);
  }
}

QRect Arrow::getArrowArea() {
  QRect rt = rect();
  int half = rt.width() / 2;
  switch (m_angleIdx) {
    case 0:  // 45°
      rt.setX(half - 1);
      rt.setY(half - 1);
      break;
    case 1:  // 90°
      rt.setX(half - 1);
      rt.setY(half / 2 - 1);
      break;
    case 2:  // 135°
      rt.setX(half - 1);
      rt.setY(0);
      break;
    case 3:  // 180°
      rt.setX(half / 2 - 1);
      rt.setY(0);
      break;
    case 4:  // 225°
      rt.setX(0);
      rt.setY(0);
      break;
    case 5:  // 270°
      rt.setX(0);
      rt.setY(half / 2 - 1);
      break;
    case 6:  // 315°
      rt.setX(0);
      rt.setY(half - 1);
      break;
    case 7:  // 0°
      rt.setX(half / 2 - 1);
      rt.setY(half - 1);
      break;
  }
  rt.setWidth(half);
  rt.setHeight(half);
  return rt;
}

bool Arrow::arrowAreaFlag(int posX, int posY) { return getArrowArea().contains(mapFromParent(QPoint(posX, posY))); }

void Arrow::setFirstCreationFlag(const bool &flag) { m_firstCreationFlag = flag; }

bool Arrow::getFirstCreationFlag() { return m_firstCreationFlag; }

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
