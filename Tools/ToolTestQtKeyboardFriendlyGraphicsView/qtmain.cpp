#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <QApplication>
#include <QDesktopWidget>
#include "qttestkeyboardfriendlygraphicsviewmenudialog.h"
#include "trace.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  START_TRACE();

  QtTestKeyboardFriendlyGraphicsViewMenuDialog d;
  d.show();
  return a.exec();
}
