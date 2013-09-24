#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>
#include "toolstylesheetsettermaindialog.h"
#pragma GCC diagnostic pop

//2013-01-09: 0.1: initial version with a main dialog only
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::ToolStyleSheetSetterMainDialog w;
  w.show();
  return a.exec();
}
