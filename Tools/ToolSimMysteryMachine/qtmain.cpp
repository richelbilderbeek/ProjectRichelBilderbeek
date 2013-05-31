//---------------------------------------------------------------------------
#include <QtGui/QApplication>
#include "qtsimmysterymachinemenudialog.h"
#include "trace.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();
  QtSimMysteryMachineMenuDialog w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------
