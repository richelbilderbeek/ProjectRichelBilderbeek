#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "poisoningfunction.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  InvertLogisticPoisoning();
  ribi::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
