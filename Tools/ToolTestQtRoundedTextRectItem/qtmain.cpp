#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>
#include <QDesktopWidget>
#include "qttestqtroundedtextrectitemmenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtTestQtRoundedTextRectItemMenuDialog w;
  w.show();
  return a.exec();
}
