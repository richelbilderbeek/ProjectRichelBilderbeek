#include <QApplication>
#include <QDesktopWidget>
#include "qttestqtroundededitrectitemmenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestQtRoundedEditRectItemMenuDialog d;
  d.show();
  return a.exec();
}
