#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestbinarynewickvectormenudialog.h"

#include <cassert>

#include "testbinarynewickvectormenudialog.h"
#include "qtaboutdialog.h"
#include "qttestbinarynewickvectormaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestbinarynewickvectormenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestBinaryNewickVectorMenuDialog::QtTestBinaryNewickVectorMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestBinaryNewickVectorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestBinaryNewickVectorMenuDialog::~QtTestBinaryNewickVectorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestBinaryNewickVectorMenuDialog::on_button_start_clicked()
{
  QtTestBinaryNewickVectorMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestBinaryNewickVectorMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestBinaryNewickVectorMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtTestBinaryNewickVectorMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestBinaryNewickVectorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtTestBinaryNewickVectorMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
