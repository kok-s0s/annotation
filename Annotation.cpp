#include "Annotation.h"

Annotation::Annotation(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);
}

Annotation::~Annotation() {}

void Annotation::on_btnArrow_clicked() { qDebug() << "clicked\n"; }
