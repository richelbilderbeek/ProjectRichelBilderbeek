#include <QApplication>
#include <QDesktopWidget>
#include "qttesthideandshowmaindialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestHideAndShowMainDialog d;
  d.show();
  return a.exec();
}
