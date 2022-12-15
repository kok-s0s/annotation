#ifndef FRAME_H_
#define FRAME_H_

#include <QtWidgets>

#include "ArrowManager.h"

class Frame : public QFrame {
 protected:
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

 public:
  Frame(QWidget *parent = Q_NULLPTR);
  ~Frame();
};

#endif  // FRAME_H_
