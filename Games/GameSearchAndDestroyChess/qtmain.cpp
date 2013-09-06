#include <thread>
#include <QApplication>
#include "qtsearchanddestroychessmenudialog.h"

///Graphics used from
///http://www.gnu.org/software/xboard/

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  std::thread t(
    []
    {
      ribi::QtSearchAndDestroyChessMenuDialog::Test();
    }
  );

  ribi::QtSearchAndDestroyChessMenuDialog w;
  w.show();
  t.detach();
  return a.exec();
}


