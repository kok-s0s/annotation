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
  void start();

 private:
  Arrow* m_curArrow = nullptr;
  QList<Arrow*> m_ctrlArrowList;
};

#endif  // ARROWMANAGER_H_
