#include <QApplication>
#include "lizardpaperrockscissorsspock.h"
#include "qtlizardpaperrockscissorsspockmenudialog.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::TestLizardPaperRockScissorsSpock();
  ribi::QtLizardPaperRockScissorsSpockMenuDialog w;
  w.show();
  return a.exec();
}
