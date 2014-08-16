#include <QApplication>
#include "qttestfunctionparsermenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtTestFunctionParserMenuDialog w;
  w.show();
  return a.exec();
}

