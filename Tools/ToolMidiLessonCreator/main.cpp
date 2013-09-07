#include <QApplication>
#include "qtmidilessoncreatormaindialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtMidiLessonCreatorMainDialog w;
  w.show();  
  return a.exec();
}
