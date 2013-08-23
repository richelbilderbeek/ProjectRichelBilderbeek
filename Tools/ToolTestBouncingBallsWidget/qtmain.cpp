#include <QApplication>
#include "qttooltestbouncingballswidgetmaindialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtToolTestBouncingBallsWidgetMainDialog w;
  w.show();
  return a.exec();
}
