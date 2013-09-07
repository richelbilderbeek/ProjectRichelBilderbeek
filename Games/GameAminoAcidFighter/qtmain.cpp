#include <QApplication>
#include "qtaminoacidfightermaindialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::aaf::QtAminoAcidFighterMainDialog w;
  w.show();
  return a.exec();
}
