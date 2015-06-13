#include "qttreesearchermaindialog.h"
#include <QApplication>

#include "birthdeathmodelhelper.h"
#include "phylogeny_r.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::bdm::Helper();
  ribi::PhylogenyR();
  QtTreesearcherMainDialog w;
  w.show();
  return a.exec();
}
