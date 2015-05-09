#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "poisoningfunction.h"
#include "loripesconsumptionfunction.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  InvertLogisticPoisoning();
  InvertedExponentialConsumption();
  ribi::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
