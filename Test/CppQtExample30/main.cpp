#include "commander.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Commander::GetInstance()->Run();
}
