#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <thread>
#include <QApplication>
#include "qtsearchanddestroychessmenudialog.h"
#pragma GCC diagnostic pop

///Graphics used from
///http://www.gnu.org/software/xboard/
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  std::thread t(
    []
    {
      ribi::sadc::QtSearchAndDestroyChessMenuDialog::Test();
    }
  );

  ribi::sadc::QtSearchAndDestroyChessMenuDialog w;
  w.show();
  t.detach();
  return a.exec();
}


