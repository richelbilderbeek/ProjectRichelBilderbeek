#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <algorithm>
#include <cassert>
#include <string>

#include <QApplication>
#include <QDir>
#include <QFile>

#include "ocr.h"
#include "qtocrinputdialog.h"
#include "qtocrwidget.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  //Check if dataset exists. If not, recreate it
  const std::string qrcfilename = "eng.traineddata";
  //Tesseract wants it to be in a folder called tessdata
  const std::string tesseract_filename = "tessdata/eng.traineddata";
  if (!QFile::exists(tesseract_filename.c_str()))
  {
    QFile f( (std::string(":/data/") + qrcfilename).c_str() );
    assert(f.size() > 0);
    QDir().mkdir("tessdata");
    bool success = f.copy(tesseract_filename.c_str());

    assert(success);
    f.close();
  }
  assert(QFile::exists(tesseract_filename.c_str()));

  //The chars enabled to be detected
  const std::string whitelist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  //But Tesseract wants the qrc filename, because it will add the 'tessdata' folder itself
  QtOcrInputDialog w(std::string("./") + qrcfilename,whitelist);

  w.show();

  return a.exec();
}
