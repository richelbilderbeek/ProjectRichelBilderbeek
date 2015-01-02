#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>
#include "qtvisualabcmenudialog.h"
#include "visualabccheckprerequisites.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::CheckPrerequisites();
  ribi::QtVisualAbcMenuDialog w;
  w.show();
  return a.exec();
}

