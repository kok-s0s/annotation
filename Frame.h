#ifndef FRAME_H_
#define FRAME_H_

#include <QtWidgets>

#include "Manager/ArrowManager.h"
#include "Manager/TextManager.h"

class Frame : public QFrame {
 protected:
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

 public:
  Frame(QWidget *parent = Q_NULLPTR);
  ~Frame();
  void arrowSwitchWorkStatus();
  void apiSetArrowAngle(const int &value);
  void apiSetArrowSolid(const int &value);
  void apiSetArrowFixedColor(const int &value);
  void apiSetArrowSize(const int &value);
  void apiDeleteArrow();
  void apiUndoArrow();
  void textSwitchWorkStatus();

 private:
  ArrowManager *m_arrowManager;
  TextManager *m_textManager;
};

#endif  // FRAME_H_
