#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <boost/shared_ptr.hpp>
#include "dialog.h"
#include "ui_dialog.h"
#pragma GCC diagnostic pop

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_button_clicked()
{
  const QString filename = "CppQPrinterExample2.pdf";

  //Set up a QPrinter
  QPrinter printer;
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOrientation(QPrinter::Portrait);
  printer.setPaperSize(QPrinter::A4);
  printer.setFullPage(false);
  printer.setOutputFileName(filename);

  //Grab the window
  const QImage image = QPixmap::grabWindow(this->winId()).toImage();

  //Draw the image to painter to printer
  QPainter painter;
  painter.begin(&printer);
  painter.drawImage(0,0,image);
  painter.end();

  //Start the printer
  boost::shared_ptr<QPrintDialog> dialog(new QPrintDialog(&printer));
  dialog->exec();
}
