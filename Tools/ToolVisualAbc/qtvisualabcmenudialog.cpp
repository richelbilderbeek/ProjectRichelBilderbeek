//---------------------------------------------------------------------------
#include "about.h"
#include "qtaboutdialog.h"
#include "qtmaindialog.h"
#include "qtvisualabcmenudialog.h"
#include "ui_qtvisualabcmenudialog.h"
#include "menudialog.h"
//---------------------------------------------------------------------------
QtVisualAbcMenuDialog::QtVisualAbcMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtVisualAbcMenuDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtVisualAbcMenuDialog::~QtVisualAbcMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtVisualAbcMenuDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
//---------------------------------------------------------------------------
void QtVisualAbcMenuDialog::on_button_start_clicked()
{
  QtMainDialog d;
  this->hide();
  d.exec();
  this->show();
  this->ui->button_start->setFocus();
}
//---------------------------------------------------------------------------
void QtVisualAbcMenuDialog::on_button_about_clicked()
{
  About a = VisualAbcMenuDialog::GetAbout();
  QtAboutDialog d(a);
  this->hide();
  d.exec();
  this->show();
  this->ui->button_about->setFocus();
}
//---------------------------------------------------------------------------
void QtVisualAbcMenuDialog::on_button_quit_clicked()
{
  close();
}
//---------------------------------------------------------------------------
