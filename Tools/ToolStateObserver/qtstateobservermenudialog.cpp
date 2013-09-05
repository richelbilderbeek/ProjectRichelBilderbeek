#include "qtstateobservermenudialog.h"

#include "qtaboutdialog.h"
#include "qtstateobservermaindialog.h"
#include "qthideandshowdialog.h"
#include "stateobservermenudialog.h"
#include "ui_qtstateobservermenudialog.h"

ribi::QtStateObserverMenuDialog::QtStateObserverMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtStateObserverMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtStateObserverMenuDialog::~QtStateObserverMenuDialog()
{
  delete ui;
}

void ribi::QtStateObserverMenuDialog::on_button_start_clicked()
{
  QtStateObserverMainDialog d;
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtStateObserverMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = StateObserverMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  d.exec();
  this->show();
}

void ribi::QtStateObserverMenuDialog::on_button_quit_clicked()
{
  close();
}

