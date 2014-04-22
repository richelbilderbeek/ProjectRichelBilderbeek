#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtvirtualbastardmenudialog.h"
#include <QApplication>
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtVirtualBastardMenuDialog w;
  w.show();
  return a.exec();
}
