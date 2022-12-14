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

 private:
  Status m_status;
  int m_fixedColorIndex = 1;
  int m_isSolid = 1;
  int m_angle = 0;
  int m_sizeIndex = 0;
  QPixmap m_fixedImage;
  QPixmap m_activedImage;
};

#endif  // ARROW_H_
