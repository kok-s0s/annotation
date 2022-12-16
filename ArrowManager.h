#ifndef ARROWMANAGER_H_
#define ARROWMANAGER_H_

#include <QtCore>
#include <QtWidgets>

#include "Arrow.h"

class ArrowManager : public QObject {
  Q_OBJECT

 protected:
  QWidget* m_parent = nullptr;

 public:
  ArrowManager(QWidget* parent);
  ~ArrowManager();
  void addArrow();
  void changeWorkStatus();
  void setArrowAngle(const int& value);
  void setArrowSolid(const int& value);
  void setArrowFixedColor(const int& value);
  void setArrowSize(const int& value);
  void mouseMove(const QPoint& wdgPt);
  void onPressArrow(Arrow* curArrow);

 private:
  Arrow* m_curArrow = nullptr;
  QList<Arrow*> m_ctrlArrowList;
  bool m_workStatus = false;
};

#endif  // ARROWMANAGER_H_
