#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include "qtsearchanddestroychessmenudialog.h"
#pragma GCC diagnostic pop

///Graphics used from
///http://www.gnu.org/software/xboard/
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::sadc::QtSearchAndDestroyChessMenuDialog w;
  w.show();
  return a.exec();
}


