#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtdialog.h"

#include <boost/shared_ptr.hpp>

#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

#include "ui_qtdialog.h"
#pragma GCC diagnostic pop

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  QPrinter printer;

  const boost::shared_ptr<QPrintDialog> print_dialog(new QPrintDialog(&printer));
  if (print_dialog->exec() != QDialog::Accepted)
  {
    return;
  }

  QPainter painter;

  painter.begin(&printer);
  this->render(&painter);
  painter.end();
}
