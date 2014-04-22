#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtocrwidget.h"

#include <QFile>

#include "ocr.h"
#pragma GCC diagnostic pop

QtOcrWidget::QtOcrWidget(
  const std::string& datafile,
  const std::string& whitelist,
  QWidget *parent)
  : QtSketchWidget(parent),
    m_ocr(new Ocr(datafile,whitelist))
{
  //assert(QFile::exists(datafile.c_str())); //Tesseract adds path
}

const std::string QtOcrWidget::Read() const
{
  QImage copy = const_cast<QtOcrWidget*>(this)->grab().toImage();
  //QImage copy = QPixmap::grabWidget(const_cast<QtOcrWidget*>(this)).toImage();
  copy.save("QtOcrWidget.png");
  const std::string text = m_ocr->Read(
    copy.bits(),
    copy.depth() / 8, //Convert bit to byte
    copy.bytesPerLine(),
    0, //left
    0, //top
    copy.width(),
    copy.height());
  return text;
}
