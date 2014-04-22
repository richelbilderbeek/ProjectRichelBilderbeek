#include "qtbrainspinnermaindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtBrainSpinnerMainDialog w;
  w.show();

  return a.exec();
}
