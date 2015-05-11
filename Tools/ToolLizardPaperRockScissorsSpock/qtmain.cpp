#include "qtwidget.h"
#include <QApplication>
#include "lizard_paper_rock_scissors_spock.h"
#include "qtlizardpaperrockscissorsspockmenudialog.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TestLizardPaperRockScissorsSpock();
  ribi::QtLizardPaperRockScissorsSpockMenuDialog w;
  w.show();
  return a.exec();
}
