#include "qtpaperrockscissorswidget.h"
#include <QApplication>
#include "paperrockscissors.h"
#include "qtpaperrockscissorsmenudialog.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  #ifndef NDEBUG
  ribi::TestPaperRockScissors();
  #endif //~ NDEBUG
  ribi::QtPaperRockScissorsMenuDialog w;
  w.show();
  return a.exec();
}
