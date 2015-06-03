#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstochasticityinspectormenudialog.h"

#include "qtaboutdialog.h"
#include "qtstochasticityinspectormaindialog.h"
#include "qthideandshowdialog.h"
#include "ribi_apfloat.h"
#include "stochasticityinspectormenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtstochasticityinspectormenudialog.h"

#pragma GCC diagnostic pop

ribi::QtStochasticityInspectorMenuDialog::QtStochasticityInspectorMenuDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtStochasticityInspectorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtStochasticityInspectorMenuDialog::~QtStochasticityInspectorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtStochasticityInspectorMenuDialog::on_button_start_clicked() noexcept
{
  QtStochasticityInspectorMainDialog d;
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtStochasticityInspectorMenuDialog::on_button_about_clicked() noexcept
{
  About a = StochasticityInspectorMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtStochasticityInspectorMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtStochasticityInspectorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::Apfloat();
    QtStochasticityInspectorMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
