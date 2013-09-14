#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>
#include <QDesktopWidget>
#include "qttestqtroundededitrectitemmenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtTestQtRoundedEditRectItemMenuDialog d;
  d.show();
  return a.exec();
}
