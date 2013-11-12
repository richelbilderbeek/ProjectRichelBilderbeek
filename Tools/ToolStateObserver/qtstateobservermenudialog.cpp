#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstateobservermenudialog.h"

#include "qtaboutdialog.h"
#include "qtstateobservermaindialog.h"
#include "qthideandshowdialog.h"
#include "stateobservermenudialog.h"
#include "ui_qtstateobservermenudialog.h"

#pragma GCC diagnostic pop

ribi::QtStateObserverMenuDialog::QtStateObserverMenuDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtStateObserverMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtStateObserverMenuDialog::~QtStateObserverMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtStateObserverMenuDialog::on_button_start_clicked() noexcept
{
  QtStateObserverMainDialog d;
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtStateObserverMenuDialog::on_button_about_clicked() noexcept
{
  About a = StateObserverMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtStateObserverMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

