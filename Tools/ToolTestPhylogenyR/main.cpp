#include "qttestphylogenyrdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestPhylogenyRdialog w;
  w.show();

  return a.exec();
}
