#include "qttestqtbeastdisplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtTestQtNewickDisplay w;
  w.show();

  return a.exec();
}
