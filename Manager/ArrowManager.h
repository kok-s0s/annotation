#ifndef ARROWMANAGER_H_
#define ARROWMANAGER_H_

#include <QtCore>
#include <QtWidgets>

#include "../Unit/Arrow.h"

class ArrowManager : public QObject {
  Q_OBJECT

 protected:
  QWidget* m_parent = nullptr;

 public:
  ArrowManager(QWidget* parent);
  ~ArrowManager();
  void addArrow(const int& x, const int& y);
  void deleteArrow();
  void undoArrow();
  void changeWorkStatus();
  void changeCurArrow(Arrow* arrow);
  void setArrowAngle(const int& value);
  void setArrowFixedColor(const int& value);
  void setArrowSolid(const int& value);
  void setArrowSize(const int& value);
  void mouseMove(const QPoint& wdgPt);
  void onPressArrow();

 private:
  Arrow* m_curArrow = nullptr;
  QList<Arrow*> m_curArrowList;
  QList<Arrow*> m_undoArrowList;
  int m_arrowMaxCount = 30;
  bool m_workStatus = false;
  int m_angleIdxF = 0;
  int m_fixedColorIdxF = 0;
  int m_solidIdxF = 1;
  int m_sizeIdxF = 0;
};

#endif  // ARROWMANAGER_H_
