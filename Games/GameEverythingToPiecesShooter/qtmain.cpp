#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include "qteverythingtopiecesshootergamewidget.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  a.setStyleSheet(
    "QDialog { "
    "  background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #FF9090, stop: 1 #9090FF);"
    "}"
  );

  QtEverythingToPiecesShooterGameWidget w;
  w.show();
  return a.exec();
}
