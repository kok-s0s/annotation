#include "Text.h"

Text::Text(QWidget* parent, QLabel* label) : QLineEdit(parent), m_cursorDrawTimer(this), m_label(label) {
  setMouseTracking(true);
  setModified(false);
  setFrame(false);
  setStyleSheet("border-width:0;border-style:solid;");
  setContextMenuPolicy(Qt::NoContextMenu);
  connect(this, &Text::textChanged, this, &Text::onTextChanged);
  connect(&m_cursorDrawTimer, &QTimer::timeout, [=]() {
    m_bCursorDraw = !m_bCursorDraw;
    update();
  });
  m_cursorDrawTimer.start(600);
  installEventFilter(parent);
}

Text::Text(QWidget* parent, QLabel* label, QString text) : QLineEdit(parent), m_cursorDrawTimer(this), m_label(label) {
  setMouseTracking(true);
  setModified(false);
  setFrame(false);
  setStyleSheet("border-width:0;border-style:solid;");
  setContextMenuPolicy(Qt::NoContextMenu);
  setText(text);
  connect(this, &Text::textChanged, this, &Text::onTextChanged);
  connect(&m_cursorDrawTimer, &QTimer::timeout, [=]() {
    m_bCursorDraw = !m_bCursorDraw;
    update();
  });
  m_cursorDrawTimer.start(600);
  installEventFilter(parent);
}

Text::~Text() {}

void Text::setStatus(const Status& status) {
  if (status != m_status) {
    switch (status) {
      case Status::Editable:
        setModified(false);
        setReadOnly(false);
        emit sigToEditText(this);
        break;
      case Status::Fixed:
      case Status::Actived:
        setReadOnly(true);
        break;
    }

    m_status = status;
  }
}

bool Text::isInArea() {
  QRect rt = parentWidget()->rect();
  return rt.contains(mapToParent(mapFromGlobal(QCursor::pos())));
}

QPoint Text::getPointAtCursor(const QString inText) {
  int cursorX = getTextWidth(inText);
  cursorX += 2;
  int cursorY = height() / 2;
  return QPoint(cursorX, cursorY);
}

void Text::moveAnnot(const QPoint& pos) {
  if (m_status == Status::Actived) {
    int posX = pos.x();
    int posY = pos.y();

    int maxX = ((QWidget*)this->parent())->width() - width() - BORDER_PIX;
    if (posX > maxX) {
      posX = maxX;
    }
    if (posX < BORDER_PIX) {
      posX = BORDER_PIX;
    }

    int maxY = ((QWidget*)this->parent())->height() - height() - BORDER_PIX;
    if (posY > maxY) {
      posY = maxY;
    }
    if (posY < BORDER_PIX) {
      posY = BORDER_PIX;
    }

    move(posX, posY);
  }
}

bool Text::isTextEmpty() { return text().trimmed().isEmpty(); }

void Text::setAText(const QString& value, const bool& isSpace) {
  if (value.isEmpty()) {
    return;
  }
  QString allText = text();
  QString newText;
  int newPosition = 0;
  if (allText.length() <= 0) {
    newText = value;
    newPosition = newText.length();
  } else {
    const QString spaceChar = " ";
    int cursorPos = this->cursorPosition();
    if (cursorPos == 0) {
      newText.append(value);
      if (isSpace) {
        newText.append(spaceChar);
      }
      newText.append(allText);
      newPosition = newText.length();
    } else if (cursorPos < allText.length()) {
      QString strLeft = allText.left(cursorPos);
      QString strRight = allText.right(allText.length() - cursorPos);
      if (strLeft.lastIndexOf(spaceChar) != strLeft.length() - 1 && isSpace) {
        newText.append(spaceChar);
      }
      newText.append(value);
      if (strRight.lastIndexOf(spaceChar) != 0 && isSpace) {
        newText.append(spaceChar);
      }
      newText = strLeft + newText;
      newPosition = newText.length();
      newText = newText + strRight;
    } else {
      newText.append(allText);
      if (isSpace) {
        newText.append(spaceChar);
      }
      newText.append(value);
      newPosition = newText.length();
    }
  }
  setText(newText);
}

void Text::setEditWidth(const int& iWidth) {
  m_labelEditWidth = iWidth + 7;
  setFixedWidth(m_labelEditWidth);
}

void Text::setCurEditWidth() {
  int iWidth = getTextWidth(text());
  setEditWidth(iWidth);
}

void Text::setFontName(const QString& value) {
  if (value.isEmpty()) {
    return;
  }
  QFont ctrlFont = font();
  ctrlFont.setFamily(value);
  setFont(ctrlFont);
}

void Text::setCurPosToTextEnd() {
  QPoint led_pt = getPointAtCursor(text());
  QPoint parentPt = mapToParent(led_pt);
  GlobalParam::Global_X = parentPt.x();
  GlobalParam::Global_Y = parentPt.y();
  QPoint globalPt = this->parentWidget()->mapToGlobal(parentPt);
  QCursor::setPos(globalPt);
}

void Text::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
    if (text().isEmpty()) {
      emit sigDeleteText();
    }
  }
  QLineEdit::keyPressEvent(event);
}

// void Text::enterEvent(QEvent* event) { emit sigEnterText(this); }

void Text::leaveEvent(QEvent* event) {
  if (isInArea()) {
    emit sigLeaveText(this);
    if (m_status == Status::Editable) setStatus(Status::Fixed);
  }
  QLineEdit::leaveEvent(event);
}

