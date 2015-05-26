#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtsimpredatorpraymaindialog.h"
#include "qtsimtoppredatorpraymaindialog.h"
#include <QApplication>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtSimTopPredatorPrayMainDialog w;
  //ribi::QtSimTopPredatorPrayMainDialog w;
  w.show();
  return a.exec();
}
