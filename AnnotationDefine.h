#ifndef ANNOTATIONDEFINE_H_
#define ANNOTATIONDEFINE_H_

#include <QColor>
#include <QtCore>

#define ARROW_RES_PATH QCoreApplication::applicationDirPath() + "/resource/Arrow"

class GlobalParam {
 public:
  static int Global_X;
  static int Global_Y;
  static bool ATextEnterOpen;
  static void *CurrentAText;
  static QColor CursorColor;
  static QColor ActivedColor;
  static QVector<QColor> FixedColorA;
  static QVector<int> ArrowSizeA;

  static void setPos(const QPoint &pos) {
    Global_X = pos.x();
    Global_Y = pos.y();
  }

  static void setPos(const int &x, const int &y) {
    Global_X = x;
    Global_Y = y;
  }
};

#endif  // ANNOTATIONDEFINE_H_
