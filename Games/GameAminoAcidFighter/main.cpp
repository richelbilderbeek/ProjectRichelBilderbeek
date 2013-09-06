#include <QApplication>
#include "dialogmain.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::DialogMain w;
  w.show();
  return a.exec();
}
