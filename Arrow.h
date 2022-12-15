#ifndef ARROW_H_
#define ARROW_H_

#include <QtWidgets>

#include "AnnotationDefine.h"

class Arrow : public QWidget {
  Q_OBJECT
 protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

 public:
  enum class Status { Actived, Fixed };
  explicit Arrow(QWidget *parent = nullptr);
  ~Arrow();
  void setArrowStatusImage();
  void setAngleIdx(const int &value);
  int getAngleIdx();
  void setFixedColorIdx(const int &value);
  int getFixedColorIdx();
  void setSolidIdx(const int &value);
  int getSolidIdx();
  void setSizeIdx(const int &value);
  int getSizeIdx();

 private:
  Status m_status;
  int m_angleIdx = 0;
  int m_fixedColorIdx = 0;
  int m_solidIdx = 1;
  int m_sizeIdx = 0;
  QPixmap m_fixedImage;
  QPixmap m_activedImage;
};

#endif  // ARROW_H_
