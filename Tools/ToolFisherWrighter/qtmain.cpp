#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include "qtfisherwrightermaindialog.h"
#include "phylogeny_r.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtFisherWrighterMainDialog w;
  PhylogenyR();
  w.show();
  return a.exec();
}
