#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>

#include "qtzeromaindialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  //Start the application
  QApplication a(argc, argv);

  //Load the dialog
  ribi::QtZeroMainDialog w;

  //Show the dialog
  w.show();

  //Execute the application
  return a.exec();
}

