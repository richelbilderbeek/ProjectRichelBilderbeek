#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthometrainermenudialog.h"

#include <QDesktopWidget>
#include "hometrainermenudialog.h"
#include "qtaboutdialog.h"
#include "qthometrainermaindialog.h"
#include "ui_qthometrainermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtHometrainerMenuDialog::QtHometrainerMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtHometrainerMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtHometrainerMenuDialog::~QtHometrainerMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtHometrainerMenuDialog::on_button_about_clicked() noexcept
{
  About a = HometrainerMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtHometrainerMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtHometrainerMenuDialog::on_button_start_clicked() noexcept
{
  QtHometrainerMainDialog d;
  ShowChild(&d);
}

