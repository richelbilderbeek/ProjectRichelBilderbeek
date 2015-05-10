#include "qtwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include "lizard_paper_rock_scissors_spock.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TestLizardPaperRockScissorsSpock();
  QtWidget w;
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    w.move( screen.center() - w.rect().center() );
  }
  w.show();
  return a.exec();
}
