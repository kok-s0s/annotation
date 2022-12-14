#include "Annotation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Annotation w;
  w.show();
  return a.exec();
}
