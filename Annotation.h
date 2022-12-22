#ifndef ANNOTATION_H_
#define ANNOTATION_H_

#include <QDebug>
#include <QtWidgets>

#include "Frame.h"
#include "ui_Annotation.h"

class Annotation : public QMainWindow {
  Q_OBJECT

 private:
  Ui::AnnotationClass *ui;
  Frame *m_frame;
  int m_angleIdx = 0;
  int m_solidIdx = 0;
  int m_fixedColorIdx = 0;
  int m_sizeIdx = 0;

 public:
  Annotation(QWidget *parent = Q_NULLPTR);
  ~Annotation();

 private:
  Q_SLOT void on_btnArrow_clicked();
  Q_SLOT void on_btnArrowAngle_clicked();
  Q_SLOT void on_btnArrowSolid_clicked();
  Q_SLOT void on_btnArrowColor_clicked();
  Q_SLOT void on_btnArrowSize_clicked();
  Q_SLOT void on_btnArrowDelete_clicked();
  Q_SLOT void on_btnArrowUndo_clicked();
  Q_SLOT void on_btnText_clicked();
};

#endif  // ANNOTATION_H_
