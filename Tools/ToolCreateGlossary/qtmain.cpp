#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>
#include "qtcreateglossarymenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();
  ribi::QtCreateGlossaryMenuDialog w;
  w.show();
  return a.exec();
}
