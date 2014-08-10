#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtgraycodermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "graycodermenudialog.h"
#include "qtaboutdialog.h"
#include "qtgraycodermaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtgraycodermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtGrayCoderMenuDialog::QtGrayCoderMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtGrayCoderMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtGrayCoderMenuDialog::~QtGrayCoderMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtGrayCoderMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtGrayCoderMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = ribi::GrayCoderMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtGrayCoderMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtGrayCoderMenuDialog::on_button_start_clicked() noexcept
{
  QtGrayCoderMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtGrayCoderMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtGrayCoderMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
