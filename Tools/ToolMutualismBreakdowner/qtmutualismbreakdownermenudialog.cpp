#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmutualismbreakdownermenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "mutualismbreakdownermenudialog.h"
#include "qtmutualismbreakdownertimeplotdialog.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"
#include "qtmutualismbreakdownertestconsumptionfunctiondialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtmutualismbreakdownermenudialog.h"
#pragma GCC diagnostic pop


ribi::QtMutualismBreakdownerMenuDialog::QtMutualismBreakdownerMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMutualismBreakdownerMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtMutualismBreakdownerMenuDialog::~QtMutualismBreakdownerMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtMutualismBreakdownerMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}


void ribi::QtMutualismBreakdownerMenuDialog::on_button_about_clicked()
{
  About a = MutualismBreakdownerMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtMutualismBreakdownerMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtMutualismBreakdownerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtMutualismBreakdownerMenuDialog();
}
#endif

void ribi::QtMutualismBreakdownerMenuDialog::on_button_start_time_plot_clicked()
{
  QtMutualismBreakdownerTimePlotDialog d;
  ShowChild(&d);

}

void ribi::QtMutualismBreakdownerMenuDialog::on_button_start_equilibrium_plot_clicked()
{
  QtMutualismBreakdownerEquilibriumDialog d;
  ShowChild(&d);
}

void ribi::QtMutualismBreakdownerMenuDialog::on_button_consumption_clicked()
{
  QtMutualismBreakdownerTestConsumptionFunctionDialog d;
  ShowChild(&d);
}
