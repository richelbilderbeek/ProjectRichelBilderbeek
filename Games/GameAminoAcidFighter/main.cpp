#include <QApplication>
#include "dialogmain.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DialogMain w;
  w.show();
  return a.exec();
}
