//---------------------------------------------------------------------------
#include <QApplication>
#include "grabmedialog.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  GrabMeDialog w;
#if defined(Q_WS_S60)
  w.showMaximized();
#else
  w.show();
#endif
  return a.exec();
}
//---------------------------------------------------------------------------
