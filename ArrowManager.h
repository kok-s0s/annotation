#ifndef ARROWMANAGER_H_
#define ARROWMANAGER_H_

#include <QtCore>
#include <QtWidgets>

#include "Arrow.h"

class ArrowManager : public QObject {
  Q_OBJECT

 public:
  ArrowManager(QWidget* parent);
  ~ArrowManager();
  void start();

 protected:
  QWidget* m_parent = nullptr;

 private:
  Arrow* m_curArrow = nullptr;
  QList<Arrow*> m_ctrlArrowList;
};

#endif  // ARROWMANAGER_H_
