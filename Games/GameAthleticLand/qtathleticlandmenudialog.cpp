#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtathleticlandmenudialog.h"

#include "qtaboutdialog.h"
#include "athleticlandmenudialog.h"
#include "qtathleticlandmaindialog.h"
#include "testtimer.h"
#include "ui_qtathleticlandmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::athl::QtAthleticLandMenuDialog::QtAthleticLandMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtAthleticLandMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::athl::QtAthleticLandMenuDialog::~QtAthleticLandMenuDialog() noexcept
{
  delete ui;
}

void ribi::athl::QtAthleticLandMenuDialog::on_button_start_clicked()
{
  QtAthleticLandMainDialog d;
  this->ShowChild(&d);
}

void ribi::athl::QtAthleticLandMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(AthleticLandMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::athl::QtAthleticLandMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::athl::QtAthleticLandMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtAthleticLandMainDialog();
  AthleticLandMenuDialog();
}
#endif
