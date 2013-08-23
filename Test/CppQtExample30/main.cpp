#include "commander.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Commander::GetInstance()->Run();
}
