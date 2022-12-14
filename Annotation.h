#pragma once

#include "ui_Annotation.h"
#include <QDebug>
#include <QtWidgets/QMainWindow>

class Annotation : public QMainWindow {
  Q_OBJECT

private:
  Ui::AnnotationClass ui;

public:
  Annotation(QWidget *parent = Q_NULLPTR);
  ~Annotation();

private:
  Q_SLOT void on_btnArrow_clicked();
};
