#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "poisoningfunction.h"
#include "loripesconsumptionfunction.h"
#include "parameters.h"
#include "units.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::units::Test();
  InvertLogisticPoisoning();
  InvertedExponentialConsumption();
  Parameters();
  ribi::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
