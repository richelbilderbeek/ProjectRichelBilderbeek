#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>

#include <future>
#include "qtfisherwrightermaindialog.h"
#include "beast.h"
#include "counter.h"
#include "dna_r.h"
#include "ribi_rinside.h"
#include "phylogeny_r.h"
#include "newickutils.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::fw::QtFisherWrighterMainDialog w;
  w.show();
  return a.exec();
}
