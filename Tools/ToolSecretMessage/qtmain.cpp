#include <QApplication>
#include "qtsecretmessagemenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtSecretMessageMenuDialog w;
  w.show();
  return a.exec();
}
