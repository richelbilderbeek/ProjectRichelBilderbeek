#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include "mydialog.h"
#pragma GCC diagnostic pop

int main( int argc, char **argv )
{
  QApplication a( argc, argv );
  MyDialog d;
  d.show();
  d.setWindowTitle(argv[0]);
  return a.exec();
}
