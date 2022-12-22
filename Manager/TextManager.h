#ifndef TEXTMANAGER_H_
#define TEXTMANAGER_H_

#include <QtCore>
#include <QtWidgets>

#include "../Unit/Text.h"

class TextManager : public QObject {
  Q_OBJECT

 protected:
  QWidget* m_parent = nullptr;

 public:
  TextManager(QWidget* parent);
  ~TextManager();
  void addText(const int& x, const int& y);
  void changeWorkStatus();
  void mouseMove(const QPoint& wdgPt);

 private:
  bool m_workStatus = false;
  Text* m_curText = nullptr;
  QLabel* m_curLabel;
};

#endif  // TEXTMANAGER_H_
