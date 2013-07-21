//Support only Qt5
#include <qglobal.h>
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
  #error Should be Qt5
#endif

#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Dialog w;
  w.show();
  return a.exec();
}

