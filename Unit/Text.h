#ifndef TEXT_H_
#define TEXT_H_

#include <QtWidgets>

#include "../AnnotationDefine.h"

class Text : public QLineEdit {
  Q_OBJECT

 protected:
  void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

 public:
  enum class Status { Actived, Editable, Fixed };
  Text(QWidget* parent, QLabel* label);
  Text(QWidget* parent, QLabel* label, QString text);
  ~Text();
  void moveText(const QPoint& pos);

 private:
  Status m_status;
  QLabel* m_label;
  int m_labelEditWidth;
  QTimer m_cursorDrawTimer;
  int m_fixedColorIdx = 0;
};

#endif  // TEXT_H_
