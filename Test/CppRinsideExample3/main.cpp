#include <QApplication>
#include "qtdialog.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QtDialog d;
  d.show();
  return app.exec();
}
