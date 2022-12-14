#pragma once

#include "ui_Annotation.h"
#include <QtWidgets/QMainWindow>

class Annotation : public QMainWindow {
  Q_OBJECT

private:
  Ui::AnnotationClass ui;

public:
  Annotation(QWidget *parent = Q_NULLPTR);
  ~Annotation();
};
