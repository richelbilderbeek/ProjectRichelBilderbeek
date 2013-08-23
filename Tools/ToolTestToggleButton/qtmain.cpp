#include <QApplication>
#include "qttesttogglebuttonmenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestToggleButtonMenuDialog w;
  w.show();
  return a.exec();
}
