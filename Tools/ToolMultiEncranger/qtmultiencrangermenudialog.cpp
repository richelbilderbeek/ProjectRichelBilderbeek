#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmultiencrangermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "multiencrangermenudialog.h"
#include "qtaboutdialog.h"
#include "qtmultiencrangermaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtmultiencrangermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtMultiEncrangerMenuDialog::QtMultiEncrangerMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtToolMultiEncrangerMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtMultiEncrangerMenuDialog::~QtMultiEncrangerMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtMultiEncrangerMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtMultiEncrangerMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = ribi::MultiEncrangerMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtMultiEncrangerMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtMultiEncrangerMenuDialog::on_button_start_clicked() noexcept
{
  QtToolMultiEncrangerMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtMultiEncrangerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  MultiEncrangerMenuDialog();
  QtToolMultiEncrangerMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
