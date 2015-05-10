#include "qtwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include "paper_rock_scissors.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TestPaperRockScissors();
  QtWidget w;
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    w.move( screen.center() - w.rect().center() );
  }
  w.show();
  return a.exec();
}
