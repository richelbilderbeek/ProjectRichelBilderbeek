#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <QtGui/QApplication>
#include "qtstateobservermenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtStateObserverMenuDialog w;
  w.show();
  return a.exec();
}
