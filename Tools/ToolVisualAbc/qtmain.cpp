
//---------------------------------------------------------------------------
#include <QApplication>
#include "qtvisualabcmenudialog.h"
#include "checkprerequisites.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CheckPrerequisites();
  QtVisualAbcMenuDialog w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------
