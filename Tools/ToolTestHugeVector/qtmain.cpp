#include <QApplication>
#include "qttesthugevectormaindialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestHugeVectorMainDialog w;
  w.show();
  return a.exec();
}
