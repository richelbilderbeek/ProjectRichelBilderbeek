#include "qtwidget.h"
#include <QApplication>
#include "paper_rock_scissors.h"
#include "qtpaperrockscissorsmenudialog.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TestPaperRockScissors();
  ribi::QtPaperRockScissorsMenuDialog w;
  w.show();
  return a.exec();
}
