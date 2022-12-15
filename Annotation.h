#ifndef ANNOTATION_H_
#define ANNOTATION_H_

#include <QDebug>
#include <QtWidgets>

#include "ArrowManager.h"
#include "ui_Annotation.h"

class Annotation : public QMainWindow {
  Q_OBJECT

 private:
  Ui::AnnotationClass ui;
  ArrowManager *m_arrowManager;

 public:
  Annotation(QWidget *parent = Q_NULLPTR);
  ~Annotation();

 private:
  Q_SLOT void on_btnArrow_clicked();
};

#endif  // ANNOTATION_H_
