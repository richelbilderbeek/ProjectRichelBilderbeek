#include "pongdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PongDialog w;
  w.show();

  return a.exec();
}
