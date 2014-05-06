#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtsecretmessagecreatedialog.h"

#include <cassert>

#include <boost/shared_ptr.hpp>

#include <QFileDialog>

#include "secretmessagemaindialog.h"

#include "ui_qtsecretmessagecreatedialog.h"
#pragma GCC diagnostic pop

ribi::sema::QtSecretMessageCreateDialog::QtSecretMessageCreateDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSecretMessageCreateDialog)
{
  ui->setupUi(this);

  ui->stackedWidget->setCurrentIndex(0);
}

ribi::sema::QtSecretMessageCreateDialog::~QtSecretMessageCreateDialog() noexcept
{
  delete ui;
}

void ribi::sema::QtSecretMessageCreateDialog::on_button_load_original_clicked()
{
  const std::string filename
    = QFileDialog::getOpenFileName(
      0,"Please select an image to hide a message in",
      QString(),"*.png *.bmp *.jpg *.jpeg").toStdString();
  if (filename.empty()) return;

  QPixmap pixmap(filename.c_str());
  ui->label_original->setPixmap(pixmap);
  ui->stackedWidget->setCurrentIndex(1);
  ui->button_load_secret->setFocus();
}

void ribi::sema::QtSecretMessageCreateDialog::on_button_load_secret_clicked()
{
  const std::string filename
    = QFileDialog::getOpenFileName(
      0,"Please select an image to hide a message in",
      QString(),"*.png *.bmp *.jpg *.jpeg").toStdString();
  if (filename.empty()) return;
  {
    QPixmap pixmap(filename.c_str());
    ui->label_secret->setPixmap(pixmap);
    ui->stackedWidget->setCurrentIndex(2);
    ui->button_save->setFocus();
  }
  //Convert
  {
    const boost::shared_ptr<const QImage> source {
      new QImage(ui->label_original->pixmap()->toImage())
    };
    const boost::shared_ptr<const QImage> message {
      new QImage(ui->label_secret->pixmap()->toImage())
    };
    const boost::shared_ptr<const QImage> result {
      MainDialog().CreateSecretMessageRed(source,message)
    };
    QPixmap pixmap { QPixmap::fromImage(*result) };
    ui->label_result->setPixmap(pixmap);
  }
}

void ribi::sema::QtSecretMessageCreateDialog::on_button_save_clicked()
{
  const std::string filename
    = QFileDialog::getSaveFileName(
      0,"Please choose a filename to save the result to",
      QString(),"*.png *.bmp").toStdString();
  if (filename.empty()) return;
  ui->label_result->pixmap()->save(filename.c_str());
}
