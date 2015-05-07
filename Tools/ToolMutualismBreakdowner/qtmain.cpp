#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
