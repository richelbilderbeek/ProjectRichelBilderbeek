#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
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
