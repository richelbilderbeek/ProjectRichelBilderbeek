#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttronmenudialog.h"

#include "qtaboutdialog.h"
#include "tronmenudialog.h"
#include "qttrongamedialog.h"
#include "ui_qttronmenudialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::tron::QtTronMenuDialog::QtTronMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTronMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::tron::QtTronMenuDialog::~QtTronMenuDialog() noexcept
{
  delete ui;
}

void ribi::tron::QtTronMenuDialog::on_button_start_clicked()
{
  QtTronGameDialog d;
  this->ShowChild(&d);
}

void ribi::tron::QtTronMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TronMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::tron::QtTronMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::tron::QtTronMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTronGameDialog();
}
#endif
