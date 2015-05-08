#include <QApplication>
#include "qttesthistogrammenudialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtTestHistogramMenuDialog w;
  w.show();
  return a.exec();
}
