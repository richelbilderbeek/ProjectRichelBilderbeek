#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpixelatormenudialog.h"

#include <cassert>

#include "pixelatormenudialog.h"
#include "qtaboutdialog.h"
#include "qtpixelatormaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtpixelatormenudialog.h"
#pragma GCC diagnostic pop

ribi::QtPixelatorMenuDialog::QtPixelatorMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPixelatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtPixelatorMenuDialog::~QtPixelatorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtPixelatorMenuDialog::on_button_start_clicked()
{
  QtPixelatorMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtPixelatorMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(PixelatorMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtPixelatorMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtPixelatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtPixelatorMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
