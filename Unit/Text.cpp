#include "Text.h"

void Text::paintEvent(QPaintEvent* event) {
  QPainter painter(this);

  QFontMetrics fontMetrics = painter.fontMetrics();
  int textHeight = fontMetrics.height();

  if (m_status == Status::Actived && hasFocus()) {
    QString disp = displayText();
    int ipos = cursorPosition();
    int cursorX = fontMetrics.boundingRect(displayText().left(cursorPosition())).width();
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
    textWidth = fontMetrics.boundingRect(displayText().left(cursorPosition())).width();
    if (textWidth <= width()) textWidth = width();
  } else {
    textWidth = width();
  }
  textRect.setX(0);
  textRect.setY((height() - textHeight) / 2);
  textRect.setWidth(textWidth);
  textRect.setHeight(textHeight);

  QString drawText;
  if (!displayText().isEmpty()) {
    if (m_status == Status::Fixed) {
      painter.setPen(QPen(GlobalParam::FixedColorA[m_fixedColorIdx]));
    } else {
      painter.setPen(QPen(GlobalParam::ActivedColor));
    }
    drawText = displayText();
  }
  painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, drawText);
}

Text::Text(QWidget* parent, QLabel* label) : QLineEdit(parent), m_cursorDrawTimer(this), m_label(label) {
  m_status = Status::Actived;

  m_cursorDrawTimer.start(600);

  setMouseTracking(true);
  setModified(false);
  setFrame(false);
  setStyleSheet("border-width:0;border-style:solid;");
  setContextMenuPolicy(Qt::NoContextMenu);
  installEventFilter(parent);
}

Text::Text(QWidget* parent, QLabel* label, QString text) : QLineEdit(parent), m_cursorDrawTimer(this), m_label(label) {
  m_status = Status::Actived;

  m_cursorDrawTimer.start(600);

  setText(text);

  setMouseTracking(true);
  setModified(false);
  setFrame(false);
  setStyleSheet("border-width:0;border-style:solid;");
  setContextMenuPolicy(Qt::NoContextMenu);
  installEventFilter(parent);
}

Text::~Text() {}

void Text::moveText(const QPoint& pos) {
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
