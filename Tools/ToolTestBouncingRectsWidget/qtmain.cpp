#include <QtGui/QApplication>
#include "qttooltestbouncingrectswidgetmaindialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtToolTestBouncingRectsWidgetMainDialog w;
  w.show();
  return a.exec();
}
