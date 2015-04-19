#include "qttestqtdnasequencesdisplay.h"
#include "dna_r.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DnaR();
  QtTestQtDnaSequencesDisplay w;
  w.show();

  return a.exec();
}
