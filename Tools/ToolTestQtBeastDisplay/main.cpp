#include "qttestqtbeastdisplay.h"
#include "beast.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Beast();
  QtTestQtBeastDisplay w;
  w.show();

  return a.exec();
}
