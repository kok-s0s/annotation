#include "Annotation.h"

#include "ui_Annotation.h"

int GlobalParam::Global_X = 0;
int GlobalParam::Global_Y = 0;
bool GlobalParam::ATextEnterOpen = false;
void *GlobalParam::CurrentAText = nullptr;
QColor GlobalParam::CursorColor = QColor(34, 177, 76);    // Green
QColor GlobalParam::ActivedColor = QColor(118, 255, 30);  // Green
QVector<QColor> GlobalParam::FixedColorA = {
    QColor(255, 255, 0),    // Yellow
    QColor(0, 176, 240),    // Blue
    QColor(230, 175, 0),    // Orange
    QColor(255, 0, 0),      // Red
    QColor(220, 220, 220),  // Gray
    QColor(112, 48, 160)    // Purple
};
QVector<int> GlobalParam::ArrowSizeA = {40, 50, 60};

Annotation::Annotation(QWidget *parent) : QMainWindow(parent), ui(new Ui::AnnotationClass) {
  ui->setupUi(this);

  m_frame = new Frame(this);
}

Annotation::~Annotation() {}

void Annotation::on_btnArrow_clicked() { m_frame->m_arrowManager->start(); }

void Annotation::on_btnArrowAngle_clicked() {
  m_angleIdx++;
  m_frame->m_arrowManager->setArrowAngle(m_angleIdx);
  if (m_angleIdx > INT_MAX) {
    m_angleIdx = 0;
  }
}

void Annotation::on_btnArrowSolid_clicked() {
  m_solidIdx++;
  m_frame->m_arrowManager->setArrowSolid(m_solidIdx);
  if (m_solidIdx > INT_MAX) {
    m_solidIdx = 0;
  }
}

void Annotation::on_btnArrowColor_clicked() {
  m_fixedColorIdx++;
  m_frame->m_arrowManager->setArrowFixedColor(m_fixedColorIdx);
  if (m_fixedColorIdx > INT_MAX) {
    m_fixedColorIdx = 0;
  }
}

void Annotation::on_btnArrowSize_clicked() {
  m_sizeIdx++;
  m_frame->m_arrowManager->setArrowSize(m_sizeIdx);
  if (m_sizeIdx > INT_MAX) {
    m_sizeIdx = 0;
  }
}
