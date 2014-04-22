#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttoolubuntuonewatchermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "toolubuntuonewatchermenudialog.h"
#include "qtaboutdialog.h"
#include "qttoolubuntuonewatchermaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qttoolubuntuonewatchermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtUbuntuOneWatcherMenuDialog::QtUbuntuOneWatcherMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtUbuntuOneWatcherMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtUbuntuOneWatcherMenuDialog::~QtUbuntuOneWatcherMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtUbuntuOneWatcherMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtUbuntuOneWatcherMenuDialog::on_button_about_clicked()
{
  About a = UbuntuOneWatcherMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtUbuntuOneWatcherMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtUbuntuOneWatcherMenuDialog::on_button_start_clicked()
{
  QtUbuntuOneWatcherMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

