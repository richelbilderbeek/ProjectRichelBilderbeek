#include "qtvirtualbastardmenudialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtVirtualBastardMenuDialog w;
  w.show();
  return a.exec();
}
