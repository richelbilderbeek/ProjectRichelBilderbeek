#include <qglobal.h>
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  #include <QApplication>
#else
  #include <QApplication>
#endif

#include "qtdialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtDialog w;
  w.show();
  
  return a.exec();
}
