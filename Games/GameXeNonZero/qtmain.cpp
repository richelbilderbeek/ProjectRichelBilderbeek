#include <QApplication>
#include "qtxenonzeromaindialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtXeNonZeroMainDialog d;
  d.show();
  return a.exec();
}


