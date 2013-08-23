//---------------------------------------------------------------------------
#include <QApplication>
#include "qtnsanabrosmenudialog.h"
#include "trace.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  START_TRACE();
  QApplication a(argc, argv);
  QtNsanaBrosMenuDialog w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------
