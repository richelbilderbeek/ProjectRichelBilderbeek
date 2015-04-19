#include "qttestnewickutilsdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestNewickUtilsdialog w;
  w.show();

  return a.exec();
}
