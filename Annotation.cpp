#include "Annotation.h"

#include "Arrow.h"

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

Annotation::Annotation(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);
  m_arrowManager = new ArrowManager(this);
}

Annotation::~Annotation() {}

void Annotation::on_btnArrow_clicked() { m_arrowManager->start(); }