void Text::focusInEvent(QFocusEvent* event) {
  if (GlobalParam::CurrentAText != nullptr && GlobalParam::CurrentAText != this) {
    QLineEdit::focusInEvent(event);
  } else {
    if (m_status != Status::Editable && m_status != Status::Actived) {
      setStatus(Status::Editable);
    }
    QLineEdit::focusInEvent(event);
  }
}

void Text::onLeftMousePress() {
  if (GlobalParam::CurrentAText != nullptr && GlobalParam::CurrentAText != this) {
  } else {
    if (isOut()) {
      //?????????????????????????????????????????????????????????????????????
      setStatus(Status::Fixed);
    } else {
      if (m_status == Status::Actived) {
        setStatus(Status::Fixed);
      } else {
        setStatus(Status::Actived);
      }
    }
  }
}

void Text::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    onLeftMousePress();
  }
  QLineEdit::mousePressEvent(event);
}

void Text::mouseMoveEvent(QMouseEvent* event) {
  QPoint pos = mapToParent(event->pos());
  GlobalParam::Global_X = pos.x();
  GlobalParam::Global_Y = pos.y();

  if (m_status == Status::Editable) {
    if (!text().isEmpty()) {
      if (isOut()) {
        setStatus(Status::Fixed);
      } else {
        int pos = cursorPositionAt(event->pos());
        setCursorPosition(pos);
      }
    }
  } else if (m_status == Status::Actived) {
    moveAnnot(pos);
  }

  QLineEdit::mouseMoveEvent(event);
}

void Text::paintEvent(QPaintEvent* event) {
  QPainter painter(this);

  QFontMetrics fontMetric = painter.fontMetrics();
  int textHeight = fontMetric.height();

  if (m_status == Status::Editable && hasFocus() && m_bCursorDraw) {
    QString disp = displayText();
    int ipos = cursorPosition();
    int cursorX = fontMetric.boundingRect(displayText().left(cursorPosition())).width();

    if (cursorX > width()) cursorX = width();
    QPen pen;
    pen.setColor(GlobalParam::CursorColor);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(QPoint(cursorX, 0), QPoint(cursorX, textHeight));
  }

  QRect textRect;

  int textWidth = 0;
  if (!displayText().isEmpty()) {
    textWidth = fontMetric.boundingRect(displayText().left(cursorPosition())).width();
    if (textWidth <= width()) textWidth = width();
  } else {
    textWidth = width();
  }
  textRect.setX(0);
  textRect.setY((height() - textHeight) / 2);
  textRect.setWidth(textWidth);
  textRect.setHeight(textHeight);
  //????????????????????????????????????????????????????????????????????????????
  QString drawText;
  if (!displayText().isEmpty()) {
    if (m_status == Status::Fixed) {
      painter.setPen(QPen(GlobalParam::FixedColorA[m_fixedColorIdx]));
    } else {
      painter.setPen(QPen(GlobalParam::ActivedColor));
    }
    drawText = displayText();
  }
  //????????????
  painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, drawText);
}

void Text::mouseReleaseEvent(QMouseEvent* event) {
  emit sigMouseRelease(event->button(), mapToGlobal(event->pos()));
  QLineEdit::mouseReleaseEvent(event);
}

bool Text::isOut() {
  bool ret = false;
  if (isInArea()) {
    QPoint pos = mapFromGlobal(QCursor::pos());
    QRect rt = rect();
    m_label->setText(this->text());
    m_label->adjustSize();
    rt.setWidth(m_label->width() + TEXTEASYIN_PIX);
    ret = !rt.contains(pos);
  }
  return ret;
}

int Text::getTextWidth(const QString& strText) {
  //!< ??????????????????????????????????????????????????????
  QFontMetrics fm(font());
  QRect rec = fm.boundingRect(strText);
  int textWidth = rec.width();
  return textWidth;
}

QPoint Text::getCursorAtTextPos(const QString inText, const int& pos) {
  int cursorY = height() / 2;
  int cursorX = getTextWidth(inText);
  QPoint temp = QPoint(cursorX, cursorY);
  int tempPos = cursorPositionAt(temp);
  while (tempPos != pos) {
    if (tempPos > pos) {
      temp.setX(temp.x() - 1);
      tempPos = cursorPositionAt(temp);
    } else if (tempPos < pos) {
      temp.setX(temp.x() + 1);
      tempPos = cursorPositionAt(temp);
    } else {
      break;
    }
  }
  setCursorPosition(tempPos);
  return temp;
}

void Text::onEditingFinished() {
  if (isInArea()) {
    if (m_status == Status::Editable) setStatus(Status::Fixed);
  }
}

void Text::onTextChanged(const QString inText) {
  GlobalParam::ATextEnterOpen = false;

  bool needCut = false;
  QString tempText = inText;
  while (getTextWidth(tempText) > m_labelEditWidth - TEXTEASYIN_PIX) {
    needCut = true;
    tempText = tempText.left(tempText.length() - 1);
  }
  if (needCut) {
    setText(tempText);
  }
  int pos = cursorPosition();
  QString posText = tempText.left(pos);
  QPoint lineEdit = getCursorAtTextPos(posText, pos);
  QPoint parentPt = mapToParent(lineEdit);
  GlobalParam::Global_X = parentPt.x();
  GlobalParam::Global_Y = parentPt.y();
  QPoint globalPt = this->parentWidget()->mapToGlobal(parentPt);
  QCursor::setPos(globalPt);
}
