#include <QApplication>
#include <QDesktopWidget>
#include "qtarrowswidget.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtArrowsWidget w;
  {
    //Resize the dialog and put it in the screen center
    w.setGeometry(0,0,600,400);
    const QRect screen = QApplication::desktop()->screenGeometry();
    w.move( screen.center() - w.rect().center() );
  }
  w.show();
  return a.exec();
}
