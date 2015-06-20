#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtspeciesoftheringsmaindialog.h"
#include "histogram_r.h"
#include <QApplication>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::HistogramR();
  ribi::QtSpeciesOfTheRingsMainDialog w;
  w.show();
  return a.exec();
}
