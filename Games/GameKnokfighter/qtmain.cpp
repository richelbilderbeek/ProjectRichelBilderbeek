#include <QtGui/QApplication>
#include "qtknokfightermaindialog.h"
#include "trace.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();
  QtKnokfighterMainDialog w;
  w.show();
  return a.exec();
}
