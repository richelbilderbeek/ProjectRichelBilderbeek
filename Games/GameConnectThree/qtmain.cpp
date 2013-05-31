//---------------------------------------------------------------------------
#include <QtGui/QApplication>
#include "connectthreeresources.h"
#include "qtconnectthreemenudialog.h"
#include "trace.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  START_TRACE();
  //ConnectThreeResources::Check();

  QtConnectThreeMenuDialog w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------
