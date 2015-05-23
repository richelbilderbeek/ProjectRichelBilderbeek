#include "qtpaperrockscissorswithtraitwidget.h"
#include <QApplication>
#include "paperrockscissors.h"
#include "qtpaperrockscissorswithtraitmenudialog.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TestPaperRockScissors();
  ribi::QtPaperRockScissorsWithTraitMenuDialog w;
  w.show();
  return a.exec();
}
