#ifndef TEXT_H_
#define TEXT_H_

#include <QtWidgets>

#include "../AnnotationDefine.h"

class Text : public QLineEdit {
  Q_OBJECT

 protected:
  void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
  // void enterEvent(QEvent* event) Q_DECL_OVERRIDE;
  void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;
  void focusInEvent(QFocusEvent* event) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
  void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

 public:
  enum class Status { Actived, Editable, Fixed };
  Text(QWidget* parent, QLabel* label);
  Text(QWidget* parent, QLabel* label, QString text);
  ~Text();
  void setStatus(const Status& status);
  bool isInArea();
  void setEditWidth(const int& iWidth);
  void setCurEditWidth();
  void moveAnnot(const QPoint& pos);
  bool isTextEmpty();
  void setAText(const QString& value, const bool& isSpace);
  QPoint getPointAtCursor(const QString inText);
  void setFontName(const QString& value);
  void setCurPosToTextEnd();
  bool isOut();
  void onLeftMousePress();

 private:
  int getTextWidth(const QString& strText);
  QPoint getCursorAtTextPos(const QString inText, const int& pos);

 private:
  Q_SLOT void onEditingFinished();
  Q_SLOT void onTextChanged(const QString inText);

 private:
  Q_SIGNAL void sigAnnotStatusChanged(Text* text, const int& preStatus);
  Q_SIGNAL void sigToEditText(Text* text);
  Q_SIGNAL void sigDeleteText();
  Q_SIGNAL void sigEnterText(Text* text);
  Q_SIGNAL void sigLeaveText(Text* text);
  Q_SIGNAL void sigMouseRelease(const int& btnType, const QPoint& goablPt);

 private:
  Status m_status = Status::Actived;
  QLabel* m_label;
  int m_labelEditWidth = 100;
  QTimer m_cursorDrawTimer;
  bool m_bCursorDraw = false;
  int m_fixedColorIdx = 0;
};

#endif  // TEXT_H_
