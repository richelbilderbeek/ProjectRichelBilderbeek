#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include "qtnsanabrosmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  START_TRACE();
  QApplication a(argc, argv);
  ribi::QtNsanaBrosMenuDialog w;
  w.show();
  return a.exec();
}
