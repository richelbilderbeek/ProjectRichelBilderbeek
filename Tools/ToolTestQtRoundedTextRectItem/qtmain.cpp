#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <QApplication>
#include <QDesktopWidget>
#include "qttestqtroundedtextrectitemmenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestQtRoundedTextRectItemMenuDialog w;
  w.show();
  return a.exec();
}
