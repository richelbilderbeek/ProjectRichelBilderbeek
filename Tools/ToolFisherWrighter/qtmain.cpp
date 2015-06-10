#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>

#include <future>
#include "qtfisherwrightermaindialog.h"
#include "counter.h"
#include "dna_r.h"
#include "phylogeny_r.h"
#include "newickutils.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  PhylogenyR();
  std::async([](){ DnaR();} );
  std::async([](){ PhylogenyR();} );
  std::async([](){ NewickUtils();} );
  std::async([](){ ribi::Counter();} );
  /*
  std::async( std::launch::async, []() { PhylogenyR();} );
  std::async( std::launch::async, []() { NewickUtils();} );
  std::async( std::launch::async, []() { ribi::Counter();} );
  */
  QtFisherWrighterMainDialog w;
  w.show();
  return a.exec();
}
