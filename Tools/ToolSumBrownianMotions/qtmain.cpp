#include <QApplication>
#include "qtsumbrownianmotionsmenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtSumBrownianMotionsMenuDialog w;
  w.show();
  return a.exec();
}
