#include "qtcodebreakermaindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtCodeBreakerMainDialog w;
  w.show();
  
  return a.exec();
}
