#include <QApplication>
#include "cppqwebviewexample1dialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CppQWebViewExample1Dialog w;
  w.show();  
  return a.exec();
}
