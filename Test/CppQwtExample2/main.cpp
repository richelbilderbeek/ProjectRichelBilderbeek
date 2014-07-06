#include <QApplication>
#include "qtwidget.h"
#include "qwtplotwidget.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtWidget widget;
  widget.setGeometry(100,100,800,600);
  widget.show();
  return a.exec();
}
