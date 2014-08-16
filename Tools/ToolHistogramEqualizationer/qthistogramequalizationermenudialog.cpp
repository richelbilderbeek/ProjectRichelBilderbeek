#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthistogramequalizationermenudialog.h"

#include "qtaboutdialog.h"
#include "histogramequalizationermenudialog.h"
#include "qthistogramequalizationermaindialog.h"
#include "ui_qthistogramequalizationermenudialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtHistogramEqualizationerMenuDialog::QtHistogramEqualizationerMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtHistogramEqualizationerMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtHistogramEqualizationerMenuDialog::~QtHistogramEqualizationerMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtHistogramEqualizationerMenuDialog::on_button_start_clicked()
{
  QtHistogramEqualizationerMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtHistogramEqualizationerMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(HistogramEqualizationerMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtHistogramEqualizationerMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtHistogramEqualizationerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtHistogramEqualizationerMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
