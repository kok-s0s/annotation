#ifndef ARROW_H_
#define ARROW_H_

#include <QtWidgets>

#include "../AnnotationDefine.h"

class Arrow : public QWidget {
  Q_OBJECT

 protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

 public:
  Q_SIGNAL void sigPressArrow();

 public:
  enum class Status { Actived, Fixed };
  Arrow(int angleIdx, int fixedColorIdx, int solidIdx, int sizeIdx, QWidget *parent = nullptr);
  Arrow(QWidget *parent = nullptr);
  ~Arrow();
  void setArrowStatusImage();
  void setStatus(const int &value);
  QRect getArrowArea();
  bool arrowAreaFlag(int posX, int posY);
  void setFirstCreationFlag(const bool &flag);
  bool getFirstCreationFlag();
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
  bool m_firstCreationFlag = true;
  int m_angleIdx = 0;
  int m_fixedColorIdx = 0;
  int m_solidIdx = 0;
  int m_sizeIdx = 0;
  QPixmap m_fixedImage;
  QPixmap m_activedImage;
};

#endif  // ARROW_H_
