#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include "grabmedialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  GrabMeDialog w;
  w.show();
  return a.exec();
}
