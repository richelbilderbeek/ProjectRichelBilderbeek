#include "qttreesearchermaindialog.h"
#include <QApplication>

#include "phylogeny_r.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PhylogenyR();
  QtTreesearcherMainDialog w;
  w.show();
  return a.exec();
}
