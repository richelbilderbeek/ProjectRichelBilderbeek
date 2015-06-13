#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmutualismbreakdownermenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "mutualismbreakdownermenudialog.h"
#include "qtmutualismbreakdownertimeplotdialog.h"
#include "qtmutualismbreakdownerspatialplotdialog.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"
#include "qtpoisoningfunctionwidget.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtmutualismbreakdownermenudialog.h"
#pragma GCC diagnostic pop


ribi::mb::QtMutualismBreakdownerMenuDialog::QtMutualismBreakdownerMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMutualismBreakdownerMenuDialog)
{
  ui->setupUi(this);
}

ribi::mb::QtMutualismBreakdownerMenuDialog::~QtMutualismBreakdownerMenuDialog() noexcept
{
  delete ui;
}

void ribi::mb::QtMutualismBreakdownerMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}


void ribi::mb::QtMutualismBreakdownerMenuDialog::on_button_about_clicked()
{
  About a = ribi::mb::MenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::mb::QtMutualismBreakdownerMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::mb::QtMutualismBreakdownerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::mb::MenuDialog().GetAbout();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtMutualismBreakdownerMenuDialog();
}
#endif

void ribi::mb::QtMutualismBreakdownerMenuDialog::on_button_start_time_clicked()
{
  QtMutualismBreakdownerTimePlotDialog d;
  ShowChild(&d);

}

void ribi::mb::QtMutualismBreakdownerMenuDialog::on_button_start_spatial_clicked()
{
  QtMutualismBreakdownerSpatialPlotDialog d;
  ShowChild(&d);
}
