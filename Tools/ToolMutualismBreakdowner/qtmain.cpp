#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "poisoningfunction.h"
#include "loripesconsumptionfunction.h"
#include "parameters.h"
#include "units.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"
#include "qtmutualismbreakdownertimeplotdialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtMutualismBreakdownerTimePlotDialog();
  QtMutualismBreakdownerEquilibriumDialog();
  ribi::units::Test();
  InvertLogisticPoisoning();
  InvertedExponentialConsumption();
  Parameters();
  ribi::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
