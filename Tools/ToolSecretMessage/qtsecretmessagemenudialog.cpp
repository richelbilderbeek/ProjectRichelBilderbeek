#include "qtaboutdialog.h"
#include "qtsecretmessagecreatedialog.h"
#include "qtsecretmessageextractdialog.h"
#include "qtsecretmessagemenudialog.h"
#include "secretmessagemenudialog.h"
#include "ui_qtsecretmessagemenudialog.h"
//---------------------------------------------------------------------------
QtSecretMessageMenuDialog::QtSecretMessageMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtSecretMessageMenuDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtSecretMessageMenuDialog::~QtSecretMessageMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------

void QtSecretMessageMenuDialog::on_button_about_clicked()
{
  About a = SecretMessage::MenuDialog::GetAbout();
  //a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + RichelBilderbeek::QtResources::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void QtSecretMessageMenuDialog::on_button_create_clicked()
{
  QtSecretMessageCreateDialog d;
  this->hide();
  d.exec();
  this->show();
}

void QtSecretMessageMenuDialog::on_button_extract_clicked()
{
  QtSecretMessageExtractDialog d;
  this->hide();
  d.exec();
  this->show();
}


void QtSecretMessageMenuDialog::on_button_quit_clicked()
{
  close();
}


