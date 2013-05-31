#include <QApplication>
#include "toolstylesheetsettermaindialog.h"

//2013-01-09: 0.1: initial version with a main dialog only
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ToolStyleSheetSetterMainDialog w;
  w.show();
  return a.exec();
}
